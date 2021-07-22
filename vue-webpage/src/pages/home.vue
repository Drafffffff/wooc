<template>
  <div>
    <Topbar />
    <Scanwifi />
  </div>
</template>

<script>
import Scanwifi from "../components/scanwifi.vue";
import Topbar from "../components/Topbar.vue";
export default {
  name: "App",
  components: {
    Scanwifi,
    Topbar,
  },
};
</script>

<style lang="scss">


#app {  
  font-family: Pixel, Avenir, Helvetica, Arial, sans-serif;
  // -webkit-font-smoothing: antialiased;
  // -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  font-size: 1.5rem;
}

@font-face {
  font-family: "Pixel";
  src: url("../assets/DinkieBitmap-7pxDemo.woff2") format("woff2");
}
:root body {
  margin: 0;
  padding: 0;
  overflow-x: hidden;
  background-color: #000;
}

html{
  overflow-x: hidden;
}
img {
  image-rendering: optimizeSpeed;
  image-rendering: -moz-crisp-edges; /* Firefox */
  image-rendering: -o-crisp-edges; /* Opera */
  image-rendering: -webkit-optimize-contrast; /* Webkit (non-standard naming) */
  image-rendering: pixelated;
  -ms-interpolation-mode: nearest-neighbor; /* IE (non-standard property) */
}


</style>
