#include "WiFiEsp.h"
#include <PubSubClient.h>
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial(6, 7); // RX, TX
#endif
// Update these with values suitable for your network.
const char* ssid = "SK_WiFi58DA";
const char* password = "1501035687";
const char* mqtt_server = "192.168.35.235";
WiFiEspClient esp8266client;
PubSubClient client(esp8266client);
long lastMsg = 0;
char msg[50];
int value = 0;
char cmd;
#define ledPin 50
#define MAX_MSG_LEN (128)
void setup() {
 pinMode(ledPin, OUTPUT);
 Serial.begin(9600);
 Serial1.begin(9600);
 WiFi.init(&Serial1);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
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
 randomSeed(micros());
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
}
void reconnect() {
 // Loop until we're reconnected
 while (!client.connected()) {
 Serial.print("Attempting MQTT connection...");
 // Create a random client ID
 String clientId = "ESP8266Client-";
 clientId += String(random(0xffff ), HEX);
 // Attempt to connect
 if (client.connect(clientId.c_str())) {
 Serial.println("connected");
 } else {
 Serial.print("failed, rc=");
 Serial.print(client.state());
 Serial.println(" try again in 5 seconds");
 // Wait 5 seconds before retrying
 delay(5000);
 }
 }
client.subscribe("yuri/LED");
}
void callback(char* topic, byte* payload, unsigned int length) {
 Serial.print("Message arrived [");
 Serial.print(topic);
 Serial.print("] ");
 for (int i = 0; i < length; i++) {
 cmd = (char)payload[i];
 Serial.print(cmd);
 }
 Serial.println();
 // Switch on the LED if an 1 was received as first character
 if ((char)payload[0] == '1') {
 digitalWrite(ledPin, HIGH); // Turn the LED on (Note that LOW is the voltage level
 // but actually the LED is on; this is because
 // it is acive low on the ESP-01)
 Serial.println("LED ON");
 } else if((char)payload[0] == '2') {
 digitalWrite(ledPin, LOW); // Turn the LED off by making the voltage HIGH
 Serial.println("LED OFF");
 }
}
void loop() {
 if (!client.connected()) {
 reconnect();
 }
 client.loop();
 delay(1000);
}

