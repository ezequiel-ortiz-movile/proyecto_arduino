/*
  Web Server

 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)

 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 modified 02 Sept 2015
 by Arturo Guadalupi

 */
//DHT
#include <DHT.h>

//LCD LIQUID
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  

//ETHERNET
#include <SPI.h>
#include <Ethernet.h>

/*************************ETHERNET*******************************/
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
EthernetServer server(80);
/****************************************************************/

/***********************************DHT22************************/
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
const int DHTPin = 2;     // what digital pin we're connected to
DHT dht(DHTPin, DHTTYPE);
/****************************************************************/

/**********************LIQUID CRYSTAL I2C************************/
#define I2C_ADDR_2 0x3F
LiquidCrystal_I2C lcd(I2C_ADDR_2,2, 1, 0, 4, 5, 6, 7);
/****************************************************************/


//CORREN LAS INCIALIZACIONES
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  /*DHT*/
  Serial.println("DHTxx test!");
  dht.begin();

  /*LCD I2C lcd2*/
  lcd.begin (16,2);    // Inicializar el display con 16 caraceres 2 lineas
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home ();                   // go home
  lcd.print("   INICIANDO...");
 
  // start the Ethernet connection:
  Serial.println("Inicializando red...");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    for (;;)
      ;
  }
  else {
    Serial.print("IP asignada por DHCP: ");
    Serial.println(Ethernet.localIP());
  }
}


void loop() {
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
             // Reading temperature or humidity takes about 250 milliseconds!
               float h = dht.readHumidity();
               float t = dht.readTemperature();
             
               if (isnan(h) || isnan(t)) {
                  Serial.println("Failed to read from DHT sensor!");
                  return;
               }
               client.print("Temperatura: ");
               client.print(t);
               client.print(" *");
               client.print("C");
               client.print("</br>");
               client.print("Humedad: ");
               client.print(h);
               client.print(" %");
               
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
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}

