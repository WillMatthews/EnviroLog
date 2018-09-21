#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>

int ident = 1;

#define DHTPIN 12     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11 Temp & Humidity sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(2, OUTPUT);           // set pin to input
  pinMode(LED_BUILTIN, OUTPUT);
 
  Serial.begin(115200);                    //Serial connection
  WiFi.begin("WIFI SSID", "WIFI PASSWORD");   //WiFi connection

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

 delay(10000); // Sample every 10s
 digitalWrite(LED_BUILTIN,LOW);
 delay(10);
 digitalWrite(LED_BUILTIN,HIGH);
 
 if(WiFi.status() == WL_CONNECTED){   // Check WiFi connection status
   
   digitalWrite(2,HIGH); // Ensure blue LED off
   
   // Reading temperature or humidity takes about 250 milliseconds
   float h = dht.readHumidity();
   // Read temperature as Celsius (the default)
   float t = dht.readTemperature();
   
   if (isnan(h) || isnan(t)) {
     Serial.println("Failed to read from DHT sensor!");
     return;
   }
   
   Serial.print("Temp (C) = ");
   Serial.println(t);
   Serial.print("Humidity (%) = ");
   Serial.println(h);

   String postdata = "temp=" + String(t) + "&humid=" + String(h) + "&ident=" + String(ident);
 
   HTTPClient http;    // Declare object of class HTTPClient
 
   http.begin("http://domain/gettemppost.php"); //Specify request destination

   http.addHeader("Content-Type", "application/x-www-form-urlencoded");          //Specify content-type header

   int httpCode = http.POST(postdata);   //Send the request
   String payload = http.getString();  //Get the response payload

   // SERVER STATUS REPLY
   Serial.print("HttpCode: ");
   Serial.println(httpCode);   //Print HTTP return code

   // SERVER REPLY - use this to pass vars back
   Serial.print("Payload: ");
   Serial.println(payload);    //Print request response payload
 
   http.end();  //Close connection
 
 }else{
    digitalWrite(2,LOW);
    Serial.println("Error in WiFi connection");
 }
}
