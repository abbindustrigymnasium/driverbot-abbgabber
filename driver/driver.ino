#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
Servo servo;


#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1

// Here, we define some variables that will be sent to the engine and servo later on
String vel = "";
String dir = "0";
int velint = 0;
String deg = "90";
String data = "";

// Here, we have the ssid and password for the local wifi, which is necessary for the microcontroller to connect to the broker
const char* ssid = "edimax_2.4G";
const char* password =  "Admin123";

// Here, we define some things for the mqtt library like our username and password
const char* mqttServer = "maqiatto.com";
const int mqttPort = 1883;
const char* mqttUser = "gabriel.bergdahl@abbindustrigymnasium.se";
const char* mqttPassword = "qazwsxedc";

// This is the topic being subscribed to
String Sub = "gabriel.bergdahl@abbindustrigymnasium.se/driverbot";

// This thing sets up the wifi and allows it to be connected a bit later
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  // Here, we define that the 4 following pins will be outputs
  // We also define where the servo is connected, and tell it write 90 degrees, straight forward, at the start of the program
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  servo.attach(15);
  servo.write(90);

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
  // Here, we write to the engine and servo with the data received from the mqtt broker
  // We also log the direction, velocity and the angle for the servo to be used for basic debugging in the serial monitor
  velint = vel.toInt();
  client.loop();
  digitalWrite(motorPinRightDir, dir.toInt());
  analogWrite(motorPinRightSpeed, velint);
  servo.write(deg.toInt());
  /*Serial.println(dir + vel + deg);*/
}


void callback(char* topic, byte* payload, unsigned int length) {

  data = "";
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    data += (char)payload[i];
  }

  Serial.println(data);

  vel = data.substring(0, 4);
  vel = vel.toInt()- 100;
  if (vel.toInt() > 0 ) {
    dir = "1";
  }
  else {
    vel = vel.toInt() * -1;
    dir = "0";
  }
  vel = vel.toInt() * 10.24;
  deg = data.substring(5,8);

  Serial.println(deg);
  Serial.println(vel);
  Serial.println(dir);
}
