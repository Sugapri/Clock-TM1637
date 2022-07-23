#include "RTClib.h"
#include <TM1637Display.h>

#define CLK 2
#define DIO 3

RTC_DS3231 rtc;
TM1637Display display(CLK, DIO);





void setup() {
  Serial.begin(9600);
  delay (3000);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
    }
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, Lets set the time!");
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
    display.setBrightness(5);
    display.clear();
}

void loop() {

  animasi();
  

}

void Jam(){
  DateTime now = rtc.now();
 int displaytime = (now.hour() * 100)+ now.minute();
 Serial.println(displaytime);
 display.showNumberDecEx(displaytime,0b11100000,true);
 delay (500);
 display.showNumberDec(displaytime,true);
 delay(500);
  }
void tulis(){
  uint8_t data[] = {0b0001110,0b1011111,0b0110011,0b0100111};
  display.setSegments(data);
  }
  
void tulis2(){
  uint8_t data [] = {0b1101101, 0b0011100, 0b1110100, 0b0011100};
  display.setSegments(data);
  
  }

void tulistanggal(){
   uint8_t tgl [] = {0b1111000, 0b1101111, 0b0111000, 0b0000000};
  display.setSegments(tgl);
  }

void tanggal (){
  DateTime now = rtc.now();
  int d = (now.day());
  int b = (now.month());
//  display.showNumberDec(-,false,2,2);
  display.showNumberDec(d,false,2,0);
  display.showNumberDec(b,true,2,2);
  
  }

void tahun (){
  DateTime now = rtc.now();
  int y = (now.year());
  display.showNumberDec(20,false,2,0);
  display.showNumberDec(y,false,2,2);
    
  }
  
  
void Temp (){

  uint8_t data [] = {0b1100011, 0b0111001}; //celcius degrees
  int suhu = (rtc.getTemperature()-4);
   display.setSegments(data,2,2);
   display.showNumberDec(suhu,false,2,0);
     
  }

int tampil;
void animasi(){
  long cM = millis();
  static long pM;

  if (cM-pM > 5000){
    tampil++;
    if (tampil > 6){
      tampil = 0;
      }
      pM = cM;
    }
    switch (tampil){
      case 0 :
        tulis();
        break;
      case 1 :
        Jam();
        break;
      case 2 :
        tulis2();        
        break;
      case 3 :
        Temp();
        break;
      case 4 :
        tulistanggal();
        break;
      case 5 :
        tanggal();
        break;
      case 6 : 
        tahun();
        break;
      }
  
  
  }
