// Simple alarm system
//
// constants won't change. They're used here to
// set pin numbers:
const int alarmEnabled = 8;
const int zone1 = 3;     // Zone 1 sensor  --
const int zone2 = 4;     // Zone 2 sensor
const int zone3 = 5;     // Zone 3 sensor
const int zone4 = 6;     // Zone 4 sensor
const int ledPin10 =  10;      // 10 LED pin
const int ledPin11 =  11;      // 11 LED pin
const int ledPin12 =  12;      // 12 LED pin
const int ledPin13 =  9;      // 13 LED pin
const int ledAlarmStatus = 13;       // ALARN ON led  green

void setup() {
  
  Serial.begin(9600);          //Enable Serial at 9600
  Serial.println("=== BURGLAR ALARM 1.1 ===");
  pinMode(zone1, INPUT);    // initialize the sensor pin as an input:
  pinMode(zone2, INPUT);    // initialize the sensor pin as an input:
  pinMode(zone3, INPUT);    // initialize the sensor pin as an input:
  pinMode(zone4, INPUT);    // initialize the sensor pin as an input:
  pinMode(alarmEnabled, INPUT);
  
  pinMode(ledPin10, OUTPUT);      // initialize the LED pin as an output:
  pinMode(ledPin11, OUTPUT);      // initialize the LED pin as an output:
  pinMode(ledPin12, OUTPUT);      // initialize the LED pin as an output:
  pinMode(ledPin13, OUTPUT);      // initialize the LED pin as an output:
  pinMode(ledAlarmStatus, OUTPUT);   //Red led if the alarm is Enabled
  
}

void loop() {

  bool isEnabled = isAlarmEnabled();

  if(isEnabled)
  {
    digitalWrite(ledAlarmStatus, HIGH);
    //Serial.print("H");
    setZone(zone1,ledPin10,"Zone 1 detected");
    setZone(zone2,ledPin11,"Zone 2 detected");
    setZone(zone3,ledPin12,"Zone 3 detected");
    setZone(zone4,ledPin13,"Zone 4 detected");
  }
  else{
    digitalWrite(ledAlarmStatus, LOW);
    //Serial.print("L");
  }

 //delay(10);
}

bool alarmSwitchedOn = false;

bool isAlarmEnabled(){
  //int isEnabled = digitalRead(alarmEnabled);
  //return isEnabled;

  char incomingValue = readCharFromSerialPort();
  
  if (incomingValue == '1'){
      alarmSwitchedOn = true;
  }
  if (incomingValue == '2'){
    alarmSwitchedOn = false;
  }
    
  return alarmSwitchedOn;
}

char readCharFromSerialPort(){
  char val;
  if (Serial.available() > 0){
    val = Serial.read();
    Serial.print(val);
  }
  return val;
}

void setZone(int zone, int outLed, String message) {
  int buttonState = digitalRead(zone);
  
  if (buttonState == HIGH) {    
    digitalWrite(outLed, HIGH);
    delay(2500);    
    Serial.print(message);
    Serial.print('\n');
    digitalWrite(outLed, LOW);
    delay(500);
  }

 
}
