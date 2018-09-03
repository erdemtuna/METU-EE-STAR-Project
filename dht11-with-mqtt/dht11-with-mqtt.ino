/* DHTServer - ESP8266 Webserver with a DHT sensor as an input
  Based on ESP8266Webserver, DHTexample, and BlinkWithoutDelay (thank you)
  Version 1.0 5/3/2014 Version 1.0 Mike Barela for Adafruit Industries
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

#include <dht.h>
dht DHT;
#define DHT11_PIN 2

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
 
const char* ssid = "SUPERONLINE_WiFi_5555";
const char* password =  "ab6dda65";
const char* mqttServer = "35.237.42.75";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";
char payload[50] ;

WiFiClient espClient;
PubSubClient client(espClient);

float hum, temp_c; // Values read from sensor
 
void setup() {
 
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }
   
  client.subscribe("esp/#");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
 
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
  gettemperature();
  
  String tempor = "temp: " + String(temp_c) + " hum: " + String(hum);
  snprintf (payload, 50,tempor.c_str());
  client.publish("esp/test", payload);

  delay(2000);
}

void gettemperature() {
  // Reading temperature for humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
  DHT.read11(DHT11_PIN);
  hum = round(DHT.humidity * 10) / 10; // measure humidity
  temp_c = round(DHT.temperature * 10) / 10.0; // measure temperature

  // print the temperature and humidity on serial monitor
  Serial.print("temperature: ");
  Serial.print(temp_c);
  Serial.print(",\t");
  Serial.print("humidity: ");
  Serial.println(hum);

  // Check if any reads failed and exit early (to try again).
  if (isnan(hum) || isnan(temp_c)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  delay(1000);
}

