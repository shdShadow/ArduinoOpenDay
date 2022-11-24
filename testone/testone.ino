#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(9, 3);  // RX, TX

const int motorA1 = 5;  // 
const int motorA2 = 6;  // 
const int motorB1 = 10;  // 
const int motorB2  = 11;  // 
//valori temporanei che leggo
byte sxTemp = 0;
byte dxTemp = 0;
//valori che passo ai motori
int valSxB = 0;
int valSxF = 0;
int valDxB = 0;
int valDxF = 0;

void setup() {
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  Serial.begin(9600);
  Bluetooth.begin(38400);
}

void loop() {

  if (Bluetooth.available() >= 3) {
    Serial.print("Ricevuto");
    int sincro = Bluetooth.read();
    sxTemp = Bluetooth.read();
    dxTemp = Bluetooth.read();
  }
}

void muoviLaColita(char command, int vSpeed1, int vSpeed2) {

  switch (command)  //valuto cosa fare   'a' spegne , 'b' accende
  {
    case 'w':
      analogWrite(motorA1, vSpeed);
      analogWrite(motorB1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB2, vSpeed);
      Serial.println("w entrato");

      break;

    case 's':
      analogWrite(motorA1, 0);
      analogWrite(motorB1, vSpeed);
      analogWrite(motorA2, vSpeed);
      analogWrite(motorB2, 0);
      break;

    case 'a':
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, vSpeed);
      break;

    case 'd':
      analogWrite(motorA1, vSpeed);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
      break;
    case 'q':
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
      break;


  }
}
}
