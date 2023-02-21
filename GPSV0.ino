#include <SoftwareSerial.h>
int RXPin = 4;
int TXPin = 3;
int GPSBaud = 9600;
SoftwareSerial gpsSerial(RXPin,TXPin);
void setup(){
  Serial.begin(9600);
  gpsSerial.begin(9600);
}
void loop(){
  while(gpsSerial.available()>0)
  Serial.write(gpsSerial.read());
}
