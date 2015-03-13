#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

Adafruit_PCD8544 display = Adafruit_PCD8544(2,3,4,5,6);

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

#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
// MAC address and IP address for this *particular* Ethernet Shield!
// MAC address is printed on the shield
// IP address is an available address you choose on your subnet where the switcher is also present:
byte mac[] = {0x90, 0xA2, 0xDA, 0x00, 0xE8, 0xE9 };		// <= SETUP
IPAddress ip(192, 168, 0, 99);				// <= SETUP
#include <ATEM.h>
ATEM AtemSwitcher(IPAddress(192, 168, 0, 240), 56417);  // <= SETUP (the IP address of the ATEM switcher)
void setup() { 
  digitalWrite(1,HIGH);
  display.begin();
  // init done

  // you can change the contrast around to adapt the display
  // for the best viewing!
  display.setContrast(50);
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
  
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0,0);
  display.println("Starting....");
  display.display();
  
  Ethernet.begin(mac,ip);
  Serial.begin(9600);  

  // Initialize a connection to the switcher:
  AtemSwitcher.serialOutput(true);
  AtemSwitcher.connect();
  while(AtemSwitcher.isConnectionTimedOut()){
   Serial.println("Could not find AtemSwitcher");
  }
 //nRF
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"serv1");
  Mirf.payload = sizeof(int);
  Mirf.channel = 0;
  Mirf.config();
  
  Serial.println("system have done...");
  display.clearDisplay();
  display.println("system have done..."); 
  display.display();
}
void loop() {
  while(AtemSwitcher.isConnectionTimedOut()){
   Serial.println("Could not find AtemSwitcher");
  }
  
    // Check for packets, respond to them etc. Keeping the connection alive!
  AtemSwitcher.runLoop();
    // the first digit is ProgramTally ,second digit is PreviewTally
  int tally1 = AtemSwitcher.getProgramTally(8)+(10*AtemSwitcher.getPreviewTally(8))+100;
  int tally2 = AtemSwitcher.getProgramTally(7)+(10*AtemSwitcher.getPreviewTally(7))+100;
  int tally3 = AtemSwitcher.getProgramTally(4)+(10*AtemSwitcher.getPreviewTally(4))+100;
 
   
  if(!Mirf.isSending()){
    Mirf.channel = 0;
    Mirf.config();
    Mirf.setTADDR((byte *)"clie1");
    Mirf.send((byte *)&tally1);
    Serial.println("data1 sent.");
    
    Mirf.channel = 2;
    Mirf.config();
    Mirf.setTADDR((byte *)"clie2");
    Mirf.send((byte *)&tally2);
    Serial.println("data2 sent.");
    
    Mirf.channel = 4;
    Mirf.config();
    Mirf.setTADDR((byte *)"clie3");
    Mirf.send((byte *)&tally3);
    Serial.println("data3 sent.");
  
  }
  display.clearDisplay();
  display.print("data1:");
  display.println(tally1);
  display.print("data2:");
  display.println(tally2);
  display.print("data3:");
  display.println(tally3);  
  display.display();
  
  delay(50);

}
