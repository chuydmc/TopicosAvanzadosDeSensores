#include <Adafruit_MPL3115A2.h>
Adafruit_MPL3115A2 baro;
////////////////////////////////////////////////////////////////////////////////////////////////////
int gas = A2;//Pin donde establecemos la señal de datos del sensor de gas
float hg;
////////////////////////////////////////////////////////////////////////////////////////////////////
int PIN_TemperaturaAmbiente = A1; //LM35
////////////////////////////////////////////////////////////////////////////////////////////////////
int PIN_HumedadTierra = A0; //HL-69 ó YL-69
////////////////////////////////////////////////////////////////////////////////////////////////////
#include <Adafruit_AHTX0.h>
Adafruit_AHTX0 aht;
///////////////////////////////////////////////////////////////////////////////////////////////////
int Dato_Recibido;
int Led = 8;
int EV = 8;
////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
   Serial.begin(9600);
 // Serial.println("Adafruit AHT10/AHT20 demo!");

  if (! aht.begin()) {
    //Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  //Serial.println("AHT10 or AHT20 found");
  
  Serial.begin(9600);
  while(!Serial);
  //Serial.println("Adafruit_MPL3115A2 test!");

  if (!baro.begin()) {
    //Serial.println("Could not find sensor. Check wiring.");
    while(1);
  }

  pinMode(EV,OUTPUT);

  // use to set sea level pressure for current location
  // this is needed for accurate altitude measurement
  // STD SLP = 1013.26 hPa
  baro.setSeaPressure(1013.26);
}

void loop() {
  float pressure = baro.getPressure();
   Serial.print(pressure);Serial.print(";");
   hg= analogRead(gas);
  //float gay = (hg/1024.0)*1000.0; //Nota: esta operación es para que te mande los datos del sensor de gas ya bien  
  Serial.print(hg);Serial.print(";");
  int TemperaturaAmbiente = analogRead(PIN_TemperaturaAmbiente);
  Serial.print(TemperaturaAmbiente);Serial.print(";");
  int HumedadTierra = analogRead(PIN_HumedadTierra);
  Serial.print(HumedadTierra);Serial.print(";");
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);
  Serial.print(humidity.relative_humidity);Serial.println(";");

  if (Serial.available()>0){
    Dato_Recibido = Serial.read();
    if(Dato_Recibido==48){ /*/ Codigo ASCII del 0 = 48 /*/ 
    digitalWrite(EV, LOW);
    }
    if(Dato_Recibido==49){ /*/ Codigo ASCII del 1 = 49 /*/
    digitalWrite(EV, HIGH);
    }
  }



  
  delay(1000);
  

  
  
}
