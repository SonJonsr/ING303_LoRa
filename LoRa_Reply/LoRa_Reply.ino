#include <SPI.h>                    //står at er feil må ha lastet ned disse to
#include <LoRa.h>

// jeg bruker ESP32-S3 Dev Board

// Samme GPIO-er som sender
#define SCK     18
#define MISO    12
#define MOSI    11
#define SS      10
#define RST      9
#define DIO0     4

void setup() {
  Serial.begin(115200);
  while (!Serial);                    // venter til Serial har startet

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
  if (packetSize) {                   // venter bare på ny pakke
    Serial.print("Mottatt pakke: ");

    while (LoRa.available()) {        //leser inn meldingen
      char c = (char)LoRa.read(); 
      s += c;
      Serial.print(c);
    }

    delay(100);                       // venter litt før den sender samme melding tilbake
    LoRa.beginPacket();
    LoRa.print(s);
    LoRa.endPacket();
    Serial.println();
     
    Serial.print("RSSI: ");           // viser litt praktisk info
    Serial.println(LoRa.packetRssi());
    Serial.print("SNR:  ");
    Serial.print(LoRa.packetSnr());
    Serial.println("dB");
   
  }
 
}
