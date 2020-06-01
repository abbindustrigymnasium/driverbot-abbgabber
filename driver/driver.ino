#include <PubSubClient.h>
#include <Servo.h>
#include <ESP8266WiFi.h>
Servo servo;

#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1

String vel = "";
String dir = "0";
String deg = "90";
String data = "";

//Constant variables
const char* ssid = "edimax_2.4G";
const char* password =  "Admin123";
const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;
const char* mqttUser = "gabriel.bergdahl@abbindustrigymnasium.se";
const char* mqttPassword = "qazwsxedc";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  servo.attach(15);
  servo.write(90);

  Serial.begin(115200);

  // Connects to Wifi and subscribes to the topic
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

    if (client.connect("catgang", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
  client.publish("gabriel.bergdahl@abbindustrigymnasium.se/driverbot", "CatGang");
  client.subscribe("gabriel.bergdahl@abbindustrigymnasium.se/driverbot");

}

void loop() {
  // Where the different values are written to make the car run
  client.loop();
  digitalWrite(motorPinRightDir, dir.toInt());
  analogWrite(motorPinRightSpeed, vel.toInt());
  servo.write(deg.toInt());
}

// Runs when received a message in the subbed topic
void callback(char* topic, byte* payload, unsigned int length) {
  data = "";
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    data += (char)payload[i];
  }
  Serial.println(data);
  
  // Defines the three variables used to drive the car
  vel = data.substring(0, 4);
  vel = vel.toInt() - 100;
  if (vel.toInt() > 0 ) {
    dir = "1";
  }
  else {
    vel = vel.toInt() * -1;
    dir = "0";
  }
  vel = vel.toInt() * 10.24;
  deg = data.substring(5,8);
}
