#include <SPI.h> //står at er feil må ha lastet ned disse to
#include <LoRa.h>


// Samme GPIO-er som sender
#define SCK     18
#define MISO    12
#define MOSI    11
#define SS      10
#define RST      9
#define DIO0     4
int disnuts = 0;


void setup() {
  Serial.begin(115200);
  while (!Serial);


  Serial.println("LoRa Mottaker starter");


  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setSPI(SPI);


  LoRa.setPins(SS, RST, DIO0);
 
  if (!LoRa.begin(868E6)) {
    Serial.println("LoRa start feilet!");
    while (1);
  }


  Serial.println("LoRa klar til å motta");
}


void loop() {
  int packetSize = LoRa.parsePacket();
  String s = "";
  if (packetSize) {
    Serial.print("Mottatt pakke: ");
   


    while (LoRa.available()) {
      char c = (char)LoRa.read();
      s += c;
      Serial.print(c);
    }




    delay(100);
    LoRa.beginPacket();
    LoRa.print(s);
    LoRa.endPacket();


    disnuts++;


   
    Serial.println(); // Ny linje etter pakke
    Serial.print("RSSI: ");
    Serial.println(LoRa.packetRssi());
    Serial.print("SNR:  ");
    Serial.print(LoRa.packetSnr());
    Serial.println("dB");
   
  }
 
}

