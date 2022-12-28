#include "Arduino.h"
#include <string.h>
#include <stdlib.h>  
#include "config.h"
#include <iostream>
// ---------- FireBase --------------
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif

// Include Firebase library (this library)
#include <Firebase_ESP_Client.h>

unsigned long millisRecv = 0;

//Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;


void firebaseData()
{
  String sendMsg;
  char sendMsgChar[50] = "";
  if ((millis() - millisRecv > 500 || millisRecv == 0)) {
    millisRecv = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/Theta/theta1")) {
        theta1Update = fbdo.intData();
        if (theta1 != theta1Update)
          theta1 = theta1Update;
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/Theta/theta2")) {
        theta2Update = fbdo.intData();
        if (theta2 != theta2Update)
          theta2 = theta2Update;
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/Theta/theta3")) {
        theta3 = fbdo.intData();
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}