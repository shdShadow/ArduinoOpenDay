#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX | TX
int x = 10;

void setup() {
pinMode(9, OUTPUT); // this pin will pull the HC-05
// pin 34 (KEY pin) HIGH to switch module to AT mode

digitalWrite(9, HIGH);
Serial.begin(9600);
Serial.println("Enter AT commands:");
BTSerial.begin(38400); // HC-05 default speed in AT
// command mode
}

char command;

//Collegare BT tenendo premuto lo switch button per entrare in AT MODE
//Monitor seriale a 9600 NL&CR
//AT+NAME:BTC-00
//AT+PSWD?
//AT+PSWD:1234

void loop() {


// Keep reading from HC-05 and send to Arduino
// Serial Monitor
if (BTSerial.available())
Serial.write(BTSerial.read());

// Keep reading from Arduino Serial Monitor
// and send to HC-05
if (Serial.available())
BTSerial.write(Serial.read());
}
