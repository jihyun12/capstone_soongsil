#include <SoftwareSerial.h>
SoftwareSerial HM10(9,10);
//모터
#define LEFT1_A 2
#define LEFT1_B 3

#define RIGHT1_A 4
#define RIGHT1_B 5

 
//초음파 센서
#define IR_TRIG 8
#define IR_ECHO 7

 
void setup() {
  Serial.begin(9600);
  HM10.begin(9600);
  //핀모드 설정
  pinMode(LEFT1_A, OUTPUT);
  pinMode(RIGHT1_A, OUTPUT);
  pinMode(LEFT1_B, OUTPUT);
  pinMode(RIGHT1_B, OUTPUT);
 
  pinMode(IR_TRIG, OUTPUT);
  pinMode(IR_ECHO, INPUT);
}
 void forward(){
  digitalWrite(LEFT1_A, HIGH);
  digitalWrite(LEFT1_B, LOW);
  digitalWrite(RIGHT1_A, HIGH);
  digitalWrite(RIGHT1_B, LOW);
 }
void backward(){
  digitalWrite(LEFT1_A, LOW);
  digitalWrite(LEFT1_B, HIGH);
  digitalWrite(RIGHT1_A, LOW);
  digitalWrite(RIGHT1_B, HIGH);
 
  delay(500);
}
void left(){
  digitalWrite(LEFT1_A, LOW);
  digitalWrite(LEFT1_B, HIGH);
  digitalWrite(RIGHT1_A, HIGH);
  digitalWrite(RIGHT1_B, LOW);

  delay(1000);
}
void right(){
  digitalWrite(LEFT1_A, HIGH);
  digitalWrite(LEFT1_B, LOW);
  digitalWrite(RIGHT1_A, LOW);
  digitalWrite(RIGHT1_B, HIGH);

  delay(1000);
}
void stop(){
  digitalWrite(LEFT1_A, LOW);
  digitalWrite(LEFT1_B, LOW);
  digitalWrite(RIGHT1_A, LOW);
  digitalWrite(RIGHT1_B, LOW);

  delay(1000);
}
void loop() {

  //블루투스
  if(HM10.available()){
    Serial.write(HM10.read());
  }
  if(Serial.available()){
      HM10.write(Serial.read());
  }
  
  //측정
  float duration, distance;
  digitalWrite(IR_TRIG, HIGH);
  delay(10);
  digitalWrite(IR_TRIG, LOW);
  
  //초음파센서를 위한 거리 
  duration = pulseIn(IR_ECHO, HIGH);
  distance = ((float)(340 * duration) / 10000) / 2; //거리를 cm로 표현
  Serial.print("\nDIstance : ");
  Serial.println(distance);
  
  //장애물 유무에 따른 이동
  if(distance < 20) {         //20cm 이내 장애물 감지
     Serial.println("stop");
     stop();
     Serial.println("backward");
     backward();  //후진
     int rnd = random(0,2);   //좌/우회전 랜덤처리
     if(rnd == 0){
        Serial.println("right");
        right();
     }
     else{
        Serial.println("left");
        left();
     }
   }
   else{                     //장애물 무
     Serial.println("forward");
     forward();
   }

}
