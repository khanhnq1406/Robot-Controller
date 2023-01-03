void recvData() {
  byte n = Serial.available();
  if (n != 0) {
    buff = Serial.readString();
    // Serial.print(buff);
    char* p;
    p = strtok(buff.c_str(), "_");
    theta[indexTheta++] = atof(p);
    while (p != NULL) {
      p = strtok(NULL, "_");
      if (p != NULL) {
        theta[indexTheta++] = atof(p);
      }
    }
    String sendMsg = (String)theta[0] + '_' + (String)theta[1] + '_' + (String)theta[2];
    Serial.print(sendMsg);
    buff = "";
    indexTheta = 0;
  }
}