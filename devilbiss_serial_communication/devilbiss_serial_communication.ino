#include <SoftwareSerial.h>
int rxpin = 2, txpin = 3;
int serialdata;
String DVdata = "";
int purity = 0;
int firstDigitbase = 11;
int secondDigitbase = 12;
int pinA = 4;
int pinB = 5;
int pinC = 6;
int pinD = 7;
int pinE = 8;
int pinF = 9;
int pinG = 10;
int i = 0;
int k = 0;
int j = 0;
int z = 0;
int x = 0;
int y = 0;
int Pin_array[7] = {4, 5, 6, 7, 8, 9, 10};
int Segment_array[10][7] = {  { 0, 0, 0, 0, 0, 0, 1 }, // 0
  { 1, 0, 0, 1, 1, 1, 1 }, // 1''?hb
  { 0, 0, 1, 0, 0, 1, 0 }, // 2
  { 0, 0, 0, 0, 1, 1, 0 }, // 3
  { 1, 0, 0, 1, 1, 0, 0 }, // 4
  { 0, 1, 0, 0, 1, 0, 0 }, // 5
  { 0, 1, 0, 0, 0, 0, 0 }, // 6
  { 0, 0, 0, 1, 1, 1, 1 }, // 7
  { 0, 0, 0, 0, 0, 0, 0 }, // 8
  { 0, 0, 0, 0, 1, 0, 0 }  // 9

};   
void BCD0(int);
void BCD1(int);

SoftwareSerial mySerial(rxpin, txpin);

String MyASCII(int MyDigit) {
  switch (MyDigit) {
    case 48: return ("0"); break;
    case 49: return ("1"); break;
    case 50: return ("2"); break;
    case 51: return ("3"); break;
    case 52: return ("4"); break;
    case 53: return ("5"); break;
    case 54: return ("6"); break;
    case 55: return ("7"); break;
    case 56: return ("8"); break;
    case 57: return ("9"); break;
    default: return (""); break;
  }
}
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinD, OUTPUT);
  pinMode(pinE, OUTPUT);
  pinMode(pinF, OUTPUT);
  pinMode(pinG, OUTPUT);
  pinMode(firstDigitbase, OUTPUT);
  pinMode(secondDigitbase, OUTPUT);

}

void loop() {
  digitalWrite(firstDigitbase, HIGH);
  digitalWrite(secondDigitbase, HIGH);
  while (mySerial.available() > 0) {
    serialdata = mySerial.read();
    if (serialdata != 141) {
      Serial.write(serialdata - 128);
      DVdata = DVdata + (MyASCII(serialdata - 128));
    }
    else {
      Serial.println();
      purity = DVdata.substring(45, 49).toInt();
      //Serial.print(purity);
      x = (purity / 10);
      y = (purity - (x * 10));

      while (z < 45) {
        BCD0(x);
        delay(5);
        BCD1(y);
        delay(5);
        z++;
      }
      z = 0;

      DVdata =  "";
      //Serial.println();
    }
  }
  delay(50);
}

void BCD0(int number)
{

  for (int j = 0; j < 7; j++) {
    digitalWrite(secondDigitbase, HIGH);
    digitalWrite(firstDigitbase, LOW);
    digitalWrite(Pin_array[j], Segment_array[number][j]);
  }
}
void BCD1(int number)
{
  for (int j = 0; j < 7; j++) {
    digitalWrite(firstDigitbase, HIGH);
    digitalWrite(secondDigitbase, LOW);
    digitalWrite(Pin_array[j], Segment_array[number][j]);
  }
}
