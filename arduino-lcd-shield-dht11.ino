#include <LiquidCrystal.h>
#include "DHT.h"

#define DHTPIN 15 
#define DHTTYPE DHT11 

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int fan = 16;
DHT dht(DHTPIN, DHTTYPE);
void setup(){
	Serial.begin(9600);
	while(!Serial);
	pinMode(fan, OUTPUT);
   	lcd.begin(16, 2);               
   	lcd.setCursor(0,0);             
   	lcd.print("Temp:   ____ 'C");  
   	lcd.setCursor(0,1); 
   	lcd.print("Humid:  ____ % "); 
   	
   	dht.begin();
   	
}
 
void loop(){
	float temp = dht.readTemperature();
	float hum = dht.readHumidity();
 
  	lcd.setCursor(7,0); 
  	lcd.print(temp);
  	lcd.setCursor(8,1); 
  	lcd.print(padding(hum,4));
  	
  	Serial.println(temp);
  	char resp;
  	while(Serial.available()){
  		resp = Serial.read();
  		if(resp>47){
  			digitalWrite( fan, resp=='1');	
  			lcd.setCursor(6,1); 
   			lcd.print((int)resp);
  		}
  	}
  	delay(300);
  	
}

String padding( int number, byte width ) {
 String retVal="", str_num=String(number);
 byte pad= width-str_num.length();

 int currentMax = 10;
 for (byte i=0; i<pad; i++){
   retVal+=" ";
 } 
 retVal+=str_num;
 return retVal;
}