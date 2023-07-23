#include "WiFiEsp.h"
#include "PubSubClient.h"
// Emulate Serial1 on pins 6/7 if not present
#ifndef HAVE_HWSERIAL1
#include "SoftwareSerial.h"
SoftwareSerial Serial(6, 7); // RX, TX
#endif
// Update these with values suitable for your network.
const char* ssid = "SK_WiFi58DA";
const char* password = "1501035687";
const char* mqtt_server = "192.168.35.235"; // wifi ipv4
WiFiEspClient esp8266client;
PubSubClient client(esp8266client);
long lastMsg = 0;
long fsrForce;
char msg[50];
String packet;
float Flex, Force;
int fsrReading, fsrVoltage;
unsigned long fsrResistance, fsrConductance;
const int FORCE_PIN = A0;
const int FLEX_PIN = A1;
const float VCC = 5; // Measured voltage of Ardunio 5V line
const float R_DIV = 10000.0; // Measured resistance of your resistor
// Upload the code, then try to adjust these values to more accurately calculate bend degree.
const float STRAIGHT_RESISTANCE = 37300.0; // resistance when straight
const float BEND_RESISTANCE = 90000.0; // resistance at 90 deg
void setup() {
 pinMode(FLEX_PIN,INPUT);
 pinMode(FORCE_PIN,INPUT);
 Serial.begin(9600);
 Serial1.begin(9600);
 WiFi.init(&Serial1);
 setup_wifi();
 client.setServer(mqtt_server, 1883);
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
}
float get_flex(){

 // Read the ADC, and calculate voltage and resistance from it
 int flexADC = analogRead(FLEX_PIN);
 float flexV = flexADC * VCC / 1023.0;
 float flexR = R_DIV * (VCC / flexV - 1.0);
 // Use the calculated resistance to estimate the sensor's bend angle:
 float angle = map(flexR, STRAIGHT_RESISTANCE, BEND_RESISTANCE, 0, 90.0);
 return(angle);

 }
float get_force() {
 fsrReading = analogRead(FORCE_PIN);
 fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);

 if (fsrVoltage == 0) {
 Serial.println("No pressure");
 } else {
 // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
 // so FSR = ((Vcc - V) * R) / V
 fsrResistance = 5000 - fsrVoltage; // fsrVoltage is in millivolts so 5V = 5000mV
 fsrResistance *= 10000; // 10K resistor
 fsrResistance /= fsrVoltage;
 fsrConductance = 1000000; // we measure in micromhos so
 fsrConductance /= fsrResistance;
 // Use the two FSR guide graphs to approximate the force
 if (fsrConductance <= 1000) {
 fsrForce = fsrConductance / 80;
 return(fsrForce);
 } else {
 fsrForce = fsrConductance - 1000;
 fsrForce /= 30;
 return(fsrForce);
 }
 }
 Serial.println("--------------------");
 }
void loop() {
 Flex = get_flex();
 Force = get_force();
 if (!client.connected()) {
 reconnect();
 }
 client.loop();
 long now = millis();
 if (now - lastMsg > 000) {
 lastMsg = now;
 packet = "Flex : " + String(Flex) + "degrees "+ "Force : " + String(Force) + "N";
 packet.toCharArray(msg,50);
 Serial.print("Publish message: ");
 Serial.println(msg);
 Serial.println();
 client.publish("yuri/Sensor",msg);
 delay(5000);
 }
}

