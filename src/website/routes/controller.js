const express = require("express");
const router = express.Router();

const ControlController = require("../app/controllers/ControlController");
router.get("/", ControlController.index);
router.post("/", ControlController.index);
router.get("/configData", ControlController.configData);

module.exports = router;
