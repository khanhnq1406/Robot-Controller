#define MotEnable1 5
#define MotFwd1 6
#define MotRev1 7
int encoderPin1A = 2;
int encoderPin1B = 3;
volatile int lastEncoded1 = 0;
volatile long encoderValue1 = 0;
double inputD4 = 0, outputD4 = 0, setpointD4 = 0;
int REV_D4 = 0;
void setup() {
  Serial.begin(9600);
  pinMode(MotEnable1, OUTPUT);
  pinMode(MotFwd1, OUTPUT);
  pinMode(MotRev1, OUTPUT);
  pinMode(encoderPin1A, INPUT_PULLUP);
  pinMode(encoderPin1B, INPUT_PULLUP);
  digitalWrite(encoderPin1A, HIGH);
  digitalWrite(encoderPin1B, HIGH);
}
void loop() {
  analogWrite(MotEnable1, 225);
    digitalWrite(MotFwd1, HIGH);
    digitalWrite(MotRev1, LOW);
}