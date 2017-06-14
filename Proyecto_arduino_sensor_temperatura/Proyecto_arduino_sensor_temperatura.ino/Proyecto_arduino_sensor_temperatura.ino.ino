//DHT
#include "DHT.h"
 
// Uncomment whatever type you're using!

/***********************************DHT22************************/
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
const int DHTPin = 2;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);
/****************************************************************/

void setup() {
   //Inicia puerto serial
   Serial.begin(9600);

   /*DHT*/
   Serial.println("DHTxx test!");
   dht.begin();

   
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
   /***********************************DHT22************************/
   Serial.println("Humidity: ");
   Serial.println(h);
   Serial.println(" %\t");
   Serial.println("Temperature: ");
   Serial.println(t);
   Serial.println(" *C ");
   /****************************************************************/
}
