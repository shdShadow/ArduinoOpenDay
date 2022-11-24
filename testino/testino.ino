#include <SoftwareSerial.h>
const int motorA1 = 5;   // Pin  2 of L293
const int motorA2 = 6;   // Pin  7 of L293
const int motorB1 = 10;  // Pin 10 of L293
const int motorB2 = 11;  // Pin 14 of L293
int vs = 0;
int vd = 0;
char c = ' ';
SoftwareSerial s = SoftwareSerial(9, 3);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  s.begin(38400);
}

void loop() {

  while (s.available() == 0)
    ;
  vs = s.read();
  if (vs != 0)
    return;

  while (s.available() == 0)
    ;
  vs = s.read();
  if (vs == 0)
    return;

  while (s.available() == 0)
    ;
  vd = s.read();
  if (vd == 0)
    return;

  if (vs == vd)
    if (vs < 128 || vd < 128)
      c = 's';
    else
      c = 's';
  else if (vs < vd)
    c = 's';
  else
    c = 'd';


  Serial.print("valore Sx=");
  Serial.println(vs);
  Serial.print("valore Dx=");
  Serial.println(vd);
  // s.println(vs);
  // s.println(vd);
  int potenzaSx = 0;
  int potenzaDx = 0;
  if (vs < 128) {
    potenzaSx = map(vs, 127, 1, 0, 255);
    potenzaDx = map(vd, 127, 1, 0, 255);
  } else if (vs > 128) {
    potenzaSx = map(vs, 129, 255, 0, 255);
    potenzaDx = map(vd, 129, 255, 0, 255);
  } else {
    potenzaDx = 0;
    potenzaSx = 0;
  }
  muovi(c, potenzaSx, potenzaDx);
}

void muovi(char command, int potenzaSx, int potenzaDx) {
  switch (command)  //valuto cosa fare   'a' spegne , 'b' accende
  {
    case 'w':

      //analogWrite(motorA1, vSpeed);
      //analogWrite(motorA2, 0);
      //analogWrite(motorB1, vSpeed);
      //analogWrite(motorB2, 0);
      analogWrite(motorA1, potenzaSx);
      analogWrite(motorB1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB2, potenzaDx);
      Serial.println("w entrato");

      break;

    case 's':
      analogWrite(motorA1, 0);
      analogWrite(motorB1, potenzaSx);
      analogWrite(motorA2, potenzaDx);
      analogWrite(motorB2, 0);
      break;

    case 'a':
      analogWrite(motorA1, potenzaSx);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, potenzaDx);
      break;

    case 'd':
      analogWrite(motorA1, potenzaSx);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, potenzaDx);
      break;
    case 'q':
      analogWrite(motorA1, 0);
      analogWrite(motorA2, 0);
      analogWrite(motorB1, 0);
      analogWrite(motorB2, 0);
      break;
  }
}
//indietro
