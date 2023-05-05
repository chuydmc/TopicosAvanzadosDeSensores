/*******************************************************************************
********************************************************************************
Sensor_AHT20
  Características de AHT20
    - Rango de medición de temperatura -40 ~ 85 °C
    - Rango de medición de humedad 0 ~ 100% HR
    - Salida digital, interfaz I2C
    - Excelente estabilidad a largo plazo
    - Respuesta rápida y fuerte capacidad antiinterferente.
  Especificación
    - Voltaje de funcionamiento: CC: 2,0-5,5 V
    - Rango de medición (humedad) 0 ~ 100% HR
    - Rango de temperatura: -40 ~ + 85 ℃
    - Precisión de humedad: ± 2% HR (25 ℃)
    - Precisión de temperatura ± 0,3 ℃
    - Resolución: Temperatura: 0,01 ℃, Humedad: 0,024% HR
********************************************************************************
Sensor_LM35
  Características de AHT20
    - • Calibrado Directamente en Celsius (Centígrados)
      • Factor de escala lineal + 10 mV/°C
      • Adecuado para aplicaciones remotas
      • Bajo costo debido al recorte a nivel de oblea
      • Consumo de corriente inferior a 60 μA
      • Autocalentamiento bajo, 0,08 °C en aire quieto
      • Sólo no linealidad ±¼°C típico
      • Salida de baja impedancia, 0,1 Ω para carga de 1 mA
  Especificación
    - Voltaje de funcionamiento: CC: 4 V a 30 V
    - Rango de temperatura: -55 °C a 150 °C
    - Precisión de temperatura 0,5 °C (a 25 °C)
    - Resolución: Temperatura: 0,01 ℃, Humedad: 0,024% HR
********************************************************************************
*******************************************************************************/
#include <Wire.h>
#include <AHT20.h>
AHT20 aht20;
#include <DHT.h>
#define DHTPIN 2 //PIN DONDE CONECTAR LA SEÑAL DEL SENSOR
#define DHTTYPE DHT11 //Definimos el tipo de DHT a utilizar 
DHT dht(DHTPIN, DHTTYPE);//Declaramos nuestra variable DHT
/*******************************************************************************
                  Declaracion de variables globales
*******************************************************************************/
float tempC; // Variable para almacenar el valor obtenido del sensor (0 a 1023)
float tempF; 
const int pinLM35 = 0; // Variable del pin de entrada del sensor (A0)
float vout;
/******************************************************************************/
void setup()
{
  pinMode(pinLM35,INPUT);
  Serial.begin(115200);
  Serial.println("LABEL,Tiempo,T_LM35:,T_DHT11:,T_AHT20:,H_AHT20:");
  Serial.println("Humidity AHT20 examples");
  Wire.begin(); //Inicia el I2C bus
  dht.begin();
  //Revisamos si el sensor AHT20 esta conectado 
  if (aht20.begin() == false)
  
  {
    Serial.println("AHT20 No detectado.");
    while (1);
  }
  Serial.println("AHT20 reconocido.");
}

void loop(){
/*******************************************
            Datos sensor DHT11
*******************************************/
  float H = dht.readHumidity();
  float T = dht.readTemperature();
  float EscTemp = dht.readTemperature(true);
/********************************************
            Datos sensor LM35
********************************************/
  /*Con analogRead leemos el sensor,
  recordando que es un valor de 0 a 1023*/
  vout = analogRead(pinLM35); 
  // Calculamos la temperatura con la fórmula
  float R_LM35 = (5.0 * vout)/1024.0;
  vout= (((R_LM35 - 0.5)*100)*(-1));
  tempC=vout ;
  tempF=(R_LM35*1.8)+32;
/*If a new measurement is available*************/
  if (aht20.available() == true)
  {
    /*******************************************
              Datos sensor AHT20
    *******************************************/
    float temperature = aht20.getTemperature();
    float humidity = aht20.getHumidity();
    /******************************
              Resultados
    ******************************/
    // Serial.print("Datos AHT20: ");
    // Serial.print("\n");
    // Serial.print("Temperatura: ");
    // Serial.print(temperature, 2);
    // Serial.print(" C\t");
    // Serial.print("Humedad: ");
    // Serial.print(humidity, 2);
    // Serial.print("% RH");
    // Serial.print("\n");
    /******************************/
    // Serial.print("Datos LM35: ");
    // Serial.print("\n");
    // Serial.print("Temperatura: ");
    // Serial.print(tempC);
    // Serial.print(" C\t");
    // Serial.print("Temperatura: ");
    // Serial.print(tempF);
    // Serial.print(" F\t");
    // Serial.print("\n");
    /******************************/
    // Serial.print("Datos DHT11");
    // Serial.print("\n");
    // Serial.print("Temperatura: ");
    // Serial.print(T);
    // Serial.print(" C\t");
    // Serial.print("Farenheit: ");
    // Serial.print(EscTemp);
    // Serial.print("  \t");
    // Serial.print("Humedad: ");
    // Serial.print(H);
    // Serial.print("\n");
    /******************************
          Resultados a Excel
    ******************************/
      Serial.print("DATA,TIME, ");
    /*****Resultados LM35*********/
      Serial.print(tempC);
      Serial.print(",");
    /*****Resultados DHT11********/
      Serial.print(T); 
      Serial.print(",");
    /*****Resultados AHT20********/
      Serial.print(temperature); 
      Serial.print(",");
      Serial.println(humidity);
    /******************************/
  }
  delay(500);
}
/**************************************************************************************************************************************
**************************************************************************************************************************************/