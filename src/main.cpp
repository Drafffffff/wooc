#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <LittleFS.h>
#define APSSID "ESPap"
#include <ArduinoJson.h>
#include <StreamUtils.h>
#include <string>
#include <ESP8266WiFiMulti.h>
String header;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
const long timeoutTime = 2000;
ESP8266WebServer server(80);
DynamicJsonDocument WIFI_CONFIG(1024);
ESP8266WiFiMulti wifiMulti;
struct WifiInfo
{
  String WIFI_NAME;
  String WIFI_PASSWORD;
};
struct Config
{
  unsigned int WIFISTATE;
  WifiInfo WIFIINFOS[3];
};

Config config;
//TODO:不存在config文件自动生成
//TODO:拆分文件 模块化
Config loadConfiguration(Config conf)
{
  //TODO:从fs读取配置文件

  File confFile = LittleFS.open("/config/config.json", "r");
  ReadBufferingStream bufferedFile{confFile, 1024};
  DeserializationError error = deserializeJson(WIFI_CONFIG, bufferedFile);
  if (error)
  {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
  }
  conf.WIFISTATE = WIFI_CONFIG["WIFI_STATE"].as<int>();
  JsonArray wifiConfs = WIFI_CONFIG["WIFI_CONF"].as<JsonArray>();
  int i = 0;
  for (JsonObject v : wifiConfs)
  {
    Serial.println(v["WIFI_NAME"].as<String>());
    conf.WIFIINFOS[i].WIFI_NAME = v["WIFI_NAME"].as<String>();
    conf.WIFIINFOS[i].WIFI_PASSWORD = v["WIFI_PASSWORD"].as<String>();
    i++;
  }
  Serial.println(conf.WIFISTATE);
  Serial.println(conf.WIFIINFOS[0].WIFI_NAME);
  return conf;
}
void handleRoot()
{
  Serial.println("root");
  File file = LittleFS.open("/www/index.html", "r");
  server.streamFile(file, "text/html");
  file.close();
}

void handlePost()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else
  {
    server.send(200, "text/plain", "POST body was:\n" + server.arg("plain"));
    Serial.print("ssid: ");
    Serial.println(server.arg("ssid"));
    Serial.print("password: ");
    Serial.println(server.arg("password"));
  }
}
String wifi_type(int typecode)
{
  if (typecode == ENC_TYPE_NONE)
    return "Open";
  if (typecode == ENC_TYPE_WEP)
    return "WEP ";
  if (typecode == ENC_TYPE_TKIP)
    return "WPA ";
  if (typecode == ENC_TYPE_CCMP)
    return "WPA2";
  if (typecode == ENC_TYPE_AUTO)
    return "WPA*";
  else
    return "UNKNOW";
}

void handleScan()
{
  Serial.println("Scan Start");
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  Serial.println("Scan Done");
  if (n == 0)
  {
    Serial.println("not found");
  }
  else
  {
    StaticJsonDocument<1024> wifiscan;
    Serial.print(n);
    Serial.println("networks found");
    for (int i = 0; i < n; i++)
    {
      JsonObject doc = wifiscan.createNestedObject();
      doc["SSID"] = (String)WiFi.SSID(i);
      doc["encryptionType"] = wifi_type(WiFi.encryptionType(i));
      doc["RSSI"] = (int)WiFi.RSSI(i);
    }
    String wifidata;
    serializeJson(wifiscan, wifidata);
    server.send(200, "text/json;charset=UTF-8", wifidata);
  }
}

void handleConnect()
{
  if (server.method() != HTTP_POST)
  {
    server.send(405, "text/plain", "Method Not Allowed");
  }
  else
  {
    server.send(200, "text/plain", "POST body was:\n" + server.arg("plain"));
    Serial.print("ssid: ");
    Serial.println(server.arg("ssid"));
    Serial.print("password: ");
    Serial.println(server.arg("password"));
  }
}

void saveConfiguration()
{
  //TODO:保存配置文件
}
void setup()
{
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  LittleFS.begin();
  Serial.println();
  config = loadConfiguration(config);

  if (config.WIFISTATE == 0)
  {
    //TODO:AP连接模式
    //TODO:配置DNS服务器
    //TODO:AP后台网页
    Serial.println(sizeof(config.WIFIINFOS));
    for (WifiInfo w : config.WIFIINFOS)
    {
      Serial.println(w.WIFI_NAME);
    }
    Serial.println("AP模式");
    WiFi.softAP(APSSID);
    Serial.println();
    Serial.print("AP IP address:");
    Serial.println(WiFi.softAPIP());
    server.on("/", handleRoot);
    server.on("/post", handlePost);
    server.on("/scan", handleScan);
    server.on("/connect", handleConnect);
    server.begin();
  }
  else
  {
    for (WifiInfo w : config.WIFIINFOS)
    {
      wifiMulti.addAP(w.WIFI_NAME.c_str(), w.WIFI_PASSWORD.c_str());
    }
    //TODO:设置wifi连接超时，若无法连接则改变状态 wifimulti.run(yanshi)
    if (wifiMulti.run() == WL_CONNECTED)
    {
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
    }
  }
}
void loop()
{
  server.handleClient();
  // MDNS.update();
}
