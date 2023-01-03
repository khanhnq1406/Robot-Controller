#include <util/atomic.h> // For the ATOMIC_BLOCK macro
// Motor1
#define ENCA 21 // green
#define ENCB 22 // yellow
#define PWM 2
#define IN2 4
#define IN1 3
volatile int posi = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
long prevT = 0;
float eprev = 0;
float eintegral = 0;
volatile int posi_2 = 0; // specify posi as volatile: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
void setup() {
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  attachInterrupt(2,readEncoder,RISING);
  
  pinMode(PWM,OUTPUT);
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  
  
  Serial.println("target pos");
}

void loop() {
  boolean impri;
  int theta1,theta2,theta3;
  // set target position
//  int target = 1200;
  int target = 1000;

  // PID constants
//  float kp = 26;
//  float kd = 0.025;
//  float ki = 0;
  float kp = 1.0;
  float kd = 0.025;
  float ki = 0;
  // time difference
  long currT = micros();
  float deltaT = ((float) (currT - prevT))/( 1.0e6 );
  prevT = currT;

  // Read the position in an atomic block to avoid a potential
  // misread if the interrupt coincides with this code running
  // see: https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/volatile/
  int pos = 0; 
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    pos = posi;
  }
  // error
  int e = pos - target;
  // derivative
  float dedt = (e-eprev)/(deltaT);
  // integral
  eintegral = eintegral + e*deltaT;
  // control signal
  float u = kp*e + kd*dedt + ki*eintegral;
  // motor power
  float pwr = fabs(u);
  if( pwr > 255 ){
    pwr = 255;
  }
  // motor direction
  int dir = 1;
  if(u>0){
    dir = -1;
  }
  // signal the motor
  setMotor(dir,pwr,PWM,IN1,IN2);

  // store previous error
  eprev = e;
  Serial.print(target);
  Serial.print(" ");
  Serial.print(pos);
  Serial.println();
  if (Serial.available() > 0)
  {
  for(int i = 0; i <3; i++)
  {
  String data_nhan = Serial.readStringUntil(':');
  if (data_nhan!= ""){
    impri = true;
    switch(i){
      case 0:
       theta1 = data_nhan.toInt();
      break;
      case 1:
       theta2 = data_nhan.toInt();
      break;
      case 2:
       theta3 = data_nhan.toInt();
      break;
      }
    }
  }
  }
//  if (impri == true){
//  Serial.print("Theta1: ");
//  Serial.println(theta1);
//  Serial.print("Theta2: ");
//  Serial.println(theta2);
//  Serial.print("Theta3: ");
//  Serial.println(theta3);
//  }
}

void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){
  analogWrite(pwm,pwmVal);
  if(dir == 1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else{
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }  
}
void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    posi++;
  }
  else{
    posi--;
  }
}
