#include <ArduinoJson.h>
#include<SoftwareSerial.h>
#define rxPin 12
#define txPin 13
// SoftwareSerial SUART(rxPin, txPin);  //D2, D1 = SRX, STX
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
char buff[50] = "";
volatile byte indx;
int theta[3], indexTheta = 0;
unsigned long millisRecv = 0;
void setup()
{
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  Serial.begin(115200);
  mySerial.begin(115200);
}

void loop()
{

  // if ((millis() - millisRecv > 100 || millisRecv == 0)) {
  byte n = mySerial.available();
  if (n != 0)
  {
    int c = mySerial.read(); 
      if (c != '>')
        buff[indx++] = c;
   
      else {
        indexTheta = 0;
        Serial.println(buff);  
        char * p;
        p = strtok(buff, "~");
        Serial.println(p);  
        theta[indexTheta++] = atoi(p);
        while(p != NULL) {
            p = strtok(NULL, "~"); 
            if(p != NULL) {
              Serial.println(p);  
              theta[indexTheta++] = atoi(p);
            }
        }
        Serial.println("----------Int--------");
        Serial.println(theta[0]);
        Serial.println(theta[1]);  
        Serial.println(theta[2]);  
        Serial.println("----------Int--------");

        indx = 0;
        memset(buff, 0, 50);
      }
    }
  // }
  // Serial.println("----------Start--------");
  // DynamicJsonDocument doc(2048);
  // String com = Serial1.readString();
  // Serial.println(com);
  // DeserializationError error = deserializeJson(doc, com);
  // if (error) {
  //   Serial.println("Error");
  //   return;
  // }
  // Serial.println("JSON received and parsed");
  // Serial.print("Data 1 ");
  // Serial.println("");
  // String data1 =doc["theta1"];
  // Serial.print(data1);
  // Serial.print("   Data 2 ");
  // String data2=doc["theta2"];
  // String data3=doc["theta3"];
  // Serial.print(data2);
  // Serial.print(data3);
  // Serial.println("");
  // Serial.println("---------------------xxxxx--------------------");
    delay(1);
 
 
}