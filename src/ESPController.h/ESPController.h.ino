#include <PID_v1.h>
#define MotEnable 17             // Motor Enamble pin Runs on PWM signal
#define MotFwd 5                // Motor Forward pin
#define MotRev 18                // Motor Reverse pin
String readString;              // This while store the user inputTheta1 data
int User_Input = 0;             // This while convert inputTheta1 string into integer
int encoderPin1 = 2;            // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin2 = 15;            // Encoder Otput 'B' must connected with intreput pin of arduino.
volatile int lastEncoded = 0;   // Here updated value of encoder store.
volatile long encoderValue = 0; // Raw encoder value
int PPR = 1600;                 // Encoder Pulse per revolution.
int angle = 360;                // Maximum degree of motion.
int REV = 0;                    // Set point REQUIRED ENCODER VALUE
int lastMSB = 0;
int lastLSB = 0;
double kp = 3, ki = 0, kd = 0.1; // 5        // modify for optimal performance
double inputTheta1 = 0, outputTheta1 = 0, setpointTheta1 = 0;
double inputTheta2 = 0, outputTheta2 = 0, setpointTheta2 = 0;
double inputTheta3 = 0, outputTheta3 = 0, setpointTheta3 = 0;
PID PidTheta1(&inputTheta1, &outputTheta1, &setpointTheta1, kp, ki, kd, DIRECT);
PID PidTheta2(&inputTheta2, &outputTheta2, &setpointTheta2, kp, ki, kd, DIRECT);
PID PidTheta3(&inputTheta3, &outputTheta3, &setpointTheta3, kp, ki, kd, DIRECT);

unsigned long timeMillis;
void setup()
{
  pinMode(MotEnable, OUTPUT);
  pinMode(MotFwd, OUTPUT);
  pinMode(MotRev, OUTPUT);
  Serial.begin(9600); // initialize serial comunication

  pinMode(encoderPin1, INPUT_PULLUP);
  pinMode(encoderPin2, INPUT_PULLUP);

  digitalWrite(encoderPin1, HIGH); // turn pullup resistor on
  digitalWrite(encoderPin2, HIGH); // turn pullup resistor on

  // call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(encoderPin1, updateEncoder, CHANGE);
  attachInterrupt(encoderPin2, updateEncoder, CHANGE);

  // TCCR1B = TCCR1B & 0b11111000 | 1; // set 31KHz PWM to prevent motor noise
  PidTheta1.SetMode(AUTOMATIC);         // set PID in Auto mode
  PidTheta1.SetSampleTime(1);           // refresh rate of PID controller
  PidTheta1.SetOutputLimits(-125, 125); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  PidTheta2.SetMode(AUTOMATIC);         // set PID in Auto mode
  PidTheta2.SetSampleTime(1);           // refresh rate of PID controller
  PidTheta2.SetOutputLimits(-125, 125); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  PidTheta3.SetMode(AUTOMATIC);         // set PID in Auto mode
  PidTheta3.SetSampleTime(1);           // refresh rate of PID controller
  PidTheta3.SetOutputLimits(-125, 125); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  timeMillis = millis();
}

void loop()
{

  while (Serial.available())
  {                         // Check if the serial data is available.
    delay(3);               // a small delay
    char c = Serial.read(); // storing inputTheta1 data
    readString += c;        // accumulate each of the characters in readString
  }

  if (readString.length() > 0)
  { // Verify that the variable contains information

    Serial.println(readString.toInt()); // printing the inputTheta1 data in integer form
    User_Input = readString.toInt();    // here inputTheta1 data is store in integer form
  }
  REV = map(User_Input, 0, 360, 0, 6000); // mapping degree into pulse 130RPM: 2000, 247: 920
  if ((unsigned long)(millis() - timeMillis) > 500)
  {
    Serial.print("this is REV - ");
    Serial.println(REV); // printing REV value
    Serial.print("encoderValue - ");
    Serial.println(encoderValue);
    timeMillis = millis();
  }
  setpointTheta1 = REV;       // PID while work to achive this value consider as SET value
  inputTheta1 = encoderValue; // data from encoder consider as a Process value

  PidTheta1.Compute(); // calculate new outputTheta1
  pwmOut(outputTheta1);
}
void pwmOut(int out)
{
  if (out > 0)
  {                              // if REV > encoderValue motor move in forward direction.
    analogWrite(MotEnable, out); // Enabling motor enable pin to reach the desire angle
    forward();                   // calling motor to move forward
  }
  else
  {
    analogWrite(MotEnable, abs(out)); // if REV < encoderValue motor move in forward direction.
    reverse();                        // calling motor to move reverse
  }
  readString = ""; // Cleaning User inputTheta1, ready for new Input
}
void updateEncoder()
{
  int MSB = digitalRead(encoderPin1); // MSB = most significant bit
  int LSB = digitalRead(encoderPin2); // LSB = least significant bit

  int encoded = (MSB << 1) | LSB;         // converting the 2 pin value to single number
  int sum = (lastEncoded << 2) | encoded; // adding it to the previous encoded value

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderValue++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderValue--;

  lastEncoded = encoded; // store this value for next timeMillis
}

void forward()
{
  digitalWrite(MotFwd, HIGH);
  digitalWrite(MotRev, LOW);
}

void reverse()
{
  digitalWrite(MotFwd, LOW);
  digitalWrite(MotRev, HIGH);
}
void finish()
{
  digitalWrite(MotFwd, LOW);
  digitalWrite(MotRev, LOW);
}