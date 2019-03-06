#include <Servo.h>
#include <stdlib.h>
#include <stdio.h>
int turn;
Servo name_servo;
const int encoderInL = 2, encoderInR =3;
int detectState=0, count=0, lastState;
int servo_position = 0;
int trigPin= 7;
int echoPin= 8;
long duration;
int distance;
int enA = 5;
int in1 = 9;
int in2 = 10;
int enB = 6;
int in4 = 12;
int in3 = 11;
//Define I/O
void setup() {
  name_servo.attach (3);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  Serial.begin(9600);// initialize serial communication of UltraSS
  pinMode(encoderInL, INPUT);
  pinMode(encoderInR, INPUT);
}


void UltraSS() {
digitalWrite(trigPin, LOW);// short high pulse to ensure clean high pulse
delay(2);
digitalWrite(trigPin, HIGH);// pulse is sent
delay(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
}
void RunF(){
digitalWrite(in1, HIGH);//motor A at power 400, so moving
digitalWrite(in2, LOW);
analogWrite(enA, 100);
digitalWrite(in3, LOW);//motor B
digitalWrite(in4, HIGH);
analogWrite(enB,100);

 
}

void Stop(){
digitalWrite(in1, HIGH);//motor B at power 0,so stop
digitalWrite(in2, LOW);
analogWrite(enA, 0);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW);
analogWrite(enB, 0); 
}
void LEFT(){//motor B
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 0);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 100);
}
void RIGHT(){//motor A
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 100);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 0); 
}
void Turnright(){//motor B
  while (count <20) {
    LEFT();
    lastState = detectState;
    detectState=digitalRead(encoderInR);
    if (detectState != lastState){
      count++;
      Serial.println(count);
  }
}
}
void Turnleft(){//motor A
  while (count <20) {
    RIGHT();
    lastState = detectState;
    detectState=digitalRead(encoderInL);
    if (detectState != lastState){
      count++;
      Serial.println(count);
  }
}
}

void loop() {
  name_servo.write(10);
  UltraSS();

if(distance < 50){
Stop();
delay(1000);
turn = rand()%2;
Serial.print (turn);
  if (turn ==0){
    Turnleft();
    }
  else {
    Turnright();
  }
delay(500)
count=0;
}
else {
RunF();

}
}
