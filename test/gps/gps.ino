/* This sample code demonstrates the normal use of a TinyGPS object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
#include <SoftwareSerial.h>
#include <TinyGPS.h>

TinyGPS gps;
SoftwareSerial ss(4, 3);

void setup(){
  ss.begin(9600);
  Serial.begin(9600);
}

unsigned long conta = 0;
float test = 10.101010;

void loop(){
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

   while (ss.available()){
    char c = ss.read();
    if (gps.encode(c)) // Did a new valid sentence come in?
      newData = true;
  }

  if (newData){
    float flat, flon;
    unsigned long age, date, timeofday;
    // Get latitude and longitude
    gps.f_get_position(&flat, &flon, &age);
    // Get current time
    gps.get_datetime(&date, &timeofday, &age);
    // Get number of satellites
    gps.satellites();
    // Get precision
    gps.hdop();
    Serial.print("Dato x: ");
    Serial.print(flat,6);
    Serial.print(" , y: ");
    Serial.print(flon,6);
    Serial.print("\n");
  }
  // Get statistics on the GPS device
  gps.stats(&chars, &sentences, &failed);
  conta = conta + 1;
  if (conta > 50000){
    Serial.println("Stats: "+String(sentences)+" , char: "+String(chars)+" , fail:  "+String(failed));
    conta = 0;
  }
}
