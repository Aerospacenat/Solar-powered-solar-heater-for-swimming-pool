// Owner Nathaniel Robinson 
// nathanieldavidrobinson@gmail.com
// Pool heater
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

uint8_t SensorPool[8] = { 0x28, 0xEE, 0xD5, 0x64, 0x1A, 0x16, 0x02, 0xEC };
uint8_t SensorPipe[8] = { 0x28, 0x61, 0x64, 0x12, 0x3C, 0x7C, 0x2F, 0x27 };
uint8_t SensorAir[8] = { 0x28, 0x61, 0x64, 0x12, 0x3F, 0xFD, 0x80, 0xC6 };


int Pump = 1;
int ValveIn = 2;
int ValveOut = 3;
int RunningLED = 5; //green LED
int ProcessingLED = 6; // orange LED 
int IssueLED = 8; //red LED
int pos = 0;
int Ex;
int EmergencyStop = 8; // Emergency interupt button
int Exchangebutton = 9; // Emergency exchange button 




void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Pump, OUTPUT);
  pinMode(ValveIn, OUTPUT);
  pinMode(ValveOut, OUTPUT);
  pinMode(RunningLED, OUTPUT);
  pinMode(ProcessingLED, OUTPUT);
  pinMode(IssueLED, OUTPUT);
  pinMode(EmergencyStop, INPUT);
  pinMode(Exchangebutton, INPUT);
  sensors.begin();
  Start();
}

void loop() {
  TempCheck();
  if ( Ex = 1) { 
    ExchangeWater();
  }
}

void TempCheck (){
  TempUpdate();
  if (SensorPipe > 25){
    Ex = 1;
    }
   else{
    Ex = 0;
   }
   
  }
  
void TempUpdate (){

  sensors.requestTemperatures();
  
  Serial.print("SensorPool: ");
  Temp(SensorPool);
  
  Serial.print("SensorPipe: ");
  Temp(SensorPipe);
  
  Serial.print("SensorAir: ");
  Temp(SensorAir);
  
  Serial.println();
  delay(1000);
}

void Temp (DeviceAddress deviceAddress)
{
  float tempC = sensors.getTempC(deviceAddress);
  Serial.print(tempC);
  Serial.print((char)176);
  Serial.print("C  |  ");

}
void Start(){
  OpenValveIN();
  WaterON();
  Loading5Sec();
  WaterOFF();
}

void ExchangeWater(){
  OpenBothValves();
  WaterON();
  Loading10Sec();
  WaterOFF();
  CloseBothValves();
}

void WaterON() { 
  digitalWrite(Pump,HIGH);
}

void WaterOFF(){
  digitalWrite(Pump,LOW);
}

void Loading2Sec(){
  for (int i = 0; i <= 3; i++) {
    digitalWrite(ProcessingLED, HIGH);
    delay(500); //0.5 seconds 
    digitalWrite(ProcessingLED, LOW);
    delay(500); 
  }
}
void Loading5Sec(){
  for (int i = 0; i <= 6; i++) {
    digitalWrite(ProcessingLED, HIGH);
    delay(500); //0.5 seconds 
    digitalWrite(ProcessingLED, LOW);
    delay(500); 
  }
}

void Loading10Sec(){
  for (int i = 0; i <= 11; i++) {
    digitalWrite(ProcessingLED, HIGH);
    delay(500); //0.5 seconds 
    digitalWrite(ProcessingLED, LOW);
    delay(500); 
  }
}

void OpenBothValves(){
  digitalWrite(ValveIn, HIGH);
  digitalWrite(ValveOut, HIGH);
  Loading2Sec();
  digitalWrite(ValveIn, LOW);
  digitalWrite(ValveOut, LOW);
  delay(100);
}

void CloseBothValves(){
  digitalWrite(ValveIn, HIGH);
  digitalWrite(ValveOut, HIGH);
  Loading2Sec();
  digitalWrite(ValveIn, LOW);
  digitalWrite(ValveOut, LOW);
  delay(100);
}

void OpenValveIN(){ 
 digitalWrite(ValveIn, HIGH);
 Loading2Sec();
 digitalWrite(ValveIn, LOW);
 delay(100);
}
  
void CloseValveIN(){ 
  digitalWrite(ValveIn, HIGH);
  Loading2Sec();
  digitalWrite(ValveIn, LOW);
  delay(100);
  }
  
void OpenValveOUT(){ 
  digitalWrite(ValveOut, HIGH);
  Loading2Sec();
  digitalWrite(ValveOut, LOW);
  delay(100);
}
  
void CloseValveOUT(){ 
  digitalWrite(ValveOut, HIGH);
  Loading2Sec();
  digitalWrite(ValveOut, LOW);
  delay(100);
  }

void Emergency(){
  OpenBothValves();
  
  
}







//------------------
// servo 
// for (pos = 90; pos >= 0; pos -= 10) { // goes from 90 degrees to 0 degrees
   // ValveIn.write(pos);              // tell servo to go to position in variable 'pos'
  //  delay(15);                       // waits 15ms for the servo to reach the position
  //  }
 //  for (pos = 90; pos >= 0; pos -= 10) { // goes from 90 degrees to 0 degrees
 //   ValveIn.write(pos);              // tell servo to go to position in variable 'pos'
  //  delay(15);                       // waits 15ms for the servo to reach the position
  //  }
  //#include <Servo.h>
  //int ValveInPin = 2;
//int ValveOutPin = 3;

//Servo ValveIn,  ValveOut;
// ValveIn.attach(ValveInPin); 
 // ValveOut.attach(ValveOutPin); 
