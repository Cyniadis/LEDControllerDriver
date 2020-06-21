#include <Arduino.h>

#include <BluetoothSerial.h> //Header File for Serial Bluetooth, will be added by default into Arduino

static const byte RED_PIN = 13;
static const byte GREEN_PIN = 12;
static const byte BLUE_PIN = 14;

static const int RED_CHANNEL = 0;
static const int GREEN_CHANNEL = 1;
static const int BLUE_CHANNEL = 2;

static const int PWM_FREQ = 5000;
static const int PWM_RES = 8;

BluetoothSerial btSerial; //Object for Bluetooth

byte color[3];
int count = 0;
int data;

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
    data = btSerial.read(); //Read what we recevive

    color[count] = (byte)(data & 0xFF);

    if (count == 2)
    {
      ledcWrite(RED_CHANNEL, color[0]);
      ledcWrite(GREEN_CHANNEL, color[1]);
      ledcWrite(BLUE_CHANNEL, color[2]);

      Serial.println("Color:" + String(color[0]) + ", " + String(color[1]) + ", " + String(color[2]));
      count = 0;
    }
    else
    {
      count++;
    }
  }
  delay(10);
}