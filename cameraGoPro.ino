#include <SoftwareSerial.h>
#include <Stepper.h>
#define STEPS 200
bool isWait = false; 
int speed = 40;
char inChar=-1; // Where to store the character read
SoftwareSerial bluetooth(4, 5); // RX, TX
Stepper myStepper(STEPS, 8, 9, 10, 11); // initialize the stepper library on pins 8 through 11:

void setup() {
   Serial.begin(9600);
   bluetooth.begin(57600);
   Serial.println("Loading System...");
   myStepper.setSpeed(speed); 
}

void SetSpeedLow() {
   if(speed >= 15){
    speed = speed - 5;
    Serial.println(speed);
    myStepper.setSpeed(speed);   
   }
}

void SetSpeedHigh() {
   if(speed <= 80){
    speed = speed + 5;
    Serial.println(speed);
    myStepper.setSpeed(speed);   
   }
}

void ToggleWait() {
  isWait = !isWait;
  Serial.println("Toggle Wait"); 
}

void LookAtRightLittle() {
  if(isWait) {
    delay(5000);
  }
    myStepper.step(-10);
    Serial.println("LookAtRightLittle");   
}

void LookAtLeftLittle() {
  if(isWait) {
    delay(5000);
  }
    myStepper.step(10);
    Serial.println("LookAtLeftLittle");   
}

void LookAtRight() {
  if(isWait) {
    delay(5000);
  }
    myStepper.step(-1050);
    Serial.println("LookAtRight");
}

void ResetSpeed() {
    myStepper.setSpeed(40);   
    Serial.println("ResetSpeed");   
}

void LookAtLeft() {
    if(isWait) {
    delay(5000);
  }
    myStepper.step(1050);
    Serial.println("LookAtLeft");   
}

void LookAround() {
    if(isWait) {
    delay(5000);
  }
    myStepper.step(2100);
    Serial.println("LookAround");   
}

// To configure the Android controller, you can use this app:
// https://play.google.com/store/apps/details?id=com.giumig.apps.bluetoothserialmonitor&hl=pt_BR&gl=US
// and define the command with the letters below
// After that, just connect the app to the bluetooth module and send these commands
void loop() {
  if(bluetooth.available() > 0) {
    
    inChar = bluetooth.read();
    switch(inChar) {
      
      case 'W':
      ToggleWait();
      break;

      case 'U':
      SetSpeedHigh();   
      break;

      case 'D': 
      SetSpeedLow(); 
      break;

      case 'R': 
      LookAtRight();
      break;

      case 'L': 
      LookAtLeft();
      break;

      case '+': 
      LookAtRightLittle();
      break;

      case '-': 
      LookAtLeftLittle();
      break;

      case 'A': 
      LookAround();
      break;

      case 'S': 
      ResetSpeed();
      break;   
    }
    bluetooth.flush();
    Serial.flush();
  }
}
