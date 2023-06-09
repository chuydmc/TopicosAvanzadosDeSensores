const int sensorPin = 2;  // Pin digital al que está conectado el sensor de flujo
volatile int pulseCount = 0;  // Contador de pulsos
float flowRate = 0.0;  // Tasa de flujo en L/min
float flowLiters = 0.0; // Tasa de flujo en litros
unsigned int flowMilliLitres = 0;  // Flujo acumulado en mL
unsigned long totalMilliLitres = 0;  // Flujo total acumulado en mL
unsigned long oldTime = 0;  // Tiempo desde la última medición

void setup()
{
  pinMode(sensorPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  Serial.begin(9600);
}

void loop()
{
  unsigned long currentTime = millis();
  if ((currentTime - oldTime) > 1000)  // Cada segundo
  {
    detachInterrupt(digitalPinToInterrupt(sensorPin));
    flowRate = pulseCount / 7.5;  // Cálculo de la tasa de flujo en L/min
    flowMilliLitres = (flowRate / 60) * 1000;  // Cálculo del flujo acumulado en mL
    flowLiters = (flowRate/60); // Cálculo del dlujo acumulado en litros
    totalMilliLitres += flowMilliLitres;  // Acumulación del flujo total en mL
    pulseCount = 0;  // Reiniciar el contador de pulsos
    oldTime = currentTime;  // Actualizar el tiempo anterior
    
    Serial.print("Tasa de flujo: ");
    Serial.print(flowRate);
    Serial.print(" L/min - Flujo acumulado: ");
    Serial.print(totalMilliLitres);
    Serial.println(" mL");
    attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  }
}

void pulseCounter()
{
  pulseCount++;
}