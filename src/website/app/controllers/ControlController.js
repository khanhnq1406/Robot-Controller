const firebase = require("firebase");
class HomeController {
  // [GET] /controller
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
    let actuator = req.body.actuator;
    console.log("theta1:", theta1);
    console.log("theta2:", theta2);
    console.log("theta3:", theta3);
    console.log("theta1Number:", theta1Number);
    console.log("theta2Number:", theta2Number);
    console.log("theta3Number:", theta3Number);
    console.log("position1:", position1);
    console.log("position2:", position2);
    console.log("position3:", position3);
    console.log("position1Number:", position1Number);
    console.log("position2Number:", position2Number);
    console.log("position3Number:", position3Number);
    console.log("Actuator: ", actuator);
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    // When load new page
    if (
      theta1 === undefined &&
      theta2 === undefined &&
      theta3 === undefined &&
      position1 === undefined &&
      position2 === undefined &&
      position3 === undefined &&
      actuator === undefined
    ) {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        theta1 = data.theta1;
        theta2 = data.theta2;
        theta3 = data.theta3;
        position1 = data.position1;
        position2 = data.position2;
        position3 = data.position3;
        actuator = data.actuator;
        writeData(
          theta1,
          theta2,
          theta3,
          thetaRef,
          position1,
          position2,
          position3,
          0,
          actuator
        );
      });
    }
    // When change theta
    else if (
      theta1 !== undefined &&
      theta2 !== undefined &&
      theta3 !== undefined &&
      position1 === undefined &&
      position2 === undefined &&
      position3 === undefined
    ) {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        if (
          Number(theta1) !== Number(theta1Number) &&
          Number(theta1) === Number(data.theta1)
        )
          theta1 = theta1Number;
        if (
          Number(theta2) !== Number(theta2Number) &&
          Number(theta2) === Number(data.theta2)
        )
          theta2 = theta2Number;
        if (
          Number(theta3) !== Number(theta3Number) &&
          Number(theta3) === Number(data.theta3)
        )
          theta3 = theta3Number;

        writeData(
          theta1,
          theta2,
          theta3,
          thetaRef,
          data.position1,
          data.position2,
          data.position3,
          1,
          data.actuator
        );
      });
    }
    // When change position
    else if (
      theta1 === undefined &&
      theta2 === undefined &&
      theta3 === undefined &&
      position1 !== undefined &&
      position2 !== undefined &&
      position3 !== undefined
    ) {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        if (
          Number(position1) !== Number(position1Number) &&
          Number(position1) === Number(data.position1)
        )
          position1 = position1Number;
        if (
          Number(position2) !== Number(position2Number) &&
          Number(position2) === Number(data.position2)
        )
          position2 = position2Number;
        if (
          Number(position3) !== Number(position3Number) &&
          Number(position3) === Number(data.position3)
        )
          position3 = position3Number;

        writeData(
          data.theta1,
          data.theta2,
          data.theta3,
          thetaRef,
          position1,
          position2,
          position3,
          2,
          data.actuator
        );
      });
    }
    // When change actuator
    else if (actuator !== undefined) {
      thetaRef.once("value", (snapshot) => {
        const data = snapshot.val();
        if (data.actuator === false) actuator = true;
        else actuator = false;
        writeData(
          data.theta1,
          data.theta2,
          data.theta3,
          thetaRef,
          data.position1,
          data.position2,
          data.position3,
          0,
          actuator
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
          position3,
          0,
          actuator
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
      position3,
      isForward,
      actuator
    ) {
      if (isForward === 1) {
        let L1 = 114.55,
          L2 = 162,
          L3 = 130,
          d1 = 164.54,
          d2 = 69.5,
          d3 = 16;
        let theta1R = (theta1 * 3.14159) / 180;
        let theta2R = (theta2 * 3.14159) / 180;
        let theta3R = (theta3 * 3.14159) / 180;
        let Px =
          L1 -
          L3 *
            (Math.cos(theta1R) * Math.sin(theta2R) * Math.sin(theta3R) -
              Math.cos(theta1R) * Math.cos(theta2R) * Math.cos(theta3R)) +
          L2 * Math.cos(theta1R) * Math.cos(theta2R);
        let Py =
          Math.sin(theta1R) *
          (L3 * Math.cos(theta2R + theta3R) + L2 * Math.cos(theta2R));
        let Pz = d1 + L3 * Math.sin(theta2R + theta3R) + L2 * Math.sin(theta2R);
        position1 = Px.toFixed(2);
        position2 = Py.toFixed(2);
        position3 = Pz.toFixed(2);
      } else if (isForward === 2) {
        let L1 = 114.55,
          L2 = 162,
          L3 = 130,
          d1 = 164.54,
          d2 = 69.5,
          d3 = 16;
        let theta1Cal =
          Math.atan2(position2, position1 - L1) * (180 / 3.141592);
        const nx =
          position1 * Math.cos((theta1Cal * 3.14159) / 180) +
          position2 * Math.sin((theta1Cal * 3.14159) / 180) -
          L1 * Math.cos((theta1Cal * 3.14159) / 180);
        const ny = position3 - d1;
        const c3 =
          (Math.pow(nx, 2) +
            Math.pow(ny, 2) -
            Math.pow(L3, 2) -
            Math.pow(L2, 2)) /
          (2 * L3 * L2);
        const s3 = Math.sqrt(1 - Math.pow(c3, 2));
        let theta3Cal = Math.atan2(s3, c3) * (180 / 3.141592);
        const c2 =
          (nx * (L3 * c3 + L2) + L3 * s3 * ny) /
          (Math.pow(L3 * c3 + L2, 2) + Math.pow(L3, 2) * Math.pow(s3, 2));
        const s2 =
          (ny * (L3 * c3 + L2) - L3 * s3 * nx) /
          (Math.pow(L3 * c3 + L2, 2) + Math.pow(L3, 2) * Math.pow(s3, 2));
        let theta2Cal = Math.atan2(s2, c2) * (180 / 3.141592);
        theta1 = theta1Cal.toFixed(2);
        theta2 = theta2Cal.toFixed(2);
        theta3 = theta3Cal.toFixed(2);
      }
      try {
        thetaRef.once("value", (snapshot) => {
          const data = snapshot.val();
          thetaRef.set({
            theta1: Number(theta1),
            theta2: Number(theta2),
            theta3: Number(theta3),
            position1: Number(position1),
            position2: Number(position2),
            position3: Number(position3),
            actuator: actuator,
            goHome: data.goHome,
          });
        });
        res.render("controller", {
          theta1: theta1,
          theta2: theta2,
          theta3: theta3,
          position1: position1,
          position2: position2,
          position3: position3,
          isWrongPosition: false,
          actuator: actuator,
        });
      } catch {
        thetaRef.once("value", (snapshot) => {
          const data = snapshot.val();
          res.render("controller", {
            theta1: data.theta1,
            theta2: data.theta2,
            theta3: data.theta3,
            position1: data.position1,
            position2: data.position2,
            position3: data.position3,
            isWrongPosition: true,
            actuator: data.actuator,
            goHome: data.goHome,
          });
        });
      }
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
      actuator: Number(0),
    });
    res.send("Add successfully");
  }

  savePosition(req, res, next) {
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    let positionRef = database.ref("PositionSaved");
    let positionSaved = req.query.save;
    thetaRef.once("value", (snapshot) => {
      const data = snapshot.val();
      positionRef.child(positionSaved).set({
        theta1: data.theta1,
        theta2: data.theta2,
        theta3: data.theta3,
        position1: data.position1,
        position2: data.position2,
        position3: data.position3,
        actuator: data.actuator,
      });
    });
    res.redirect("/controller");
  }

  goPosition(req, res, next) {
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    let positionRef = database.ref("PositionSaved");
    let positionSaved = req.query.go;
    positionRef.child(positionSaved).once("value", (snapshot) => {
      const data = snapshot.val();
      thetaRef.set({
        theta1: data.theta1,
        theta2: data.theta2,
        theta3: data.theta3,
        position1: data.position1,
        position2: data.position2,
        position3: data.position3,
        actuator: data.actuator,
        goHome: data.goHome,
      });
    });
    res.redirect("/controller");
  }
  goHome(req, res, next) {
    var database = firebase.database();
    let thetaRef = database.ref("Theta");
    thetaRef.set({
      theta1: Number(0),
      theta2: Number(0),
      theta3: Number(0),
      position1: Number(406.55),
      position2: Number(0),
      position3: Number(164.54),
      actuator: Number(0),
      goHome: true,
    });
    res.redirect("/controller");
  }
}
module.exports = new HomeController();
