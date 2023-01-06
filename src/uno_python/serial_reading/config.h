#include <PID_v1.h>
double kp = 3, ki = 0, kd = 0.1;
  
// Motor 1
#define MotEnable1 5
#define MotFwd1 6
#define MotRev1 7
int encoderPin1A = 2;
int encoderPin1B = 3;
volatile int lastEncoded1 = 0;
volatile long encoderValue1 = 0;
double inputTheta1 = 0, outputTheta1 = 0, setpointTheta1 = 0;
PID PidTheta1(&inputTheta1, &outputTheta1, &setpointTheta1, kp, ki, kd, DIRECT);
int REV_Theta1 = 0;

// Motor 2
#define MotEnable2 8
#define MotFwd2 9
#define MotRev2 10
int encoderPin2A = 20;
int encoderPin2B = 21;
volatile int lastEncoded2 = 0;
volatile long encoderValue2 = 0;
double inputTheta2 = 0, outputTheta2 = 0, setpointTheta2 = 0;
PID PidTheta2(&inputTheta2, &outputTheta2, &setpointTheta2, kp, ki, kd, DIRECT);
int REV_Theta2 = 0;

// Motor 3
#define MotEnable3 11
#define MotFwd3 12
#define MotRev3 13
int encoderPin3A = 18;
int encoderPin3B = 19;
volatile int lastEncoded3 = 0;
volatile long encoderValue3 = 0;
double inputTheta3 = 0, outputTheta3 = 0, setpointTheta3 = 0;
PID PidTheta3(&inputTheta3, &outputTheta3, &setpointTheta3, kp, ki, kd, DIRECT);
int REV_Theta3 = 0;

// Receive data
float theta[3];
int indexTheta = 0, indx = 0;
String buff;
char buffer[50];