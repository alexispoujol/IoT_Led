// LIBRARIES

#include <SPI.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <Wire.h>


// ACTUATORS
// led
int LEDPIN = 8;
int state = 0;

/*
// RGB LED
int redPin = 11;
int greenPin = 10;
int bluePin = 9;
int state = 1;
int color = 3;
int red = 0;
int green = 0;
int blue = 0;
*/


// SERVER
// MQTT connection
#define MQTT_SERVER "m14.cloudmqtt.com"       //MQTT Server
#define MQTT_TOPIC "Arduino"                   //TOPIC to Publish
const char* mqttUser = "gzjltozl";
const char* mqttPassword = "o3gxcWnlIX3y";

//Ethernet Shield Setup - Start.
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 4);       // IP address of the arduino
IPAddress server(54,152,234,238);   // IP address of the mqtt server


//Setting up mqtt client
EthernetClient ethClient;
PubSubClient client(ethClient);


void setup() {
  //RGB LED
  /*
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
   */
   
  // initialize led
  pinMode(LEDPIN, OUTPUT);
  digitalWrite(LEDPIN, LOW);
  Serial.println("bite");
  //initialize MQTTserver
  Serial.println("Setting up server");
  Ethernet.begin(mac, ip);
  delay(2000);

  Serial.println("Setting up server");
  client.setServer(server,12653);
  client.setCallback(callback);
  MQTT_connect();

  //subscribe
  boolean action = client.subscribe("led",1);
}


void loop() {
  

  client.loop();
  delay(2000);
}


// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
     Serial.println("Not connected");
     boolean connectionResult = client.connect("pjd-mqtt",mqttUser,mqttPassword,MQTT_TOPIC,1,0,"Test Connection");
     Serial.println(connectionResult);
     Serial.println("MQTT Connected! ");      if(!client.connected()){

  }
  
}


void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String message = "";
    for (int i=0;i<length;i++) {
      char receivedChar = (char)payload[i];
      message += receivedChar;
      Serial.print(receivedChar);
    }
      if (message == "switch" && state == 0){
        digitalWrite(LEDPIN, HIGH);
        state = 1;
      }
      else if (message == "switch" && state == 1){
        digitalWrite(LEDPIN, LOW);
        state = 0;
      }
  Serial.println();
}
