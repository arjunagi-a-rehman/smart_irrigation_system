#include <SPI.h>
#include <LoRa.h>
#include <string.h>
#include <Wire.h>
#define NSS 4
#define DIO0 3
#define RESET 2

String data;
void setup() {
  Wire.begin();
  Serial.begin(9600);
   Wire.begin(8);  
   Wire.onRequest(requestEvent);
  while (!Serial);

  Serial.println("LoRa Receiver");
  LoRa.setPins(NSS, RESET, DIO0);

   while (!LoRa.begin(866E6)) {
    Serial.println(".");
    delay(500);
  }
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");
}

void loop() {
  
  // try to parse packet
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    data="";
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
      
      data=data+LoRaData;
  
    }
    if(data.length()<2){
      data='00'+data;
    }
    
    
   //  // sends x
    //char buffer[32];
    //data.toCharArray(buffer, 32);
     
     //Wire.write(buffer); 
  
    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    
    
  }
  
  //data="";
}
void requestEvent() {
  char Buf[50];
  data.toCharArray(Buf, 50);
  Serial.print(Buf);
 Wire.write(Buf);  /*send string on request */
}
