module.exports = {
  outputDir: "../data/www",
  productionSourceMap: false,
  chainWebpack: config => {
    config.optimization.splitChunks({
      minChunks: Infinity,
    }),
      // 内联所有图片
      config.module
        .rule("images")
        .test(/\.(png|jpe?g|gif|webp)(\?.*)?$/)
        .use("url-loader")
        .loader("url-loader")
        .options({
          limit: Infinity,
        });

    // 内联 web font
    config.module
      .rule("fonts")
      .test(/\.(woff2?|eot|ttf|otf)(\?.*)?$/i)
      .use("url-loader")
      .loader("url-loader")
      .options({
        limit: Infinity,
      });
  },
};
