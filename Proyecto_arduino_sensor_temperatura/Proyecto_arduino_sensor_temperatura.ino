//DHT
#include "DHT.h"

 //LCD LIQUID
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h> 

 

/***********************************DHT22************************/
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
const int DHTPin = 2;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);
/****************************************************************/

/**********************LIQUID CRYSTAL I2C************************/
#define I2C_ADDR_2 0x3F
LiquidCrystal_I2C lcd(I2C_ADDR_2,2, 1, 0, 4, 5, 6, 7);
/****************************************************************/

void setup() {
   //Inicia puerto serial
   Serial.begin(9600);

   /*DHT*/
   Serial.println("DHTxx test!");
   dht.begin();

   /*LCD I2C lcd2*/
   lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
   lcd.setBacklightPin(3,POSITIVE);
   lcd.setBacklight(HIGH);
   lcd.home ();                   // go home
   lcd.print("      TEST2");
   lcd.setCursor ( 0, 1 );        // go to the 2nd line
   lcd.print("      LCD2");
   
}
 
void loop() {
   // Wait a few seconds between measurements.
   delay(2000);
 
   // Reading temperature or humidity takes about 250 milliseconds!
   float h = dht.readHumidity();
   float t = dht.readTemperature();
 
   if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
   }
   
   //imprime por serial
   /***********************************DHT22************************/
   Serial.println("Humidity: ");
   Serial.println(h);
   Serial.println(" %\t");
   Serial.println("Temperature: ");
   Serial.println(t);
   Serial.println(" *C ");
   /****************************************************************/

   //imprime por lcd  
   /**********************LIQUID CRYSTAL I2C************************/
   lcd.clear();
   lcd.print("Temp: ");
   lcd.print(t);
   lcd.print(" *C");
   lcd.setCursor ( 0, 1 );        // go to the 2nd line
   lcd.print("Humedad: ");
   lcd.print(h);
   lcd.print("%"); 
   /****************************************************************/
}
