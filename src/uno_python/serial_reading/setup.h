void motor1Setup() {
  pinMode(MotEnable1, OUTPUT);
  pinMode(MotFwd1, OUTPUT);
  pinMode(MotRev1, OUTPUT);
  pinMode(encoderPin1A, INPUT_PULLUP);
  pinMode(encoderPin1B, INPUT_PULLUP);
  digitalWrite(encoderPin1A, HIGH);
  digitalWrite(encoderPin1B, HIGH);
  attachInterrupt(0, updateEncoder1, CHANGE);
  attachInterrupt(1, updateEncoder1, CHANGE);
  PidTheta1.SetMode(AUTOMATIC);
  PidTheta1.SetSampleTime(1);
  PidTheta1.SetOutputLimits(-255, 255);
}

void motor2Setup() {
  pinMode(MotEnable2, OUTPUT);
  pinMode(MotFwd2, OUTPUT);
  pinMode(MotRev2, OUTPUT);
  pinMode(encoderPin2A, INPUT_PULLUP);
  pinMode(encoderPin2B, INPUT_PULLUP);
  digitalWrite(encoderPin2A, HIGH);
  digitalWrite(encoderPin2B, HIGH);
  attachInterrupt(2, updateEncoder2, CHANGE);
  attachInterrupt(3, updateEncoder2, CHANGE);
  PidTheta2.SetMode(AUTOMATIC);
  PidTheta2.SetSampleTime(1);
  PidTheta2.SetOutputLimits(-255, 255);
}

void motor3Setup() {
  pinMode(MotEnable3, OUTPUT);
  pinMode(MotFwd3, OUTPUT);
  pinMode(MotRev3, OUTPUT);
  pinMode(encoderPin3A, INPUT_PULLUP);
  pinMode(encoderPin3B, INPUT_PULLUP);
  digitalWrite(encoderPin3A, HIGH);
  digitalWrite(encoderPin3B, HIGH);
  attachInterrupt(4, updateEncoder3, CHANGE);
  attachInterrupt(5, updateEncoder3, CHANGE);
  PidTheta3.SetMode(AUTOMATIC);
  PidTheta3.SetSampleTime(1);
  PidTheta3.SetOutputLimits(-255, 255);
}