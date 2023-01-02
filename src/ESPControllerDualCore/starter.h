#include "esp32-hal-gpio.h"
void runMotor(int motor, int pwm);
void turnOffMotor1();
void turnOffMotor2();
void turnOffMotor3();
int starterX = 0;
int starterY = 150;
int starterZ = 160;
void getBeginRotation() {
  theta1 = starterX;
  theta2 = starterY;
  theta3 = starterZ;
}

void resetRotation() {
  theta1 = 0;
  theta2 = 0;
  theta3 = 0;
  REV_Theta1 = 0;
  REV_Theta2 = 0;
  REV_Theta3 = 0;
  encoderValue1 = 0;
  encoderValue2 = 0;
  encoderValue3 = 0;
  inputTheta1 = 0;
  outputTheta1 = 0;
  setpointTheta1 = 0;
  inputTheta2 = 0;
  outputTheta2 = 0;
  setpointTheta2 = 0;
  inputTheta3 = 0;
  outputTheta3 = 0;
  setpointTheta3 = 0;
  lastEncoded1 = 0;
  lastEncoded2 = 0;
  lastEncoded3 = 0;
  flagSensor1 = 0;
  flagSensor2 = 0;
  flagSensor3 = 0;
}

void start() {
  Serial.println("Finding Home");
  while (flagSensor3 == 0) {
    Serial.println("Finding home 3");
    Serial.println(digitalRead(sensor3Pin));
    if (digitalRead(sensor3Pin) == 0) {
      delay(1);
      if (digitalRead(sensor3Pin) == 0) {
        flagSensor3 = 1;
        turnOffMotor3();
        Serial.println("Done finding home 3");
      }
    }
    runMotor(3, 180);
  }
  while (flagSensor2 == 0) {
    Serial.println("Finding home 2");
    Serial.println(digitalRead(sensor2Pin));
    if (digitalRead(sensor2Pin) == 0) {
      delay(1);
      if (digitalRead(sensor2Pin) == 0) {
        flagSensor2 = 1;
        turnOffMotor2();
        Serial.println("Done finding home 2");
      }
    }
    runMotor(2, 180);
  }

  while (flagSensor1 == 0) {
    Serial.println("Finding home 1");
    Serial.println(digitalRead(sensor1Pin));

    if (digitalRead(sensor1Pin) == 0) {
      flagSensor1 = 1;
      turnOffMotor1();
      break;
    }
    if (encoderValue1 >= REV_Theta1) {
      REV_Theta1 += 50;
    }
    setpointTheta1 = REV_Theta1;  // PID while work to achive this value consider as SET value
    inputTheta1 = encoderValue1;  // data from encoder consider as a Process value

    PidTheta1.Compute();                    // calculate new outputTheta1
    analogWrite(MotEnable1, outputTheta1);  // Enabling motor enable pin to reach the desire angle
    digitalWrite(MotFwd1, LOW);
    digitalWrite(MotRev1, HIGH);
  }
}

void runMotor(int motor, int pwm) {
  if (motor == 1) {
    analogWrite(MotEnable1, 255);  // Enabling motor enable pin to reach the desire angle
    digitalWrite(MotFwd1, LOW);
    digitalWrite(MotRev1, HIGH);
  } else if (motor == 2) {
    analogWrite(MotEnable2, 200);  // Enabling motor enable pin to reach the desire angle
    digitalWrite(MotFwd2, LOW);
    digitalWrite(MotRev2, HIGH);
  } else if (motor == 3) {
    analogWrite(MotEnable3, 200);  // Enabling motor enable pin to reach the desire angle
    digitalWrite(MotFwd3, LOW);
    digitalWrite(MotRev3, HIGH);
  }
}

void turnOffMotor1() {
  digitalWrite(MotFwd1, LOW);
  digitalWrite(MotRev1, LOW);
}

void turnOffMotor2() {
  digitalWrite(MotFwd2, LOW);
  digitalWrite(MotRev2, LOW);
}

void turnOffMotor3() {
  digitalWrite(MotFwd3, LOW);
  digitalWrite(MotRev3, LOW);
}