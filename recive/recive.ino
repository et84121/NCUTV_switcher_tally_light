/**
 * A Mirf example to test the latency between two Ardunio.
 *
 * Pins:
 * Hardware SPI:
 * MISO -> 12
 * MOSI -> 11
 * SCK -> 13
 *
 * Configurable:
 * CE -> 8
 * CSN -> 7
 *
 * Note: To see best case latency comment out all Serial.println
 * statements not displaying the result and load 
 * 'ping_server_interupt' on the server.
 */

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

void none_connect(){
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(10);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  delay(10);
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  delay(10);
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}

void setup() { 
  Serial.begin(9600);  

 //nRF
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"clie1");
  Mirf.payload = sizeof(int);
  Mirf.channel = 0;
  Mirf.config();
  Serial.println("RF_starting..."); 
}

int tally = 0;
int tally_program=0,
    tally_preview=0;
void loop() {
    Mirf.setTADDR((byte *)"serv1");
   
    unsigned long time = millis();
         
    while(!Mirf.dataReady()){
    //Serial.println("Waiting");
    if ( ( millis() - time ) > 1000 ) {
      Serial.println("Timeout on response from server!");
      none_connect();
      return;
      }
    }
    
    Mirf.getData((byte *)&tally);
    Serial.print("tally:");
    Serial.println(tally);
    
    tally_program = tally%10;
    tally_preview = (tally-tally%10-100)/10;
    
    Serial.print("tally_program:");
    Serial.println(tally_program);
    Serial.print("tally_preview:");
    Serial.println(tally_preview);
    
    if(tally_program == 1){
      digitalWrite(2,HIGH);
    }
    else{
      digitalWrite(2,LOW);
    }
    
    if(tally_preview == 1){
      digitalWrite(3,HIGH);
    }
    else{
      digitalWrite(3,LOW);
    }
//    delay(50);
}
