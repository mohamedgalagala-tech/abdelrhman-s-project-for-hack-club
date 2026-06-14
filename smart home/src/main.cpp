#include <Keypad.h>
#include <Servo.h>

Servo theDoor;

int pirSensor = 10;
int gasSensor = A0;
int theBuzzer = 11;
int lightRoom1 = 12;
int lightRoom2 = 13;
int ldrSensor = A1;
int theFan = A2;
int tempSensor = A3;
int gardenLight = A4;

int pCount = 0;
char pass1 = '1';
char pass2 = '2';
char pass3 = '3';
char pass4 = '4';
char k1, k2, k3, k4;

const byte r = 4;
const byte c = 4;
char keys[r][c] = {
{'1','2','3','A'},
{'4','5','6','B'},
{'7','8','9','C'},
{'*','0','#','D'}
};
byte rPins[r] = {9, 8, 7, 6};
byte cPins[c] = {5, 4, 3, 2};
Keypad mypad = Keypad(makeKeymap(keys), rPins, cPins, r, c);

void setup() {
Serial.begin(115200);
theDoor.attach(A5);
theDoor.write(0);

pinMode(pirSensor, INPUT);
pinMode(gasSensor, INPUT);
pinMode(theBuzzer, OUTPUT);
pinMode(lightRoom1, OUTPUT);
pinMode(lightRoom2, OUTPUT);
pinMode(ldrSensor, INPUT);
pinMode(theFan, OUTPUT);
pinMode(tempSensor, INPUT);
pinMode(gardenLight, OUTPUT);

digitalWrite(theBuzzer, LOW);
digitalWrite(lightRoom1, LOW);
digitalWrite(lightRoom2, LOW);
digitalWrite(theFan, LOW);
digitalWrite(gardenLight, LOW);
}

void loop() {

int gValue = analogRead(gasSensor);
if (gValue > 400) {
digitalWrite(theBuzzer, HIGH);
delay(300);
digitalWrite(theBuzzer, LOW);
delay(300);
}
if (gValue <= 400) {
digitalWrite(theBuzzer, LOW);
}

int pValue = digitalRead(pirSensor);
if (pValue == HIGH) {
digitalWrite(theBuzzer, HIGH);
delay(1000);
digitalWrite(theBuzzer, LOW);
}

int lValue = analogRead(ldrSensor);
if (lValue < 300) {
digitalWrite(gardenLight, HIGH);
}
if (lValue >= 300) {
digitalWrite(gardenLight, LOW);
}

int tValue = analogRead(tempSensor);
int cTemp = (5.0 * tValue * 100.0) / 1024.0;
if (cTemp > 28) {
digitalWrite(theFan, HIGH);
}
if (cTemp < 28) {
digitalWrite(theFan, LOW);
}

if (Serial.available() > 0) {
char blue = Serial.read();

if (blue == 'A') {
digitalWrite(lightRoom1, HIGH);
}
if (blue == 'a') {
digitalWrite(lightRoom1, LOW);
}
if (blue == 'B') {
digitalWrite(lightRoom2, HIGH);
}
if (blue == 'b') {
digitalWrite(lightRoom2, LOW);
}
if (blue == 'C') {
digitalWrite(theFan, HIGH);
}
if (blue == 'c') {
digitalWrite(theFan, LOW);
}
if (blue == 'O') {
theDoor.write(90);
delay(3000);
theDoor.write(0);
}
}

char k = mypad.getKey();
if (k) {
if (pCount == 0) {
k1 = k;
pCount = 1;
}
else if (pCount == 1) {
k2 = k;
pCount = 2;
}
else if (pCount == 2) {
k3 = k;


pCount = 3;
}
else if (pCount == 3) {
k4 = k;

if (k1 == pass1 && k2 == pass2 && k3 == pass3 && k4 == pass4) {
theDoor.write(90);
delay(4000);
theDoor.write(0);
pCount = 0;
} else {
digitalWrite(theBuzzer, HIGH);
delay(2000);
digitalWrite(theBuzzer, LOW);
pCount = 0;
}
}
}
}