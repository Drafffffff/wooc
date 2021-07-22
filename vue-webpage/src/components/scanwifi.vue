<template>
  <div class="scan">
    <button
      :class="{ scanButton: !isScaned, refreshButton: isScaned }"
      @click.stop="scan"
    >
      <span>{{ buttonText }}</span>
      <span>
        <transition name="fade" mode="out-in">
          <img
            v-if="isStartLoading"
            src="../assets/img/icon/refresh.png"
            alt="refresh"
            class="refresh"
          />
          <img v-else src="../assets/img/icon/smile.png" alt="smile" />
        </transition>
      </span>
    </button>
    <transition-group class="wifi-list" name="list-complete" tag="ul">
      <li
        v-for="(wifiInfo, index) in wifiList"
        :key="index"
        @click="selectSSID(wifiInfo)"
        :data-index="index"
      >
        <p class="SSID">{{ wifiInfo.SSID }}</p>
        <img :src="calRSSI(wifiInfo.RSSI)" alt="RSSI" />
      </li>
    </transition-group>
    <div class="modal" v-if="isShowmodal">
      <p>{{ SSID }}</p>
      <input v-model="password" type="password" />
      <button @click="submit">连接</button>
    </div>
  </div>
</template>
<script>
import wifi3 from "../assets/img/icon/wifi-3.png";
import wifi2 from "../assets/img/icon/wifi-2.png";
import wifi1 from "../assets/img/icon/wifi-1.png";
import wifi0 from "../assets/img/icon/wifi-0.png";
export default {
  setup() {},
  data() {
    return {
      isShowmodal: false,
      isStartLoading: false,
      isScaned: false,
      wifiList: {},
      SSID: "",
      password: "",
      buttonText: "扫描WiFi",
    };
  },
  beforeMount() {},
  methods: {
    //TODO:添加扫描错误状态
    //TODO:添加逐个进入逐个推出 
    scan() {
      this.wifiList = {};
      this.isStartLoading = true;
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
          this.isStartLoading = false;
          this.buttonText = "刷新";
          this.isScaned = true;
        });
    },
    selectSSID(wifiobj) {
      setTimeout(() => (this.isShowmodal = true), 0.3 * 1000);

      this.SSID = wifiobj.SSID;
      console.log(wifiobj.SSID);
    },
    submit() {
      this.isShowmodal = false;
      console.log(this.password);
      this.password = "";
    },
    calRSSI(RSSI) {
      if (RSSI > -75) {
        return wifi3;
      } else if (RSSI > -85) {
        return wifi2;
      } else if (RSSI > -95) {
        return wifi1;
      } else {
        return wifi0;
      }
    },
  },
};
</script>

<style lang="scss">
@mixin btn($bgc, $height: 6px, $dark: darken($bgc, 10%)) {
  background-color: $bgc;
  font-family: Pixel;
  width: 100%;
  height: 4rem;
  border-radius: 0;
  position: relative;
  top: -$height;
  border: 0;
  transition: all 40ms linear;
  &:active:focus,
  &:focus:hover,
  &:focus {
    outline: medium none;
  }

  box-shadow: 0 $height 0 0 $dark;
  &:active,
  &.active {
    background-color: lighten($bgc, 5%);
    box-shadow: 0 1px 1px 0px lighten($bgc, 10%);
    top: 0;
  }
}
.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.1s ease;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
}
.list-complete-item {
  transition: all 1s ease;
}
.list-complete-enter-from,
.list-complete-leave-to {
  opacity: 0;
  transform: translateY(80px);
}
.scan {
  padding: 1rem 2rem;
  max-width: 40rem;
  margin: auto;
}

@keyframes self-rotation {
  from {
    transform: rotate(0deg);
  }
  to {
    transform: rotate(360deg);
  }
}

.scanButton {
  @include btn(#de626e);

  font-size: 1.5rem;
  color: white;
  margin-top: 20px;
  img {
    height: 1.4rem;
    margin-left: 0.5rem;
    transform: translateY(4px);
  }
  .refresh {
    animation-duration: 1s;
    animation-name: self-rotation;
    animation-iteration-count: infinite;
  }
}

.refreshButton {
  @extend .scanButton;
  @include btn(#3f9e79);
}

.wifi-list {
  overflow: scroll;
  overflow-x: hidden;
  margin: 0;
  margin-block: 0;
  list-style-type: none;
  padding-inline-start: 0;
  margin-top: 1rem;
  li {
    display: flex;
    align-items: center;
    justify-content: space-between;
    cursor: pointer;
    margin-top: 1.5rem;
    color: white;
    text-align: center;

    @include btn(#26233b, 6px, #64615c);
    p {
      margin: 0;
      margin-left: 2rem;
    }
    img {
      margin-right: 1rem;
      height: 1.4rem;
    }
  }
}
.modal {
  position: absolute;
  width: 100vw;
  height: 100vh;
  background-color: rgba(0, 0, 0, 0.564);
  top: 0;
  left: 0;
  color: white;
  display: flex;
  justify-content: center;
  align-items: center;
  flex-direction: column;
  button {
    font-family: Pixel, Avenir, Helvetica, Arial, sans-serif;
  }
}
</style>
