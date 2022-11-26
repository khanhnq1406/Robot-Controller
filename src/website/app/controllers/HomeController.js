const firebase = require("firebase");
class HomeController {
  // [GET] /
  index(req, res, next) {
    let theta1 = req.body.theta1;
    let theta2 = req.body.theta2;
    let theta3 = req.body.theta3;
    let theta1Number = req.body.theta1Number;
    let theta2Number = req.body.theta2Number;
    let theta3Number = req.body.theta3Number;
    console.log("theta1:", theta1);
    console.log("theta2:", theta2);
    console.log("theta3:", theta3);
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    if (theta1 === undefined || theta2 === undefined || theta3 === undefined) {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        writeThetaData(data.theta1, data.theta2, data.theta3, thetaRef);
      });
    } else {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        if (data.theta1 !== theta1Number) theta1 = theta1Number;
        if (data.theta2 !== theta2Number) theta2 = theta2Number;
        if (data.theta3 !== theta3Number) theta3 = theta3Number;
        writeThetaData(theta1, theta2, theta3, thetaRef);
      });
    }
    function writeThetaData(theta1, theta2, theta3, thetaRef) {
      thetaRef.set({
        theta1: Number(theta1),
        theta2: Number(theta2),
        theta3: Number(theta3),
      });

      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        if (data.theta1 !== theta1Number) theta1 = theta1Number;
        if (data.theta2 !== theta2Number) theta2 = theta2Number;
        if (data.theta3 !== theta3Number) theta3 = theta3Number;
        res.render("home", {
          theta1: data.theta1,
          theta2: data.theta2,
          theta3: data.theta3,
        });
      });
    }
  }

  configData(req, res, next) {
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    thetaRef.set({
      theta1: Number(180),
      theta2: Number(180),
      theta3: Number(180),
    });
    res.send("Add successfully");
  }
}
module.exports = new HomeController();
