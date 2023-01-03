// LED pins
const int led1 = 2;
const int led2 = 4;
#include <PID_v1.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#define MotEnable2 21  // Motor Enamble pin Runs on PWM signal
#define MotFwd2 18     // Motor Forward pin
#define MotRev2 19     // Motor Reverse pin

#define MotEnable3 17  // Motor Enamble pin Runs on PWM signal
#define MotFwd3 5      // Motor Forward pin
#define MotRev3 4      // Motor Reverse pin

#define MotEnable1 27  // Motor Enamble pin Runs on PWM signal
#define MotFwd1 12     // Motor Forward pin
#define MotRev1 14     // Motor Reverse pin

int encoderPin2A = 32;  // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin2B = 33;  // Encoder Otput 'B' must connected with intreput pin of arduino.

int encoderPin3A = 23;  // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin3B = 22;  // Encoder Otput 'B' must connected with intreput pin of arduino.

int encoderPin1A = 26;  // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin1B = 13;  // Encoder Otput 'B' must connected with intreput pin of arduino.

int sensor1Pin = 36; //SP
int sensor2Pin = 39; // SN
int sensor3Pin = 34;

int MSB3;
int LSB3;

String readString;  // This while store the user inputTheta1 data

float theta1, theta2, theta3;
float theta1Update, theta2Update, theta3Update;
float Px, Py, Pz;
float PxUpdate, PyUpdate, PzUpdate;

int starterX = 90;
int starterY = 160;
int starterZ = 165;
int flagSensor1 = 0;
int flagSensor2 = 0;
int flagSensor3 = 0;

float L1 = 114.55, L2 = 162, L3 = 130, d1 = 164.54, d2 = 69.5, d3 = 16;

int User_Input = 0;  // This while convert inputTheta1 string into integer

volatile int lastEncoded1 = 0;  // Here updated value of encoder store.
volatile int lastEncoded2 = 0;  // Here updated value of encoder store.
volatile int lastEncoded3 = 0;  // Here updated value of encoder store.

volatile long encoderValue1 = 0;  // Raw encoder value
volatile long encoderValue2 = 0;  // Raw encoder value
volatile long encoderValue3 = 0;  // Raw encoder value

// int PPR = 1600;                 // Encoder Pulse per revolution.
// int angle = 360;                // Maximum degree of motion.
int REV_Theta1 = 0;  // Set point REQUIRED ENCODER VALUE
int REV_Theta2 = 0;  // Set point REQUIRED ENCODER VALUE
int REV_Theta3 = 0;  // Set point REQUIRED ENCODER VALUE
// int lastMSB = 0;
// int lastLSB = 0;
// OK PID
double kp = 3, ki = 0.1, kd = 0.5;     // 5        // modify for optimal performance


double inputTheta1 = 0, outputTheta1 = 0, setpointTheta1 = 0;
double inputTheta2 = 0, outputTheta2 = 0, setpointTheta2 = 0;
double inputTheta3 = 0, outputTheta3 = 0, setpointTheta3 = 0;
PID PidTheta1(&inputTheta1, &outputTheta1, &setpointTheta1, kp, ki, kd, DIRECT);
PID PidTheta2(&inputTheta2, &outputTheta2, &setpointTheta2, kp, ki, kd, DIRECT);
PID PidTheta3(&inputTheta3, &outputTheta3, &setpointTheta3, kp, ki, kd, DIRECT);

unsigned long timeMillis;

bool isStarter = true;


void setup() {
    Serial.begin(115200);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.println("Setup Starting");

  pinMode(MotEnable1, OUTPUT);
  pinMode(MotFwd1, OUTPUT);
  pinMode(MotRev1, OUTPUT);

  pinMode(MotEnable2, OUTPUT);
  pinMode(MotFwd2, OUTPUT);
  pinMode(MotRev2, OUTPUT);

  pinMode(MotEnable3, OUTPUT);
  pinMode(MotFwd3, OUTPUT);
  pinMode(MotRev3, OUTPUT);

  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);

  pinMode(encoderPin1A, INPUT_PULLUP);
  pinMode(encoderPin1B, INPUT_PULLUP);

  pinMode(encoderPin2A, INPUT_PULLUP);
  pinMode(encoderPin2B, INPUT_PULLUP);

  pinMode(encoderPin3A, INPUT_PULLUP);
  pinMode(encoderPin3B, INPUT_PULLUP);

  digitalWrite(encoderPin1A, HIGH);  // turn pullup resistor on
  digitalWrite(encoderPin1B, HIGH);  // turn pullup resistor on

  digitalWrite(encoderPin2A, HIGH);  // turn pullup resistor on
  digitalWrite(encoderPin2B, HIGH);  // turn pullup resistor on

  digitalWrite(encoderPin3A, HIGH);  // turn pullup resistor on
  digitalWrite(encoderPin3B, HIGH);  // turn pullup resistor on
  // call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
   attachInterrupt(encoderPin1A, updateEncoder1, CHANGE);
  attachInterrupt(encoderPin1B, updateEncoder1, CHANGE);

  attachInterrupt(encoderPin2A, updateEncoder2, CHANGE);
  attachInterrupt(encoderPin2B, updateEncoder2, CHANGE);

  attachInterrupt(encoderPin3A, updateEncoder3, CHANGE);
  attachInterrupt(encoderPin3B, updateEncoder3, CHANGE);
  //Interrupt endsensor
  // attachInterrupt(sensor1Pin, turnOffMotor1, FALLING);
  attachInterrupt(sensor2Pin, turnOffMotor2, FALLING);
  attachInterrupt(sensor3Pin, turnOffMotor3, FALLING);

  // TCCR1B = TCCR1B & 0b11111000 | 1; // set 31KHz PWM to prevent motor noise
  PidTheta1.SetMode(AUTOMATIC);          // set PID in Auto mode
  PidTheta1.SetSampleTime(1);            // refresh rate of PID controller
  PidTheta1.SetOutputLimits(-255, 200);  // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  PidTheta2.SetMode(AUTOMATIC);          // set PID in Auto mode
  PidTheta2.SetSampleTime(1);            // refresh rate of PID controller
  PidTheta2.SetOutputLimits(-255, 255);  // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  PidTheta3.SetMode(AUTOMATIC);          // set PID in Auto mode
  PidTheta3.SetSampleTime(1);            // refresh rate of PID controller
  PidTheta3.SetOutputLimits(-255, 255);  // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  timeMillis = millis();
}

void loop() {
  Serial.println("Finding Home");
  int count1 = 0, count2 = 0, count3 = 0;
  while (flagSensor1 == 0) {
    Serial.println("Finding home 1");
    Serial.println(digitalRead(sensor1Pin));

    if(digitalRead(sensor1Pin) == 0)
    {
      flagSensor1 = 1;
      turnOffMotor1();
      count1 = 0;
      break;
    }
    if (encoderValue1 >= REV_Theta1) {
      REV_Theta1 += 100;
    }
    setpointTheta1 = REV_Theta1;  // PID while work to achive this value consider as SET value
    inputTheta1 = encoderValue1;  // data from encoder consider as a Process value
    
    PidTheta1.Compute();          // calculate new outputTheta1
    analogWrite(MotEnable1, outputTheta1);  // Enabling motor enable pin to reach the desire angle
    digitalWrite(MotFwd1, LOW);
    digitalWrite(MotRev1, HIGH);
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
    runMotor(2, 200);
  }

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
    runMotor(3, 200);
  }
  // Serial.println("Done finding home");
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
            // flagSensor1 = 1;
      
}

void turnOffMotor2() {
  digitalWrite(MotFwd2, LOW);
  digitalWrite(MotRev2, LOW);
}

void turnOffMotor3() {
  digitalWrite(MotFwd3, LOW);
  digitalWrite(MotRev3, LOW);
}
void updateEncoder1() {
  int MSB1 = digitalRead(encoderPin1A);  // MSB1 = most significant bit
  int LSB2 = digitalRead(encoderPin1B);  // LSB2 = least significant bit

  int encoded1 = (MSB1 << 1) | LSB2;          // converting the 2 pin value to single number
  int sum1 = (lastEncoded1 << 2) | encoded1;  // adding it to the previous encoded value

  if (sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011)
    encoderValue1++;
  if (sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000)
    encoderValue1--;

  lastEncoded1 = encoded1;  // store this value for next timeMillis
}

void updateEncoder2() {
  int MSB2 = digitalRead(encoderPin2A);  // MSB2 = most significant bit
  int LSB2 = digitalRead(encoderPin2B);  // LSB2 = least significant bit

  int encoded2 = (MSB2 << 1) | LSB2;          // converting the 2 pin value to single number
  int sum2 = (lastEncoded2 << 2) | encoded2;  // adding it to the previous encoded value

  if (sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011)
    encoderValue2++;
  if (sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000)
    encoderValue2--;

  lastEncoded2 = encoded2;  // store this value for next timeMillis
  // readString = "";
}

void updateEncoder3() {
  MSB3 = digitalRead(encoderPin3A);  // MSB3 = most significant bit
  LSB3 = digitalRead(encoderPin3B);  // LSB3 = least significant bit

  int encoded3 = (MSB3 << 1) | LSB3;          // converting the 2 pin value to single number
  int sum3 = (lastEncoded3 << 2) | encoded3;  // adding it to the previous encoded value

  if (sum3 == 0b1101 || sum3 == 0b0100 || sum3 == 0b0010 || sum3 == 0b1011)
    encoderValue3++;
  if (sum3 == 0b1110 || sum3 == 0b0111 || sum3 == 0b0001 || sum3 == 0b1000)
    encoderValue3--;

  lastEncoded3 = encoded3;  // store this value for next timeMillis

  // readString = "";
}