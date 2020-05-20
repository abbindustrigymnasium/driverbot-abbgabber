#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Servo.h>
Servo servo;
//First, we install some libraries to help control the driverbot
// The libraries are: a wifi client for the esp8266, a mqtt library to connect to the broker, and a servo library to control the servo

// Here, we define some pins for the engine
#define motorPinRightDir  0//D2
#define motorPinRightSpeed 5//D1
#define motorPinLeftDir 2
#define motorPinLeftSpeed 4

// Here, we define some variables that will be sent to the engine and servo later on
String vel = "";
String dir = "0";
int velint = 0;
String deg = "90";
String pay = "";

// Here, we have the ssid and password for the local wifi, which is necessary for the microcontroller to connect to the broker
const char* ssid = "edimax_2.4G";
const char* password =  "admin123";

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
  pinMode(motorPinLeftDir, OUTPUT);
  pinMode(motorPinLeftSpeed, OUTPUT);
  servo.attach(15);
  servo.write(90);

  Serial.begin(115200);

  //  This is where the microcontroller connects to the wifi
  WiFi.begin(ssid, password);

  //  While connecting, it writes that it is connecting to the wifi, and when connected, it says so
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  //  Defines some mqtt things, the broker and port we use and the function used to callback when a message is received
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  //  Here, we connect the microcontroller to the mqtt broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("CatGang", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

  //  Publishes a message in the topic, and also subscribes to the same topic where it will fetch data later
  client.publish("gabriel.bergdahl@abbindustrigymnasium.se/driverbot");
  client.subscribe("gabriel.bergdahl@abbindustrigymnasium.se/driverbot");

}
