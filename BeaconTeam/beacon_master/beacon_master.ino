//master beacon 1개에 업로드할 코드. (소화기에 부착)

#include <SoftwareSerial.h>
char incommingMsg;
//블루투스 모듈 설정 TX, RX
SoftwareSerial HM10(9,10);

void setup()
{

  Serial.begin(9600);
  HM10.begin(9600);
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
  Serial.flush();

}

//////////////////////////////////////////////////////
//    변수 내부 값 시리얼모니터로 출력해주는 함수.       //
/////////////////////////////////////////////////////
void printValue(String tag, int value){
    Serial.print(tag + " : ");
    Serial.println(value);
}
