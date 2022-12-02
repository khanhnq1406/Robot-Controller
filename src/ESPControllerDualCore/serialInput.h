void serialInput() {
  // while (Serial.available())
  // {                         // Check if the serial data is available.
  //   delay(3);               // a small delay
  //   char c = Serial.read(); // storing inputTheta1 data
  //   readString += c;        // accumulate each of the characters in readString
  // }

  // if (readString.length() > 0)
  // { // Verify that the variable contains information

  //   Serial.println(readString.toInt()); // printing the inputTheta1 data in integer form
  //   User_Input = readString.toInt();    // here inputTheta1 data is store in integer form
  // }

  String data_ ,mode_,val;
  int moc;
  int data;
  if(Serial.available() > 0)
  {
    val = Serial.readStringUntil('\n');
    for (int i = 0; i < val.length(); i++) {
    if (val.charAt(i) == ' ') {
        moc = i; //Tìm vị trí của dấu ""
      }
    }
    mode_=val;
    data_=val;
    mode_.remove(moc);
    data_.remove(0,moc+1);
    data=data_.toInt();
  }
  if(mode_ == "t1")
  {
    theta1 = data;
  }
  if(mode_ == "t2")
  {
    theta2 = data;
  }
  if(mode_ == "t3")
  {
    theta3 = data;
  }

}