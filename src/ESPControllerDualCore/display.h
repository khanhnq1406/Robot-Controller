void display() {

  if ((unsigned long)(millis() - timeMillis) > 100)
  {
    Serial.print("Theta 1: ");
    Serial.println(theta1);
    Serial.print("Theta 2: ");
    Serial.println(theta2);
    Serial.print("Theta 3: ");
    Serial.println(theta3);
    Serial.print("Theta 1 update: ");
    Serial.println(theta1Update);
    Serial.print("Theta 2 update : ");
    Serial.println(theta2Update);
    Serial.print("Theta 3 update: ");
    Serial.println(theta3Update);

    Serial.print("this is REV_Theta1 - ");
    Serial.println(REV_Theta1); // printing REV_Theta1 value
    Serial.print("encoderValue1 - ");
    Serial.println(encoderValue1);

    Serial.print("this is REV_Theta2 - ");
    Serial.println(REV_Theta2); // printing REV_Theta2 value
    Serial.print("encoderValue2 - ");
    Serial.println(encoderValue2);

    Serial.print("this is REV_Theta3 - ");
    Serial.println(REV_Theta3); // printing REV_Theta3 value
    Serial.print("encoderValue3 - ");
    Serial.println(encoderValue3);

    // Serial.print("MSB3: ");
    // Serial.println(MSB3);
    // Serial.print("LSB3: ");
    // Serial.println(LSB3);
    Serial.print("Px: ");
    Serial.println(Px);
    Serial.print("Py: ");
    Serial.println(Py);
    Serial.print("Pz: ");
    Serial.println(Pz);
    Serial.print("Px Update: ");
    Serial.println(PxUpdate);
    Serial.print("Py Update: ");
    Serial.println(PyUpdate);
    Serial.print("Pz Update: ");
    Serial.println(PzUpdate);    
    timeMillis = millis();
  }

}