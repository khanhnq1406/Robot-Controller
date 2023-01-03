void controlMotor();
void pwmOut(int out1, int out2, int out3);
void updateEncoder1();
void forward1();
void reverse1();
void finish1();
void updateEncoder2();
void forward2();
void reverse2();
void finish2();
void updateEncoder3();
void forward3();
void reverse3();
void finish3();

void controlMotor() {
  REV_Theta1 = map(theta[0], 0, 360, 0, 6000);
  REV_Theta2 = map(theta[1], 0, 360, 0, 6000);
  REV_Theta3 = map(theta[2], 0, 360, 0, 6000);
  setpointTheta1 = REV_Theta1;  
  inputTheta1 = encoderValue1; 
  setpointTheta2 = REV_Theta2;  
  inputTheta2 = encoderValue2; 
  setpointTheta3 = REV_Theta3;  
  inputTheta3 = encoderValue3; 
  PidTheta1.Compute();
  PidTheta2.Compute();
  PidTheta3.Compute();

  pwmOut(outputTheta1, outputTheta2, outputTheta3);
}

void pwmOut(int out1, int out2, int out3)
{
  if (out1 > 0)
  {                              
    analogWrite(MotEnable1, out1); 
    forward1();                 
  }
  else
  {
    analogWrite(MotEnable1, abs(out1)); 
    reverse1();                       
  }
  
  if (out2 > 0)
  {                              
    analogWrite(MotEnable2, out2); 
    forward2();                 
  }
  else
  {
    analogWrite(MotEnable2, abs(out2)); 
    reverse2();                       
  }

  if (out3 > 0)
  {                              
    analogWrite(MotEnable3, out3); 
    forward3();                 
  }
  else
  {
    analogWrite(MotEnable3, abs(out3)); 
    reverse3();                       
  }
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
  int MSB1 = digitalRead(encoderPin2A); // MSB1 = most significant bit
  int LSB2 = digitalRead(encoderPin2B); // LSB2 = least significant bit

  int encoded1 = (MSB1 << 1) | LSB2;         // converting the 2 pin value to single number
  int sum1 = (lastEncoded1 << 2) | encoded1; // adding it to the previous encoded value

  if (sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011)
    encoderValue2++;
  if (sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000)
    encoderValue2--;

  lastEncoded1 = encoded1; // store this value for next timeMillis
}

void updateEncoder3()
{
  int MSB1 = digitalRead(encoderPin3A); // MSB1 = most significant bit
  int LSB2 = digitalRead(encoderPin3B); // LSB2 = least significant bit

  int encoded1 = (MSB1 << 1) | LSB2;         // converting the 2 pin value to single number
  int sum1 = (lastEncoded1 << 2) | encoded1; // adding it to the previous encoded value

  if (sum1 == 0b1101 || sum1 == 0b0100 || sum1 == 0b0010 || sum1 == 0b1011)
    encoderValue3++;
  if (sum1 == 0b1110 || sum1 == 0b0111 || sum1 == 0b0001 || sum1 == 0b1000)
    encoderValue3--;

  lastEncoded1 = encoded1; // store this value for next timeMillis
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