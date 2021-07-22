<template>
  <div>
    <ul class="wifi-list">
      <li
        v-for="(wifiInfo, index) in wifiList"
        :key="index"
        @click="selectSSID(wifiInfo)"
      >
        <p class="SSID">{{ wifiInfo.SSID }}</p>
        <p class="encryptionType">{{ wifiInfo.encryptionType }}</p>
        <p class="RSSI">{{ wifiInfo.RSSI }}</p>
      </li>
    </ul>
    <div class="modal" v-if="isShowmodal">
      <p>{{ SSID }}</p>
      <input v-model="password" type="password" />
      <button @click="submit">连接</button>
    </div>
  </div>
</template>
<script>
export default {
  setup() {},
  data() {
    return {
      isShowmodal: false,
      wifiList: {},
      SSID: "",
      password: "",
    };
  },
  beforeMount() {
    fetch(process.env.VUE_APP_SCAN_WIFI_URL)
      .then(res => {
        return res.json();
      })
      .then(d => {
        //去重
        let obj = {};
        d = d.reduce((cur, next) => {
          obj[next.SSID] ? "" : (obj[next.SSID] = true && cur.push(next));
          return cur;
        }, []);
        this.wifiList = d;
      });
  },
  methods: {
    selectSSID(wifiobj) {
      this.isShowmodal = true;
      this.SSID = wifiobj.SSID;
      console.log(wifiobj.SSID);
    },
    submit() {
      this.isShowmodal = false;
      console.log(this.password);
      this.password = "";
    },
  },
};
</script>

<style lang="scss">
.wifi-list {
  max-height: 40vh;
  background-color: rgb(195, 200, 216);
  overflow: scroll;
  overflow-x: hidden;
  margin: 10px 20px;
  border-radius: 5px;
  padding: 20px 20px;
  list-style-type: none;
  li {
    padding: 20px 0;
    border-radius: 5px;
    cursor: pointer;
    &:focus {
      background-color: rgb(108, 110, 134);
      transition: all 0.5ms ease-in-out;
    }
    &:hover {
      background-color: rgb(108, 110, 134);
      color: white;
      // transition: background-color 300ms linear;
      transition: all 0.5s ease-out;
    }
  }
}
.modal {
  position: absolute;
  width: 100vw;
  height: 100vh;
  background-color: rgba(0, 0, 0, 0.13);
  top: 0;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  button {
    font-family: Pixel, Avenir, Helvetica, Arial, sans-serif;
  }
}
</style>
