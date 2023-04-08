#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro;
void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Adafruit_MPL3115A2 test!");

  if (!baro.begin()) {
    Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }
  baro.setSeaPressure(1013.26);
}

void loop() {
  float Resp=287.0500676; // constante de gas especifica de aire seco
  float pressure = baro.getPressure();
  float altitude = baro.getAltitude();
  float temperature = baro.getTemperature();
  float t = 237.15 + temperature; // grados a kelvin
  float press = pressure*100; // hecto pascales a pascales 
  float p = (press/(Resp*t)); // formula de la densidad de aire

  Serial.println("-----------------");
  Serial.print("pressure = "); Serial.print(pressure); Serial.println(" hPa");
  Serial.print("altitude = "); Serial.print(altitude); Serial.println(" m");
  Serial.print("temperature = "); Serial.print(temperature); Serial.println(" C");
  Serial.print("densidad = "); Serial.print(p); Serial.println(" kg/m3 ");
  delay(250);
}