//[아두이노 코드]

//불꽃 감지센서

int flame = A0;
int buzz = 5;
int val = 0;

void setup()
{
	pinMode(buzz, OUTPUT);

	pinMode(flame, INPUT);
	Serial.begin(9600);
}

void loop()
{
	val = analogRead(flame);
	Serial.println(val);

	if (val >= 800)
	{
		tone(5, 262);
		delay(500);
		tone(5, 294);
		delay(500);
		tone(5330);
		delay(500);
	}
	else
	{
		noTone(5);
	}
	delay(500);
}

//가스 감지센서

const int gas = A0;
const int led = 9;
int GasValue;

void loop(){
	GasValue = analogRead(gas);
	if (GasValue >= 500)
	{
		digitalWrite(led, HIGH);
	}
	else
	{
		digitalWrite(led, LOW);
	}
Serial.print("GasValue = ");
Serial.print(GasValue);
delay(500);
}
