#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

float tempMax = -100.0;
float tempMin = 100.0;
float tempSum = 0.0;
int count = 0;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  Wire.begin();
  baro.begin();
}

void loop() {
  baro.getTemperature();;
  float temp = baro.getTemperature(); // Leer temperatura
  if (temp > tempMax) {
    tempMax = temp; // Aactualizo
  }
  if (temp < tempMin) {
    tempMin = temp; // Actualizo
  }
  tempSum += temp; // 
  count++; //sumo e incremento
  delay(1000); // 1 segundo espero
  if (count == 86400) { // para dia completo ese es el contador
    float tempAvg = tempSum / count; //temperatura promedio del dia 
    float unidadesCalor = (tempMax + tempMin) / 2.0 - 10.0; // unidades de calor
    Serial.print("Temperatura máxima: ");
    Serial.print(tempMax);
    Serial.println(" °C");
    Serial.print("Temperatura mínima: ");
    Serial.print(tempMin);
    Serial.println(" °C");
    Serial.print("Temperatura promedio: ");
    Serial.print(tempAvg);
    Serial.println(" °C");
    Serial.print("Unidades de calor: ");
    Serial.println(unidadesCalor);
    if (unidadesCalor >= 153.24) {
      Serial.println("La planta se encuentra en la etapa fenológica de maduración");
    } else if (unidadesCalor >= 112.77) {
      Serial.println("La planta se encuentra en la etapa fenológica de llenado de vainas");
    } else if (unidadesCalor >= 99.31) {
      Serial.println("La planta se encuentra en la etapa fenológica de formación de vaina");
    } else if (unidadesCalor >= 91.33) {
      Serial.println("La planta se encuentra en la etapa fenológica de floración");
    } else if (unidadesCalor >= 64.41) {
      Serial.println("La planta se encuentra en la etapa fenológica de formación de guías");
    } else if (unidadesCalor >= 12.89) {
      Serial.println("La planta se encuentra en la etapa fenológica de emergencia");
    } else {
      Serial.println("La planta se encuentra en la etapa fenológica de dormancia");
    }
    tempMax = -100.0; // reinic tem max
    tempMin = 100.0; // rein min
    tempSum = 0.0; // suma a 
    count = 0; // limpio contador
  }
}