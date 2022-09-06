#include <SPI.h>
#include <LoRa.h>
#include <string.h>
#include <Wire.h>
#define NSS 4
#define DIO0 3
#define RESET 2
int counter=1;
String data;
String Recived="500";
void setup() {
  Wire.begin();
  Serial.begin(9600);
   Wire.begin(8);  
   Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
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
  Serial.println("critical value :");
  Serial.print(Recived);
  boolean r=false;
  // try to parse packet
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    r=true;
    data="";
    while (LoRa.available()) {
      String LoRaData = LoRa.readString();
      Serial.print(LoRaData);
      
      data=data+LoRaData;
  
    }
    Serial.println();
    Serial.println( data.toInt());
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
  //delay(1000);
  //data="";
  if(r){
    LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Initializing OK!");
  Serial.print("Sending packet: ");
 

  // send packet
  LoRa.beginPacket();
  //LoRa.print("hello ");
  LoRa.write(0xAB);
 // LoRa.print("Id:1");
 if(data.toInt()>=Recived.toInt()){
  LoRa.print(1);
   Serial.println(1);
 }
 else{
  LoRa.print(0);
   Serial.println(0);
  }
  LoRa.endPacket();
  counter++;

  delay(2000);
}
}
void requestEvent() {
  char Buf[50];
  data.toCharArray(Buf, 50);
  Serial.print(Buf);
 Wire.write(Buf);  /*send string on request */
}
void receiveEvent(int howMany) {
  Recived=" ";
 while (0 <Wire.available()) {
    char c = Wire.read(); 
    Recived=Recived+c;/* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}
