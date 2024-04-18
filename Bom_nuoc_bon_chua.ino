//1 Mach Arduino Nano
//1 Cam bien khoang cach (HC-SR04)
//1 Man hinh lcd 16X2 (su dung i2c lcd)
//1 Relay (5 V)
//Code chinh sua va viet lai boi Kenny Nguyen (Toi yeu Arduino)

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#define BACKLIGHT_PIN     13
const int chipSelect = 4;
#define trigPin 2 // Chan triger cua cam bien gan vao pin so 3 cua arduino
#define echoPin 3  // chan echo cua cam bien gan vao pin so 3 cua arduino
#define re1 7 // pin for relay
//#define re2 8
#define lenght 16.0 // chieu dai 16 cot cua man hinh
double percent = 100.0;
unsigned char b;
unsigned int peace;

int i = 0;

uint8_t bar0[8]  =
{
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0
};
uint8_t bar1[8]  =
{
	0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10
};
uint8_t bar2[8]  =
{
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18
};
uint8_t bar3[8]  =
{
	0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C
};
uint8_t bar4[8]  =
{
	0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E
};
uint8_t bar5[8]  =
{
	0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F
};
LiquidCrystal_I2C lcd(0x27, 16, 2);  // thiet lap man hinh dia chi LCD 0x20 cho 16 ki tu va hien thi 2 dong tren man hinh
int secs = 0;
int secs2 = 0;
int mins = -1;
int hrs = 0;
boolean isAM = true;

int milliDivSecs = 1000;
int milliDivMins = 60000;
int milliDivHrs = 360000;

unsigned long prevmillis = 0;

int interval = 1000;

void setup()
{
	Serial.begin(9600);
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	pinMode(re1, OUTPUT);
	pinMode(13, OUTPUT);
	while(!Serial);
	Serial.println("Khoi tao hoan tat");
	lcd.init();
	     // khoi tao man hinh LCD
	lcd.backlight();
	lcd.createChar(0, bar0);
	lcd.createChar(1, bar1);
	lcd.createChar(2, bar2);
	lcd.createChar(3, bar3);
	lcd.createChar(4, bar4);
	lcd.createChar(5, bar5);
}
void loop()
{
	{
		Serial.print(hrs);
		Serial.print(" : ");
		Serial.print(mins);
		Serial.print(" : ");
		Serial.print(secs);
		Serial.print(" , ");
	}

	unsigned long currmillis = millis();
	long duration, distance;
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	distance = (duration / 2) / 29.1;
// thiet lap muc nuoc su dung xuong 30 cm thi tu dong bat relay
	if (distance >= 30)
	{
		digitalWrite (re1, HIGH);
		digitalWrite (13 , HIGH);

		Serial.print(" ON ");
		lcd.setCursor(14, 0);
		lcd.print("ON");
	}
// thiet lap muc nuoc len den 10 cm thi tu dong tat relay
	if (distance < 10)
	{
		digitalWrite (re1, LOW);
		digitalWrite (13, LOW);

		Serial.print(" OF ");
		lcd.setCursor(14, 0);
		lcd.print("OF");
	}

	lcd.setCursor(0, 0);
	lcd.print(distance);
	Serial.print(distance);
	Serial.print(" CM , ");
	percent = ((30. - distance) / 30.) * 100.;
	Serial.print(percent);

	Serial.println(" %");
	lcd.print(" CM-");
	lcd.print(percent);
	lcd.print("%");
	lcd.setCursor(0, 1);

	double a = lenght / 100.*percent;
	if (a >= 1)
	{
		for (int i = 1; i < a; i++)
		{
			lcd.write(5);
			b = i;
		}
		a = a - b;
	}
	peace = a * 5;

	switch (peace)
	{
		case 0:
			break;
		case 1:
			lcd.write(0);
			break;
		case 2:
			lcd.write(1);
			break;
		case 3:
			lcd.write(2);
			break;
		case 4:
			lcd.write(3);
			break;
		case 5:
			lcd.write(4);
			break;
		case 6:
			lcd.write(5);
			break;
	}

	for (int i = 0; i < (lenght - b); i++)
	{
		lcd.print(" ");
	}
	delay (1000);
	if(secs == 0)
	{
		mins = mins + 1;
		updateMin();
	}



	secs = (millis() / milliDivSecs) % 60;

}

void updateMin()
{
	if(mins > 59)
	{
		hrs = hrs + 1;
		updateHrs();
		if(hrs == 11 && mins > 59)
		{

		}
		mins = 0;
	}
}
void updateHrs()
{


	if(hrs > 12)
	{

		hrs = 1;
	}
}