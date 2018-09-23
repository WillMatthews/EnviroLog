#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "DHT.h"

#define DHTPIN 12       // what digital pin we're connecting our temp sensor to
#define DHTTYPE DHT11   // DHT 11 Temp & Humidity sensor

DHT dht(DHTPIN, DHTTYPE);

// BEGIN USER SETTINGS
int ident = 1;
int waittime = 10000; // in ms
boolean flash_http = true;
boolean flash_loop = true;

char phplocation[] = "http://url/gettemppost.php";
char wifiSSID[] = "wifi-ssid";
char wifiPass[] = "wifi-password";
// END USER SETTINGS



void setup() {
    pinMode(2, OUTPUT);                     // allow use of built in LED
    pinMode(LED_BUILTIN, OUTPUT);           // allow use of built in LED

    Serial.begin(115200);                   //Serial connection
    WiFi.begin(wifiSSID, wifiPass);         //WiFi connection

    Serial.println("");
    Serial.print("Waiting for connection");
  
    while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
        delay(100);
        Serial.print(".");
    }

    Serial.println("");
    dht.begin();
    digitalWrite(2,HIGH);
}



void loop() {

    delay(waittime);
    digitalWrite(LED_BUILTIN,LOW);

    if(flash_loop){
        delay(10);
        digitalWrite(LED_BUILTIN,HIGH);
    }
 
    if(WiFi.status() == WL_CONNECTED){     // Check WiFi connection status
   
        digitalWrite(2,HIGH);                // Ensure blue LED off
   
        float h = dht.readHumidity();        // Reading temperature or humidity takes about 250 milliseconds
        float t = dht.readTemperature();     // Read temperature as Celsius

        // Input sanitation code (don't log if bad data)
        if (isnan(h) || isnan(t)) {
            Serial.print("Failed to read from DHT sensor!");
            return;
        }
  
        // debugging code 
        Serial.print("Temp (C) = ");
        Serial.println(t);
        Serial.print("Humidity (%) = ");
        Serial.println(h);

        // Add your sensor to the `postdata` here
        String postdata =     "ident="  + String(ident);
        postdata = postdata + "&humid=" + String(h);
        postdata = postdata + "&temp="  + String(t); 

        if (flash_http){
            digitalWrite(2,LOW);                 // HTTP Flash START
        }
   
        HTTPClient http;                     // Declare object of class HTTPClient

        http.begin(phplocation);             // Specify request destination
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");    // Specify content-type header

        int httpCode = http.POST(postdata);  // Send the request
        String payload = http.getString();   // Get the response payload

        // SERVER STATUS REPLY
        Serial.print("HttpCode: ");
        Serial.println(httpCode);            // Print HTTP return code

        // SERVER REPLY - use this to pass vars back
        Serial.print("Payload: ");
        Serial.println(payload);             // Print request response payload

        http.end();                          // Close connection

        if (flash_http){
            digitalWrite(2,HIGH);                // HTTP Flash END
        }
   
    }else{
        digitalWrite(2,LOW);                // Hold WIFI module light on when fault occurs
        Serial.println("Error in WiFi connection");
    }
}
