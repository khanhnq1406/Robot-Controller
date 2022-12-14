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


void updateData() {
  Firebase.RTDB.setFloat (&fbdo,"/Theta/theta1/", theta1);
  Firebase.RTDB.setFloat (&fbdo,"/Theta/theta2/", theta2);
  Firebase.RTDB.setFloat (&fbdo,"/Theta/theta3/", theta3);
  Firebase.RTDB.setFloat (&fbdo,"/Theta/position1/", Px);
  Firebase.RTDB.setFloat (&fbdo,"/Theta/position2/", Py);
  Firebase.RTDB.setFloat (&fbdo,"/Theta/position3/", Pz);
}  
void firebaseData()
{
  String sendMsg;
  char sendMsgChar[50] = "";
  if ((millis() - millisRecv > 100 || millisRecv == 0)) {
    millisRecv = millis();
    if (Firebase.RTDB.getFloat(&fbdo, "/Theta/theta1")) {
        theta1Update = fbdo.floatData();
        if (theta1 != theta1Update) {
          theta1 = theta1Update;
          // forwardKinematic();
          // updateData();
        }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getFloat(&fbdo, "/Theta/theta2")) {
        theta2Update = fbdo.floatData();
        if (theta2 != theta2Update) {
          theta2 = theta2Update;
          // forwardKinematic();
          // updateData();
        }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getFloat(&fbdo, "/Theta/theta3")) {
        theta3Update = fbdo.floatData();
        if (theta3 != theta3Update) {
          theta3 = theta3Update;
          // forwardKinematic();
          // updateData();
        }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getFloat(&fbdo, "/Theta/position1")) {
        PxUpdate = fbdo.floatData();
        if (Px != PxUpdate) {
          Px = PxUpdate;
          // inverseKinematic();
          // updateData();
        }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getFloat(&fbdo, "/Theta/position2")) {
        PyUpdate = fbdo.floatData();
        if (Py != PyUpdate) {
          Py = PyUpdate;
          // inverseKinematic();
          // updateData();
        }
    }
    else {
      Serial.println(fbdo.errorReason());
    }

    if (Firebase.RTDB.getFloat(&fbdo, "/Theta/position3")) {
        PzUpdate = fbdo.floatData();
        if (Pz != PzUpdate) {
          Pz = PzUpdate;
          // inverseKinematic();
          // updateData();
        }
    }
    else {
      Serial.println(fbdo.errorReason());
    }
  }
}