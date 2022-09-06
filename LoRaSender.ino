#include <SPI.h>
#include <LoRa.h>
#define NSS 4
#define DIO0 3
#define RESET 2

int sensordata = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(NSS, RESET, DIO0);

  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  //Serial.println("LoRa Sender");
 // LoRa.setPins(NSS, RESET, DIO0);

  while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
  Serial.print("Sending packet: ");
  Serial.println(sensordata);
sensordata=analogRead(A0);
  // send packet
  LoRa.beginPacket();
  //LoRa.print("hello ");
  LoRa.print(sensordata);
  LoRa.endPacket();

  //counter++;

  delay(2000);
}
