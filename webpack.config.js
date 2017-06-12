var path = require("path");

module.exports = {
  entry: "./lib/js/src/index.js",
  output: {
    filename: "bundle.js",
    path: path.resolve(__dirname, "dist")
  }
};
