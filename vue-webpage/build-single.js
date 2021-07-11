// Copyright (c) 2021 drafff
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT
// 代码来自 https://zhuanlan.zhihu.com/p/38299118

const fs = require("fs");
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
fs.writeFileSync("../data/www/index.html", html);
