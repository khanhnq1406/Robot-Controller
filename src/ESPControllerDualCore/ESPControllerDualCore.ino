TaskHandle_t Task1;
TaskHandle_t Task2;

// LED pins
const int led1 = 2;
const int led2 = 4;
#include <PID_v1.h>
#include "soc/timer_group_struct.h"
#include "soc/timer_group_reg.h"

#define MotEnable1 21             // Motor Enamble pin Runs on PWM signal
#define MotFwd1 18                // Motor Forward pin
#define MotRev1 19                // Motor Reverse pin

#define MotEnable2 17             // Motor Enamble pin Runs on PWM signal
#define MotFwd2 5                // Motor Forward pin
#define MotRev2 4                // Motor Reverse pin

#define MotEnable3 27             // Motor Enamble pin Runs on PWM signal
#define MotFwd3 14                // Motor Forward pin
#define MotRev3 12                // Motor Reverse pin

int MSB3;
int LSB3;

String readString;              // This while store the user inputTheta1 data

int theta1, theta2, theta3;
int theta1Update, theta2Update, theta3Update;

int User_Input = 0;             // This while convert inputTheta1 string into integer
int encoderPin1A = 32;            // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin1B = 33;            // Encoder Otput 'B' must connected with intreput pin of arduino.

int encoderPin2A = 22;            // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin2B = 23;            // Encoder Otput 'B' must connected with intreput pin of arduino.

int encoderPin3A = 13;            // Encoder Output 'A' must connected with intreput pin of arduino.
int encoderPin3B = 26;            // Encoder Otput 'B' must connected with intreput pin of arduino.
volatile int lastEncoded1 = 0;   // Here updated value of encoder store.
volatile int lastEncoded2 = 0;   // Here updated value of encoder store.
volatile int lastEncoded3 = 0;   // Here updated value of encoder store.

volatile long encoderValue1 = 0; // Raw encoder value
volatile long encoderValue2 = 0; // Raw encoder value
volatile long encoderValue3 = 0; // Raw encoder value

// int PPR = 1600;                 // Encoder Pulse per revolution.
// int angle = 360;                // Maximum degree of motion.
int REV_Theta1 = 0;                    // Set point REQUIRED ENCODER VALUE
int REV_Theta2 = 0;                    // Set point REQUIRED ENCODER VALUE
int REV_Theta3 = 0;                    // Set point REQUIRED ENCODER VALUE
// int lastMSB = 0;
// int lastLSB = 0;
double kp = 3, ki = 0, kd = 0.1; // 5        // modify for optimal performance
double kp3 = 3, ki3 = 0, kd3 = 0.1; // 5        // modify for optimal performance
double inputTheta1 = 0, outputTheta1 = 0, setpointTheta1 = 0;
double inputTheta2 = 0, outputTheta2 = 0, setpointTheta2 = 0;
double inputTheta3 = 0, outputTheta3 = 0, setpointTheta3 = 0;
PID PidTheta1(&inputTheta1, &outputTheta1, &setpointTheta1, kp, ki, kd, DIRECT);
PID PidTheta2(&inputTheta2, &outputTheta2, &setpointTheta2, kp, ki, kd, DIRECT);
PID PidTheta3(&inputTheta3, &outputTheta3, &setpointTheta3, kp, ki, kd, DIRECT);

unsigned long timeMillis;
#include "serialInput.h"
#include "display.h"
#include "firebaseConnectEsp.h"
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

  pinMode(encoderPin1A, INPUT_PULLUP);
  pinMode(encoderPin1B, INPUT_PULLUP);
  
  pinMode(encoderPin2A, INPUT_PULLUP);
  pinMode(encoderPin2B, INPUT_PULLUP);

  pinMode(encoderPin3A, INPUT_PULLUP);
  pinMode(encoderPin3B, INPUT_PULLUP);

  digitalWrite(encoderPin1A, HIGH); // turn pullup resistor on
  digitalWrite(encoderPin1B, HIGH); // turn pullup resistor on

  digitalWrite(encoderPin2A, HIGH); // turn pullup resistor on
  digitalWrite(encoderPin2B, HIGH); // turn pullup resistor on

  digitalWrite(encoderPin3A, HIGH); // turn pullup resistor on
  digitalWrite(encoderPin3B, HIGH); // turn pullup resistor on
  // call updateEncoder() when any high/low changed seen
  // on interrupt 0 (pin 2), or interrupt 1 (pin 3)
  attachInterrupt(encoderPin1A, updateEncoder1, CHANGE);
  attachInterrupt(encoderPin1B, updateEncoder1, CHANGE);

  attachInterrupt(encoderPin2A, updateEncoder2, CHANGE);
  attachInterrupt(encoderPin2B, updateEncoder2, CHANGE);

  attachInterrupt(encoderPin3A, updateEncoder3, CHANGE);
  attachInterrupt(encoderPin3B, updateEncoder3, CHANGE);
  // TCCR1B = TCCR1B & 0b11111000 | 1; // set 31KHz PWM to prevent motor noise
  PidTheta1.SetMode(AUTOMATIC);         // set PID in Auto mode
  PidTheta1.SetSampleTime(1);           // refresh rate of PID controller
  PidTheta1.SetOutputLimits(-255, 255); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  PidTheta2.SetMode(AUTOMATIC);         // set PID in Auto mode
  PidTheta2.SetSampleTime(1);           // refresh rate of PID controller
  PidTheta2.SetOutputLimits(-255, 255); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.

  PidTheta3.SetMode(AUTOMATIC);         // set PID in Auto mode
  PidTheta3.SetSampleTime(1);           // refresh rate of PID controller
  PidTheta3.SetOutputLimits(-255, 255); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  
  timeMillis = millis();
  // Firebase
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Dang ket noi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println ("");
  Serial.println ("Da ket noi WiFi!");
  Serial.println(WiFi.localIP());

  /* Assign the api key (required) */
  config.api_key = API_KEY;
 
  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;
 
  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
 
  /* Assign the callback function for the long running token generation task */
  // config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
   
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  delay(1000);
  Serial.println("Setup Done");
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){  
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;
    REV_Theta1 = map(theta1, 0, 360, 0, 6000); // mapping degree into pulse 130RPM: 2000, 247: 920
    REV_Theta2 = map(theta2, 0, 360, 0, 7500); // mapping degree into pulse 130RPM: 2000, 247: 920
    REV_Theta3 = map(theta3, 0, 360, 0, 3450); // mapping degree into pulse 130RPM: 2000, 247: 920

    setpointTheta1 = REV_Theta1;       // PID while work to achive this value consider as SET value
    inputTheta1 = encoderValue1; // data from encoder consider as a Process value

    setpointTheta2 = REV_Theta2;       // PID while work to achive this value consider as SET value
    inputTheta2 = encoderValue2; // data from encoder consider as a Process value

    setpointTheta3 = REV_Theta3;       // PID while work to achive this value consider as SET value
    inputTheta3 = encoderValue3; // data from encoder consider as a Process value
    PidTheta1.Compute(); // calculate new outputTheta1
    PidTheta2.Compute(); // calculate new outputTheta1
    PidTheta3.Compute(); // calculate new outputTheta1
    pwmOut(outputTheta1, outputTheta2, outputTheta3);
  } 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());
  for(;;){
    TIMERG0.wdt_wprotect=TIMG_WDT_WKEY_VALUE;
    TIMERG0.wdt_feed=1;
    TIMERG0.wdt_wprotect=0;
    display();
    firebaseData();
  }
}

void loop() {
  delay(1);
}
void pwmOut(int out1, int out2, int out3)
{
  if (out1 > 0)
  {                              // if REV_Theta1 > encoderValue1 motor move in forward direction.
    analogWrite(MotEnable1, out1); // Enabling motor enable pin to reach the desire angle
    forward1();                   // calling motor to move forward
  }
  else
  {
    analogWrite(MotEnable1, abs(out1)); // if REV_Theta1 < encoderValue1 motor move in forward direction.
    reverse1();                        // calling motor to move reverse
  }

  if (out2 > 0)
  {                              // if REV_Theta1 > encoderValue1 motor move in forward direction.
    analogWrite(MotEnable2, out2); // Enabling motor enable pin to reach the desire angle
    forward2();                   // calling motor to move forward
  }
  else
  {
    analogWrite(MotEnable2, abs(out2)); // if REV_Theta1 < encoderValue1 motor move in forward direction.
    reverse2();                        // calling motor to move reverse
  }

  if (out3 > 0)
  {                              // if REV_Theta1 > encoderValue1 motor move in forward direction.
    analogWrite(MotEnable3, out3); // Enabling motor enable pin to reach the desire angle
    forward3();                   // calling motor to move forward
  }
  else
  {
    analogWrite(MotEnable3, abs(out3)); // if REV_Theta1 < encoderValue1 motor move in forward direction.
    reverse3();                        // calling motor to move reverse
  }
  readString = "";

}
void updateEncoder1()
{
  int MSB1 = digitalRead(encoderPin1A); // MSB1 = most significant bit
  int LSB2 = digitalRead(encoderPin1B); // LSB2 = least significant bit

  int encoded1 = (MSB1 << 1) | LSB2;         // converting the 2 pin value to single number
  int sum1 = (lastEncoded1 << 2) | encoded1; // adding it to the previous encoded value

  if (sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011)
    encoderValue1++;
  if (sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000)
    encoderValue1--;

  lastEncoded1 = encoded1; // store this value for next timeMillis
}

void updateEncoder2()
{
  int MSB2 = digitalRead(encoderPin2A); // MSB2 = most significant bit
  int LSB2 = digitalRead(encoderPin2B); // LSB2 = least significant bit

  int encoded2 = (MSB2 << 1) | LSB2;         // converting the 2 pin value to single number
  int sum2 = (lastEncoded2 << 2) | encoded2; // adding it to the previous encoded value

  if (sum2 == 0b1101 || sum2 == 0b0100 || sum2 == 0b0010 || sum2 == 0b1011)
    encoderValue2++;
  if (sum2 == 0b1110 || sum2 == 0b0111 || sum2 == 0b0001 || sum2 == 0b1000)
    encoderValue2--;

  lastEncoded2 = encoded2; // store this value for next timeMillis
  // readString = "";

}

void updateEncoder3()
{
  MSB3 = digitalRead(encoderPin3A); // MSB3 = most significant bit
  LSB3 = digitalRead(encoderPin3B); // LSB3 = least significant bit

  int encoded3 = (MSB3 << 1) | LSB3;         // converting the 2 pin value to single number
  int sum3 = (lastEncoded3 << 2) | encoded3; // adding it to the previous encoded value

  if (sum3 == 0b1101 || sum3 == 0b0100 || sum3 == 0b0010 || sum3 == 0b1011)
    encoderValue3++;
  if (sum3 == 0b1110 || sum3 == 0b0111 || sum3 == 0b0001 || sum3 == 0b1000)
    encoderValue3--;

  lastEncoded3 = encoded3; // store this value for next timeMillis
  
  // readString = "";

}

void forward1()
{
  digitalWrite(MotFwd1, HIGH);
  digitalWrite(MotRev1, LOW);
}

void reverse1()
{
  digitalWrite(MotFwd1, LOW);
  digitalWrite(MotRev1, HIGH);
}
void finish1()
{
  digitalWrite(MotFwd1, LOW);
  digitalWrite(MotRev1, LOW);
}

void forward2()
{
  digitalWrite(MotFwd2, HIGH);
  digitalWrite(MotRev2, LOW);
}

void reverse2()
{
  digitalWrite(MotFwd2, LOW);
  digitalWrite(MotRev2, HIGH);
}
void finish2()
{
  digitalWrite(MotFwd2, LOW);
  digitalWrite(MotRev2, LOW);
}

void forward3()
{
  digitalWrite(MotFwd3, HIGH);
  digitalWrite(MotRev3, LOW);
}

void reverse3()
{
  digitalWrite(MotFwd3, LOW);
  digitalWrite(MotRev3, HIGH);
}
void finish3()
{
  digitalWrite(MotFwd3, LOW);
  digitalWrite(MotRev3, LOW);
}
