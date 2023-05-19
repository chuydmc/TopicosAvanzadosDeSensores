int sensorPin = A0; // Pin analógico al que se conecta el sensor
float sensorValue; // Variable para almacenar el valor leído del sensor
int i=0;
void setup() {
  Serial.begin(9600); // Iniciar comunicación serial a 9600 
  Serial.println("LABEL,Tiempo,i,ValorSensor");
}

void loop() {
  


  // Leer el valor analógico del sensor
  sensorValue = analogRead(sensorPin);

  // Convertir el valor analógico a una concentración de gas (en ppm)
  float gasPPM = (sensorValue / 1024.0) * 10000.0;

  // Imprimir el valor de la concentración de gas en ppm
  //Serial.print("Concentración de gas (en ppm): ");

  Serial.print("DATA,TIME, ");
  Serial.print(i);
  Serial.print(",");
  Serial.println(gasPPM);
  // Esperar 1 segundo antes de volver a leer el sensor

  i++;

  delay(100);
}
