#include <SPI.h>
#include <LoRa.h>

// Brukbare GPIO-er for ESP32-S3
#define SCK     18
#define MISO    12
#define MOSI    11
#define SS      10
#define RST      9
#define DIO0     4
int i = 0;

void setup() 
{
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender starter");

  // Start SPI med egendefinerte pins
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setSPI(SPI);

  // Sett kontrollpinner for LoRa
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(868E6)) 
  {
    Serial.println("LoRa start feilet!");
    while (1);
  }

  Serial.println("LoRa initialisert");
}
int gammel_millionær;
void loop() 
{
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    Serial.print("Mottatt pakke: ");
    while (LoRa.available()) 
    {
      char c = (char)LoRa.read();
      Serial.print(c);
    }
    Serial.println();
  }
  else if (gammel_millionær <= millis() ) 
  {
    gammel_millionær = millis() + 1000;
    LoRa.beginPacket();
    LoRa.print(i);
    LoRa.endPacket();
    Serial.println(i);
    i++;
  }
}