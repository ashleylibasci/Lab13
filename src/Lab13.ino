#include "oled-wing-adafruit.h"
#include "Particle.h"

SYSTEM_THREAD(ENABLED);

OledWingAdafruit display;

#include "MQTT.h"

void callback(char *topic, byte *payload, unsigned int length);

MQTT client("lab.thewcl.com", 1883, callback);

void setup()
{
  Serial.begin(9600);

  display.setup();
  display.clearDisplay();
  display.display();
}

void loop()
{
  display.loop();

  if (client.isConnected())
  {
    client.loop();
  }
  else
  {
    client.connect(System.deviceID());
    client.subscribe("ashleyLab13");
    client.publish("ashleyLab13", "welcome!!");
  }
}

void callback(char *topic, byte *payload, unsigned int length)
{
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.printf("%s", p);
  Serial.println();

  if (String(p).equals("1"))
  {
    Serial.println("1");
  }
  else if (String(p).equals("0"))
  {
  }
  else
  {
    Serial.println(p);
  }
}