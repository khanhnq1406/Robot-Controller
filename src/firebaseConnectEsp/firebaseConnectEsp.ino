#include "Arduino.h"
#include <string.h>
#include <stdlib.h>  
#include "config.h"
#include <iostream>
// ---------- FireBase --------------
#include <FirebaseESP8266.h>
#include  <ESP8266WiFi.h>
// ---------- communicates  --------------
#include<SoftwareSerial.h>

FirebaseData fbdo;
unsigned long millisRecv = 0;

// Communication
SoftwareSerial SUART(5, 4);  //D2, D1 = SRX, STX

//The setup function is called once at startup of the sketch
void setup()
{
  Serial.begin(9600);
  SUART.begin(115200);
  delay(1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println ("");
  Serial.println ("Da ket noi WiFi!");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  delay(1000);
}

// The loop function is called in an endless loop
void loop()
{
  String sendMsg;
  int theta1, theta2, theta3;
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
    sendMsg = theta1 + '~' + theta2 + '~' + theta3 + '>';
    strcat(sendMsgChar,sendMsg.c_str());
    Serial.println(sendMsgChar);
    // SUART.print(sendMsgChar); 
    SUART.print(theta1); 
    // SUART.print('~'); 
    SUART.print(theta2); 
    // SUART.print('~'); 
    SUART.print(theta3); 
    SUART.print('>'); 
  }
}