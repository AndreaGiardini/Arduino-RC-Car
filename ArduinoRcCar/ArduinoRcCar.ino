#include <SPI.h>
#include <WiFi.h>
//#include <WiFiUdp.h>

char ssid[] = "natspot";     //  your network SSID (name)
char pass[] = "123456789";  // your network password
int status = WL_IDLE_STATUS;     // the Wifi radio's status

IPAddress server(192,168,1,1);
unsigned int remotePort = 8080;

//Motor pins
int enableA = 53;
int pinA1 = 51;
int pinA2 = 49;

int enableB = 43;
int pinB1 = 47;
int pinB2 = 45;

WiFiClient client;
char c;

void setup() {
  Serial.begin(9600);

  //Setup motors
  pinMode(enableA, OUTPUT);
  pinMode(pinA1, OUTPUT);
  pinMode(pinA2, OUTPUT);

  pinMode(enableB, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinB2, OUTPUT);

  //Setup Wifi
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }

  Serial.println("You're connected to the network");
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  client.connect(server, remotePort);

  enableMotors();

  Serial.println("Entering the loop");
}

void loop() {

  if(client.available()){
    client.readBytes(&c, 1);
    Serial.write(c);

    if (c == 'A') {
      forward();
      //Serial.println("Avanti");
    } else if (c == 'I') {
      backward();
      //Serial.println("Indietro");
    } else if (c == 'D') {
      turnRight();
      //Serial.println("Destra");
    } else if (c == 'S') {
      turnLeft();
      //Serial.println("Sinistra");
    } else {
      brake();
      //Serial.println("Stop");
    }

  }

}

//Define Low Level H-Bridge Commands

//enable motors
void motorAOn()
{
 digitalWrite(enableA, HIGH);
}

void motorBOn()
{
 digitalWrite(enableB, HIGH);
}

 //disable motors
void motorAOff()
{
 digitalWrite(enableB, LOW);
}

void motorBOff()
{
 digitalWrite(enableA, LOW);
}

 //motor A controls
void motorAForward()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, LOW);
}

void motorABackward()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, HIGH);
}

//motor B contorls
void motorBForward()
{
 digitalWrite(pinB1, HIGH);
 digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
 digitalWrite(pinB1, LOW);
 digitalWrite(pinB2, HIGH);
}

//coasting and braking
void motorACoast()
{
 digitalWrite(pinA1, LOW);
 digitalWrite(pinA2, LOW);
}

void motorABrake()
{
 digitalWrite(pinA1, HIGH);
 digitalWrite(pinA2, HIGH);
}

void motorBCoast()
{
 digitalWrite(pinB1, LOW);
 digitalWrite(pinB2, LOW);
}

void motorBBrake()
{
 digitalWrite(pinB1, HIGH);
 digitalWrite(pinB2, HIGH);
}

//Define High Level Commands

void enableMotors()
{
 motorAOn();
 motorBOn();
}

void disableMotors()
{
 motorAOff();
 motorBOff();
}

void forward()
{
 motorAForward();
 motorBForward();
 //delay(time);
}

void backward()
{
 motorABackward();
 motorBBackward();
 //delay(time);
}

void turnLeft()
{
 motorABackward();
 motorBForward();
 //delay(time);
}

void turnRight()
{
 motorAForward();
 motorBBackward();
 //delay(time);
}

void coast()
{
 motorACoast();
 motorBCoast();
 //delay(time);
}

void brake()
{
 motorABrake();
 motorBBrake();
 //delay(time);
}
