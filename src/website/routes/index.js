const homeRouter = require("./home");
const controllerRouter = require("./controller");

function route(app) {
  app.use("/", homeRouter);
  app.use("/controller", controllerRouter);
}
module.exports = route;
