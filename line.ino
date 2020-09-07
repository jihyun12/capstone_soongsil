#include <SoftwareSerial.h>
#define IN1 3
#define IN2 5
#define IN3 9
#define IN4 10 

 //적외선 센서
int SENSOR_L =  7;      // 라인트레이서 왼쪽 센서
int SENSOR_R = 6;      // 라인트레이서 오른쪽 센서

void forward() {    // 전진 : 모터 두 개를 모두 정회전 시킴
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
}
void back() {    // 후진 : 모터 두 개를 모두 역회전 시킴 
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
}
void left() {    // 좌회전 : 오른쪽 모터만 정회전 시킴
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
}
void right() {   // 우회전 : 왼쪽 모터만 정회전 시킴
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);  
}
void stop() {    // 정지 : 2개의 모터 모두 회전 멈춤
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, LOW);
}
void setup() {
    Serial.begin(115200);
  pinMode(IN1, OUTPUT);     // A 모터 1
  pinMode(IN2, OUTPUT);     // A 모터 2
  pinMode(IN3, OUTPUT);     // B 모터 1
  pinMode(IN4, OUTPUT);     // B 모터 2
  pinMode(SENSOR_L, INPUT); 
  pinMode(SENSOR_R, INPUT);
}

void loop() {  
// 만약 양쪽 센서가 모두 선 ‘미감지’(반사신호’OK’) 경우 : 전진

if (!digitalRead(SENSOR_L) && !digitalRead(SENSOR_R)) {

  stop();  

 }  



// 만약 왼쪽 센서만 ‘선감지(반사신호X)’ 경우 :  좌회전

else if (!digitalRead(SENSOR_L) && digitalRead(SENSOR_R)) {

  left();  

 }   



// 만약 오른쪽 센서만 ‘선감지(반사신호X)’ 경우 :  우회전

else if (digitalRead(SENSOR_L) && !digitalRead(SENSOR_R)) {

  right();

 } 



  // 만약 양쪽 센서 모두 ‘선감지(반사신호X)’ 경우 :  정지

else if (digitalRead(SENSOR_L) && digitalRead(SENSOR_R)) {

  forward();  

 } 
}
