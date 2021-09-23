#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <ArduinoJson.h>
#include "Adafruit_seesaw.h"
 
const char* wifi_ssid = "your_wifi_ssid"; //type your ssid
const char* wifi_password = "your_wifi_password"; //type your password

// MQTT Broker running on HomeAssistant (insert IP, user and password matching your HomeAssistant setup)
#define mqtt_server "192.168.1.250"
#define mqtt_port 1883
#define mqtt_user "esp01"
#define mqtt_password "esp01password"
#define mqtt_topic "/esp01/data"
 
Adafruit_seesaw ss;
PubSubClient mqtt_client;
WiFiClient espClient;
 
void setup() {
  Serial.begin(115200);
  delay(10);

  // initialize GPIOs for I2C
  Wire.begin(0, 2);
  
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
   
  // connect to WiFi network
  WiFi.hostname("ESP-01");
  setup_wifi();

  // initialize MQTT client
  mqtt_client.setClient(espClient);
  mqtt_client.setServer(mqtt_server, mqtt_port);   
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(wifi_ssid);

  WiFi.begin(wifi_ssid, wifi_password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // retry until we're reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // attempt to connect
    if (mqtt_client.connect("ESP8266Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqtt_client.state());
      Serial.println(" try again in 5 seconds");
      // wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void loop() {  
  if (!mqtt_client.connected()) {
    reconnect();
  }
  mqtt_client.loop();
  
  // read sensor trough seasaw
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);

  // create a JSON mqtt message
  StaticJsonDocument<200> root;
  root["temperature"] = tempC;
  root["moisture"] = capread;

  char data[200];
  serializeJson(root, data);

  // publish
  mqtt_client.publish(mqtt_topic, data, true);
  
  // wait 1 min
  delay(60*1000);
}
