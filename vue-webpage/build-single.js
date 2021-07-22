// Copyright (c) 2021 drafff
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
// 代码来自 https://zhuanlan.zhihu.com/p/38299118

const fs = require("fs");
const zlib = require("zlib");
let html = fs.readFileSync("../data/www/index.html").toString();
html = html
  // 因为css和js将内联到html中，所以此处移除preload标签
  .replace(/<link[^>]+?rel="preload"[^>]+?>/gm, "")
  // 提取link和script上的文件路径，并内联到html中
  .replace(
    /<(?:script|link)\s*(?:href|src)="\/(.+?)\.(css|js)\s*.+?>/gm,
    (str, filename, ext) => {
      let path = `../data/www/${filename}.${ext}`;
      let fileContent = fs.readFileSync(path).toString();
      if (ext === "css") {
        console.log("Insert %s success", path);
        return `<style>${fileContent}</style>`;
      } else if (ext === "js") {
        console.log("Insert %s success", path);
        return `<script>${fileContent}</script>`;
      }
      return str;
    }
  );
fs.writeFileSync("../data/www/index.html", html);
function deletDir(path) {
  var files = [];
  if (fs.existsSync(path)) {
    files = fs.readdirSync(path);
    files.forEach(function(file) {
      var curPath = path + "/" + file;
      if (fs.statSync(curPath).isDirectory()) {
        // recurse
        deletDir(curPath);
      } else {
        // delete file
        fs.unlinkSync(curPath);
        console.log("Delet %s success", curPath);
      }
    });
    fs.rmdirSync(path);
    console.log("Delet %s success", path);
  }
}
deletDir("../data/www/css");
deletDir("../data/www/js");

// 处理输入和输出的文件路径
let sourcePath = "../data/www/index.html";
let gzipPath = "../data/www/index.html.gz";
// 创建转化流
let gzip = zlib.createGzip();
// 创建可读流
let rs = fs.createReadStream(sourcePath);
// 创建可写流
let ws = fs.createWriteStream(gzipPath);
// 实现转化
rs.pipe(gzip).pipe(ws);
console.log("gzip %s success", gzipPath);
fs.unlinkSync(sourcePath);
console.log("Delet %s success", sourcePath);
