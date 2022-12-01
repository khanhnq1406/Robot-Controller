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
// //Provide the token generation process info.
// #include “addons/TokenHelper.h”
// //Provide the RTDB payload printing info and other helper functions.
// #include “addons/RTDBHelper.h”
unsigned long millisRecv = 0;

//Define Firebase Data object
FirebaseData fbdo;
 
FirebaseAuth auth;
FirebaseConfig config;
bool signupOK = false;
int theta1, theta2, theta3;
// The loop function is called in an endless loop
void firebaseData()
{
  String sendMsg;
  char sendMsgChar[50] = "";
  if ((millis() - millisRecv > 100 || millisRecv == 0)) {
    millisRecv = millis();
    if (Firebase.RTDB.getInt(&fbdo, "/Theta/theta1")) {
        theta1 = fbdo.intData();
        Serial.print("Theta 1: ");
        Serial.println(theta1);
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/Theta/theta2")) {
        theta2 = fbdo.intData();
        Serial.print("Theta 2: ");
        Serial.println(theta2);
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getInt(&fbdo, "/Theta/theta3")) {
        theta3 = fbdo.intData();
        Serial.print("Theta 3: ");
        Serial.println(theta3);
    }
    else {
      Serial.println(fbdo.errorReason());
    }
    // if (Firebase.RTDB.getString(&fbdo, "/Theta")) {
    //   // sendMsg = fbdo.stringData();
    //   Serial.println(sendMsg);
    // }
    Serial.println("--------------------------------");
  }
}