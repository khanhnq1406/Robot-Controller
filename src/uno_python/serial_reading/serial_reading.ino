#include "config.h"
#include "recvData.h"
#include "controlMotor.h"
#include "setup.h"
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(1); 
  motor1Setup();
  motor2Setup();
  motor3Setup();
}

void loop() {
  recvData();
  controlMotor();
}