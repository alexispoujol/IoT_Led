// LIBRARIES
#include <SPI.h>
#include <PubSubClient.h>
#include <Ethernet.h>
#include <Wire.h>




// ACTUATORS
// led



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
IPAddress server (54,152,234,238); // IP address of the mqtt server


//Setting up mqtt client
EthernetClient ethClient;
PubSubClient client(ethClient);


void setup() {
  //
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

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
  delay(1000);
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



void setColor(int couleur)
{
if (couleur == 0){
    red = 255;
    green = 255;
    blue = 255;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
   }
else if (couleur == 1){
    red = 255;
    green = 0;
    blue = 0;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
   }
else if (couleur == 2){
    red = 0;
    green = 255;
    blue = 0;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
   }
else if (couleur == 3){
    red = 0;
    green = 0;
    blue = 255;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
   }
else if (couleur == 4){
    int red = 0;
    int green = 0;
    int blue = 0;
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue); 
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
        state = 1;
        color = 0;
        setColor(color);
      }
      else if (message == "switch" && state == 1){
        state = 0;
        color = 4;
        setColor(color);
      }
      else if (message == "Red" && state == 1){
        color = 1;
        setColor(color);
      }
      else if (message == "Blue" && state == 1 ){
        color = 3;
        setColor(color);
      }
      else if (message == "Green" && state == 1){
        color = 2;
        setColor(color);
      }
      else if (message == "White" && state == 1){
        color = 0;
        setColor(color);
      }
  Serial.println();
}
