/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

  Adatped by Erdem Tuna for this code to work with DHT11.

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 2 // GPIO 2 of ESP8266

float hum, temp_c; // variables to store humidity and temperature
float last_temp_c = -45; // last sent 

const char* ssid = "DESKTOP-NET"; // wifi ssid
const char* password = "pass1234"; // wifi password

const char* mqtt_server = "broker.hivemq.com"; // mqtt server
const int mqtt_port = 1883; // mqtt port

char payload[50]; // mqtt payload
uint16_t delay_duration = 2000; // loop function delay

WiFiClient espClient;
PubSubClient client(espClient);


void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      //client.publish("outTopic", "hello world");
      client.subscribe("inTopic/#"); // subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void get_temperature() {
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
}

String get_payload(){
  get_temperature();
  String pre;
  pre= "temp: " + String(temp_c) + " hum: " + String(hum);
  return pre;
  }

void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //payload = get_payload();
  snprintf (payload, 75, get_payload().c_str());
  if(abs(temp_c-last_temp_c) > last_temp_c/70){
    Serial.print("Publish message: ");
    Serial.println(payload);
    client.publish("fLab/sensor2", payload);
    last_temp_c = temp_c;
    }
  delay(delay_duration);
}
