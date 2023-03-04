#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

void setup() {
  Serial.begin(115200);


  while (! Serial) {
    delay(1);
  }
  
  Serial.println("----- VL53L0X -----");
  if (!lox.begin()) {
    Serial.println(F("error de inicializacion"));
    while(1);
  }
  
  Serial.println(F("VL53L0X ejemplo rango\n\n")); 
}


void loop() {
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Leyendo distancia ... ");
  lox.rangingTest(&measure, false); 

  if (measure.RangeStatus != 4) {  
    Serial.print("Distancia  (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" fuera de rango ");
  }
    
  delay(500);
}
