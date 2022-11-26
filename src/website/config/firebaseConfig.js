const firebase = require("firebase");
const express = require("express");
const app = express();

const firebaseConfig = {
  apiKey: "AIzaSyAGSoXB8u6OYhbO7Jb_YHMrQTOyec7Tcvo",
  authDomain: "robot-controller-71ebb.firebaseapp.com",
  databaseURL:
    "https://robot-controller-71ebb-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "robot-controller-71ebb",
  storageBucket: "robot-controller-71ebb.appspot.com",
  messagingSenderId: "1004826420259",
  appId: "1:1004826420259:web:7bb1325f120eccd93abd96",
  measurementId: "G-VYBTEBENJ6",
};

// Initialize Firebase
firebase.initializeApp(firebaseConfig);

const firebaseDB = firebase.database();

console.log(`Connect successfully`);
module.exports = { firebaseDB };
