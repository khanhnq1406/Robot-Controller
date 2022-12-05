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
    let position1 = req.body.position1;
    let position2 = req.body.position2;
    let position3 = req.body.position3;
    let position1Number = req.body.position1Number;
    let position2Number = req.body.position2Number;
    let position3Number = req.body.position3Number;
    console.log("theta1:", theta1);
    console.log("theta2:", theta2);
    console.log("theta3:", theta3);
    console.log("theta1Number:", theta1Number);
    console.log("theta2Number:", theta2Number);
    console.log("theta3Number:", theta3Number);
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    if (theta1 === undefined && theta2 === undefined && theta3 === undefined) {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        theta1 = data.theta1;
        theta2 = data.theta2;
        theta3 = data.theta3;
        position1 = data.position1;
        position2 = data.position2;
        position3 = data.position3;
        writeData(
          theta1,
          theta2,
          theta3,
          thetaRef,
          position1,
          position2,
          position3
        );
      });
    } else {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        if (theta1 !== theta1Number && Number(theta1) === data.theta1)
          theta1 = theta1Number;
        if (theta2 !== theta2Number && Number(theta2) === data.theta2)
          theta2 = theta2Number;
        if (theta3 !== theta3Number && Number(theta3) === data.theta3)
          theta3 = theta3Number;
        if (
          position1 !== position1Number &&
          Number(position1) === data.position1
        )
          position1 = position1Number;
        if (
          position2 !== position2Number &&
          Number(position2) === data.position2
        )
          position2 = position2Number;
        if (
          position3 !== position3Number &&
          Number(position3) === data.position3
        )
          position3 = position3Number;
        writeData(
          theta1,
          theta2,
          theta3,
          thetaRef,
          position1,
          position2,
          position3
        );
      });
    }
    function writeData(
      theta1,
      theta2,
      theta3,
      thetaRef,
      position1,
      position2,
      position3
    ) {
      thetaRef.set({
        theta1: Number(theta1),
        theta2: Number(theta2),
        theta3: Number(theta3),
        position1: Number(position1),
        position2: Number(position2),
        position3: Number(position3),
      });
      res.render("controller", {
        theta1: theta1,
        theta2: theta2,
        theta3: theta3,
        position1: position1,
        position2: position2,
        position3: position3,
      });
    }
  }

  configData(req, res, next) {
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    thetaRef.set({
      theta1: Number(0),
      theta2: Number(0),
      theta3: Number(0),
      position1: Number(0),
      position2: Number(0),
      position3: Number(0),
    });
    res.send("Add successfully");
  }
}
module.exports = new HomeController();
