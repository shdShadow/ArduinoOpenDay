#include <SoftwareSerial.h>
SoftwareSerial Bluetooth(6,7); // RX, TX

const int motorA1  = 5;  // Pin  2 of L293
const int motorA2  = 6;  // Pin  7 of L293
const int motorB1  = 10; // Pin 10 of L293
const int motorB2  = 11;  // Pin 14 of L293
char command;   //dove salvo i comandi ricevuti

int vSpeed = 200;   // Default speed, from 0 to 255

void setup() {

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);

  Serial.begin(9600);
  Bluetooth.begin(9600);
}

void loop() {
  //leggo il comanda dalla seriale pin 0,1
  if (Bluetooth.available() > 0)   //se arriva un adato
  {
   
    command = Bluetooth.read();
     Bluetooth.print(command);
       //leggo il dato da seriale (tastiera o bt)
    switch (command)    //valuto cosa fare   'a' spegne , 'b' accende
    {
      case 'w':
      
        //analogWrite(motorA1, vSpeed);
        //analogWrite(motorA2, 0);
        //analogWrite(motorB1, vSpeed);
        //analogWrite(motorB2, 0);
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


void muovi()
