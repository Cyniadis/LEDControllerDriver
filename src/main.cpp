#include <Arduino.h>

#include <BluetoothSerial.h> //Header File for Serial Bluetooth, will be added by default into Arduino

static byte RED_PIN = 25;
static byte GREEN_PIN = 26;
static byte BLUE_PIN = 27;

static int RED_CHANNEL = 0;
static int GREEN_CHANNEL = 1;
static int BLUE_CHANNEL = 2;

static int PWM_FREQ = 5000;
static int PWM_RES = 8;

static int idx = 0;

BluetoothSerial btSerial; //Object for Bluetooth
int incoming;

void setup()
{
  Serial.begin(9600);
  
  // configure LED PWM functionalitites
  ledcSetup(RED_CHANNEL, PWM_FREQ, PWM_RES);
  ledcSetup(GREEN_CHANNEL, PWM_FREQ, PWM_RES);
  ledcSetup(BLUE_CHANNEL, PWM_FREQ, PWM_RES);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(RED_PIN, RED_CHANNEL);
  ledcAttachPin(GREEN_PIN, GREEN_CHANNEL);
  ledcAttachPin(BLUE_PIN, BLUE_CHANNEL);

  // Belutooth setup
  btSerial.begin("ESP32_LED_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  pinMode(LED_BUILTIN, OUTPUT); //Specify that LED pin is output
}

void loop()
{

  if (btSerial.available()) //Check if we receive anything from Bluetooth
  {
    incoming = btSerial.read(); //Read what we recevive
    Serial.print("Received:");
    Serial.println(incoming);

    if (incoming == 49)
    {
      digitalWrite(LED_BUILTIN, HIGH);
      btSerial.println("LED turned ON");
    }

    if (incoming == 48)
    {
      digitalWrite(LED_BUILTIN, LOW);
      btSerial.println("LED turned OFF");
    }
  }
  
   delay(20);
}