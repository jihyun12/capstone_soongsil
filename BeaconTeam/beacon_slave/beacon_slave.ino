//slave beacon 3개에 업로드할 코드.

#include <SoftwareSerial.h>
const int flame = A0;
const int gas = A1;
int buzz = 3;

int flameValue = 0;
int gasValue = 0;
char incommingMsg;
//블루투스 모듈 설정 TX, RX
SoftwareSerial HM10(9,10);

void setup()
{

  Serial.begin(9600);
  HM10.begin(9600);
  pinMode(buzz, OUTPUT);
  pinMode(flame, INPUT);
  pinMode(gas, INPUT);
}

void loop()
{
////////////////////////////////////////////////////////////////////
//    HM-10 블루투스 모듈과 시리얼모니터로 AT 통신하게 해주는 코드.     //
///////////////////////////////////////////////////////////////////

  //incommingMsg로 읽은 글자를 inData에 이어붙여 스트링 만들고
  //inDataBuf의 char형 포인터에 담아 HM10에 한번에 write함.
  String inData = "";
  char* inDataBuf = 0;
  while(Serial.available()){
    incommingMsg = Serial.read();
    inData = inData + incommingMsg;
  }
  inDataBuf = (char*)malloc(sizeof(char)*inData.length()+1);
  inData.toCharArray(inDataBuf, inData.length()+1);
  HM10.write(inDataBuf);
  while(HM10.available()){
    Serial.write(HM10.read());
  }


/////////////////////////////////////////////////////////////////
//        불꽃, 가스 감지해서 부저로 소리 내는 코드.                //
//        (가스 테스트 끝나면 불꽃 세기+가스 세기 if문 합쳐야 함. )  //
/////////////////////////////////////////////////////////////////

  //불꽃감지센서 read
  flameValue = analogRead(flame);
  printValue("Flame", flameValue);

  //불꽃 세기와 flameValue가 반비례함.
  //불꽃이 900 이하 감지되면 부저에서 도레미 음 출력.
  if (flameValue <= 900)
  {
    tone(3, 262);
    delay(500);
    tone(3, 294);
    delay(500);
    tone(3,330);
    delay(500);
  }
  else
  {
    noTone(3);
  }
  delay(500);


  //가스누출 감지센서 read
  gasValue = analogRead(gas);
  printValue("Gas", gasValue);
  //가스 테스트는 못 해봄.
  // 가스 500 이상 감지되면 부저에서 도레미 음 출력.
  if (gasValue >= 500)
  {
    tone(3, 262);
    delay(500);
    tone(3, 294);
    delay(500);
    tone(3,330);
    delay(500);
  }
  delay(500);
  Serial.flush();

}

//////////////////////////////////////////////////////
//    변수 내부 값 시리얼모니터로 출력해주는 함수.       //
/////////////////////////////////////////////////////
void printValue(String tag, int value){
    Serial.print(tag + " : ");
    Serial.println(value);
}
