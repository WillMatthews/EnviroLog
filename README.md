# EnviroLog - An ESP8266 based data logging system.


## Installation:

ESP8266:
1. Install the code in `./esp/` on an ESP8266 board with the Arduino IDE.
2. Setup a serial link to check if Wifi is correctly configured.
3. Ensure the DHT11 or DHT22 is correctly connected to the ESP8266.
    Web Server:
4. Install PHP.
5. Install MongoDB, and create a table. Add a document to create the table.
6. Configure and place `gettemppost.php` in a secure but visible location on your web directory.
7. Move python scripts to an appropriate location (scripts currently are not automated).
    ESP8266:
8. Confirm packet replies are being recieved on the serial link.
9. Confirm documents are being added to the MongoDB database (the count on items should increase).

Done for now - Project is a work in progress.
Check back soon for updates, as more of this program will be automated away with time.


## Process Flow:
1. ESP8266 reads data from sensors.
1. ESP8266 connects to an external server and sends a POST to the server's PHP page.
1. PHP in server stores data to a MongoDB database.
1. Server presents a stats page plotting contents of MongoDB database.
