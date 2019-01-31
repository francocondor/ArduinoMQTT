#include <SPI.h>
#include <Ethernet.h>
#include <CayenneMQTTEthernet.h>
#include <DHT.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
unsigned long lastMillis = 0;
EthernetClient client;
DHT dht(3, DHT11);
char username[] = "xxxx";
char password[] = "xxxx";
char clientID[] = "xxxx";
float tempC = 0.0;
float tempF = 0.0;
float humidity = 0.0;

IPAddress ip(172,17,62,200);
IPAddress myDns(192,168,80,231);
void setup() {
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID);
  dht.begin();

  delay(1000);
}

void loop() {
  Cayenne.loop();

  if (millis() - lastMillis > 4000) {
    lastMillis = millis();

    int chk = dht.read();
    Serial.println("Read OK");
    humidity = (float)dht.readHumidity();
    tempC = (int)dht.readTemperature();
    tempF = (int)round(1.8 * tempC + 32);

    Serial.println("Humedad " + (String)humidity);
    Serial.println("Temp. Celsius " + (String)tempC);
    Serial.println("Temp. Fahrenheit " + (String)tempF);
    Cayenne.virtualWrite(0, humidity);
    Cayenne.celsiusWrite(1, tempC);
    Cayenne.virtualWrite(2, tempF);
  }
}
