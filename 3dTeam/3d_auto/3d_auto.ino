#include<Servo.h>

Servo left;
Servo right;

int leftServo = 9;
int rightServo = 10;

void setup() {
  // put your setup code here, to run once:
  left.attach(leftServo);
  right.attach(rightServo);
  pinMode(leftServo, OUTPUT);
  pinMode(rightServo, OUTPUT);
  
  Serial.begin(9600);


  
}

void loop() {
  // put your main code here, to run repeatedly:
  String inData = "";
  char* inDataBuf = 0;
  char incommingMsg = 0;
  while(Serial.available()){
    incommingMsg = Serial.read();
    inData = inData + incommingMsg;
  }
  inDataBuf = (char*)malloc(sizeof(char)*inData.length()+1);
  inData.toCharArray(inDataBuf, inData.length()+1);
  Serial.println(inDataBuf);
  delay(500);
  if(strcmp(inDataBuf, "up") == 0){
    left.write(180);
    right.write(0);
    Serial.println("up");
    delay(1500);
  }
  else if(strcmp(inDataBuf, "down") == 0){
    left.write(0);
    right.write(180);
    Serial.println("down");
    delay(1500);
  }
 


}
