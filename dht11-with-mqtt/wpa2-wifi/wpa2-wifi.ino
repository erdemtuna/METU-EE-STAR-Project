#include "ESP8266WiFi.h"
extern "C" {
  #include "user_interface.h"
  #include "wpa2_enterprise.h"
}

static const char* ssid = "ssid";
static const char* username = "username";
static const char* password = "password";
const char* host = "host_ip";

void setup(){
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);
   // Setting ESP into STATION mode only (no AP mode or dual mode)
  wifi_set_opmode(0x01);

  struct station_config wifi_config;

  memset(&wifi_config, 0, sizeof(wifi_config));
  strcpy((char*)wifi_config.ssid, ssid);

  wifi_station_set_config(&wifi_config);

  wifi_station_clear_cert_key();
  wifi_station_clear_enterprise_ca_cert();

  wifi_station_set_wpa2_enterprise_auth(1);
  wifi_station_set_enterprise_username((uint8*)username, strlen(username));
  wifi_station_set_enterprise_password((uint8*)password, strlen(password));

  wifi_station_connect();
  Serial.print("Wifi station connect status:");
  Serial.println(wifi_station_get_connect_status());

  // Wait for connection AND IP address from DHCP
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(WiFi.status());
    delay(2000);
    Serial.println("Not connected");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  delay(2000);
}
