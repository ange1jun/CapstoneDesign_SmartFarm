#include <DHT.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN 7      // 네오픽셀 D핀과 연결한 아두이노 핀 번호
#define LED_COUNT 200   // 네오픽셀 LED 개수
#define BRIGHTNESS 250 // 네오픽셀 LED 밝기(0 ~ 255) *RGBW만

#define motor 8
#define fan1 9
#define fan2 10


int select_mode = 0;
char btval = 0;
unsigned long previousMillis = 0; //이전시간
const long delayTime = 1000; //1초(1000) 대기시간

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT mydht(A0,DHT11);
SoftwareSerial mySerial(2,3);
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800); // RGB일 경우 NEO_GRBW 대신 NEO_GRBW 입력

void setup()
{
  mySerial.begin(9600);
  mydht.begin();
  lcd.init(); //LCD 초기화
  lcd.backlight(); //LCD 백라이트 켜기
  pixels.begin();                  // 네오픽셀 초기화(필수)
  pixels.setBrightness(BRIGHTNESS);  // 네오픽셀 밝기 설정 *RGBW만
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

byte r = 0, g = 0, b = 0;  //rgb 변수선언

void loop()
{
 
  // unsigned long currentMillis = millis();

  // if(currentMillis - previousMillis >= delayTime){
  //   previousMillis = currentMillis;


  //   if (mySerial.available()>2){
  //   r = mySerial.read();
  //   g = mySerial.read();
  //   b = mySerial.read();
  //   mySerial.flush();



  //   for (int i=0; i< LED_COUNT; i++){
  //   pixels.setPixelColor(i, pixels.Color(r, g, b));
  //   pixels.show();
  // }

  // }
  // }

  float a = mydht.readTemperature(); //온도 변수
  mySerial.println("t"+String(a));
  delay(1000);
  float b = mydht.readHumidity(); //습도 변수 
  mySerial.println("m"+String(b));
  delay(1000);
 
  float val = 1023 - analogRead(A1); //토양습도 변수
  float soil = map(val, 0, 700, 0, 100);
  mySerial.println("s"+String(soil));

  btval = mySerial.read();
 
  if (btval == '2'){  //자동모드로전환
    select_mode = 2;
  }else if (btval == '3'){  //수동모드로 전환
    select_mode = 3;
  }else if (btval == '4'){
    select_mode = 4;
  }else if (btval == '5'){
    select_mode = 5;
  }else if (btval == '6'){
    select_mode = 6;
  }else if (btval == '7'){
    select_mode = 7;
  }else if (btval == '8'){
    select_mode = 8;
  }else if (btval == '9'){
    select_mode = 9;
  }
  
  Serial.print(select_mode);

  if ( 1 < select_mode && select_mode < 3){ //수동모드
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      lcd.clear();
      lcd.backlight();
      lcd.display();
      lcd.println("User mode status");
  }

  if ( 2 < select_mode && select_mode < 4){ //자동모드
     
        if (soil < 10){
        digitalWrite(8, HIGH);
        } else 
        digitalWrite(8, LOW);
        if (a > 20) {
        digitalWrite (9, HIGH);
        } else
        digitalWrite (9, LOW);
        if (a > 20) {
        digitalWrite (10, HIGH);
        } else
        digitalWrite (10, LOW);

        lcd.backlight();
        lcd.display();
        lcd.setCursor(0, 0);
        lcd.print("Tmp:");
        lcd.print(a);
        lcd.print("'C");
        lcd.setCursor(0, 1);
        lcd.print("Hum:");
        lcd.print(b);
        lcd.print("% ");
        lcd.setCursor(12, 0); //1행 12열
        lcd.print("Soil:");
        lcd.setCursor(11, 1); //2행 11열
        lcd.print(soil);
        lcd.print("% ");

        Serial.print("습도: ");
        Serial.print(a);
        Serial.print("온도: ");
        Serial.print(b);
        Serial.print("Moisture: ");
        Serial.print(soil);
  
  
  }

  if ( 3 < select_mode && select_mode < 5){
    digitalWrite(8,HIGH);
  }

  if ( 4 < select_mode && select_mode < 6){
    digitalWrite(8,LOW);
  }

  if ( 5 < select_mode && select_mode < 7){
    digitalWrite(9,HIGH);
  }

  if ( 6 < select_mode && select_mode < 8){
    digitalWrite(9,LOW);
  }

  if ( 7 < select_mode && select_mode < 9){
    digitalWrite(10,HIGH);
  }

  if ( 8 < select_mode && select_mode < 10){
    digitalWrite(10,LOW);
  }

}  

  













