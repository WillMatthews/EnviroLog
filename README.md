# EnviroLog - An ESP8266 based data logging system.

1. ESP8266 reads data from sensors.
1. ESP8266 connects to an external server and sends a POST to the server's PHP page.
1. PHP in server stores data to a MongoDB database.
1. Server presents a stats page plotting contents of MongoDB database.
