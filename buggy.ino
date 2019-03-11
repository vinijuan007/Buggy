#include <Servo.h>
#include <stdlib.h>
#include <stdio.h>
int turn;
Servo name_servo;
const int encoderInA = 11, encoderInB =10;

int detectState=0, count=0, lastState;
int servo_position = 0;
//US1
int trigPin1= 2;
int echoPin1= 3;
long duration1;
int distance1;

//US2-left
int trigPin2= 8;
int echoPin2= 9;
long duration2;
int distance2;

//US3-right
int trigPin3= 13;
int echoPin3= 12;
long duration3;
int distance3;


int enA = 5;
int in1 = 4;
int in2;

int enB = 6;
int in4 = 7;
int in3;


//Define I/O
void setup() {
  name_servo.attach (3);
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode(trigPin1, OUTPUT); 
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT); 
  pinMode(echoPin2, INPUT);

  pinMode(trigPin3, OUTPUT); 
  pinMode(echoPin3, INPUT);
  
  Serial.begin(9600);// initialize serial communication of UltraSS
  pinMode(encoderInA, INPUT);
  pinMode(encoderInB, INPUT);
}


void UltraSS1() {
digitalWrite(trigPin1, LOW);// short high pulse to ensure clean high pulse
delay(2);
digitalWrite(trigPin1, HIGH);// pulse is sent
delay(10);
digitalWrite(trigPin1, LOW);
duration1 = pulseIn(echoPin1, HIGH);
distance1= duration1*0.034/2;
}

void UltraSS2() {//LEFT USS
digitalWrite(trigPin2, LOW);// short high pulse to ensure clean high pulse
delay(2);
digitalWrite(trigPin2, HIGH);// pulse is sent
delay(10);
digitalWrite(trigPin2, LOW);
duration2 = pulseIn(echoPin2, HIGH);
distance2= duration2*0.034/2;
}

void UltraSS3() {//RIGHT USS
digitalWrite(trigPin3, LOW);// short high pulse to ensure clean high pulse
delay(2);
digitalWrite(trigPin3, HIGH);// pulse is sent
delay(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);
distance3= duration3*0.034/2;
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
digitalWrite(in3, LOW);
digitalWrite(in4, LOW);
analogWrite(enB, 0); 
}

void LEFT(){//motor B
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 0);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 70);
}
void RIGHT(){//motor A
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW);
analogWrite(enA, 70);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
analogWrite(enB, 0); 
}
void Turnright(){//motor A
  while (count <30) {
    LEFT();
    lastState = detectState;
    detectState=digitalRead(encoderInA);
    if (detectState != lastState){
      count++;
      //Serial.println(count);
  }
}
  count = 0;
}
void Turnleft(){//motor B
  while (count <30) {
    RIGHT();
    lastState = detectState;
    detectState=digitalRead(encoderInB);
    if (detectState != lastState){
      count++;
      //Serial.println(count);
  }
}
  count = 0;
}

void loop() {
    name_servo.write(10);
    UltraSS1();
  
  if(distance1 < 10){
      Stop();
      delay(1000);
      UltraSS2();
      UltraSS3();
      Serial.println(distance2);
      Serial.print("-");
      Serial.println(distance3);
      if (distance2 < distance3) {
          Turnleft();
      }
      else {
          Turnright();
      }
      Stop();
      delay(1000);
  }
  else {
    RunF();
  }
}
