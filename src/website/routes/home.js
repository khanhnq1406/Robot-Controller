const express = require("express");
const router = express.Router();

const homeController = require("../app/controllers/HomeController");
router.get("/", homeController.index);
router.post("/", homeController.index);
router.get("/configData", homeController.configData);

module.exports = router;
