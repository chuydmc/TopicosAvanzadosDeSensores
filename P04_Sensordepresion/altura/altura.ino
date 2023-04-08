
#include <Adafruit_MPL3115A2.h>

Adafruit_MPL3115A2 baro;

void setup() {
  Serial.begin(9600);
  analogRead(4);
  while(!Serial);
  Serial.println("Adafruit_MPL3115A2 test!");

  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }

  baro.setSeaPressure(1013.26);
}

void loop() {

  float altitude = baro.getAltitude();
//muestra valor en metros de altura cada 1 segundo
   Serial.print(altitude); 
   Serial.print("\n"

   );
   delay(1000);
}