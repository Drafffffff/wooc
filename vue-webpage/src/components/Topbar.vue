<template>
  <div class="topbar">
    <div class="logo">
      <img src="../assets/img/wocLOGO.png" alt="logo" />
    </div>
    <div class="titles">
      <p class="titlezh">在线配网工具</p>
      <p class="titleen">WIFI Online Config</p>
    </div>
  </div>
</template>
<script>
export default {
  setup() {},
};
</script>
<style lang="scss">
.topbar {
  width: 100%;
  background-color: #26233b;
  border-bottom: 0.8rem solid;
  display: flex;
  flex-direction: row;
  padding: 10px;
  div {
    display: flex;
    color: #3c9c77;
  }
  .logo {
    img {
      width: 100px;
      padding:10px
    }
  }
  .titles {
    flex-direction: column;
    margin: auto 10px;
    p {
      text-align: left;
      margin: 0;
    }
    .titleen{
      font-size: 1rem;
    }
  }
}
</style>
