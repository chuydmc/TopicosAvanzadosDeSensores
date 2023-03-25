#include <Wire.h>
#include <MPU6050.h>
int m=0.1;
int D=0.1;
float Io, Wx_deg_s; 
MPU6050 mpu;
 
void setup()
{
  Serial.begin(115200);
 
  Serial.println("Inicjalizacja MPU6050");
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Nie mozna znalezc MPU6050 - sprawdz polaczenie!");
    delay(500);
  }
 
  // Kalibracja żyroskopu
  mpu.calibrateGyro();
 
  // Ustawienie czułości
  mpu.setThreshold(3);
}
 
void loop()
{
  Vector rawGyro = mpu.readRawGyro();
  Vector normGyro = mpu.readNormalizeGyro();

  Serial.print(" Xraw = ");
  Serial.print(rawGyro.XAxis);
  Serial.print(" Yraw = ");
  Serial.print(rawGyro.YAxis);
  Serial.print(" Zraw = ");
  Serial.println(rawGyro.ZAxis);
    float Wx_deg_s =(float) rawGyro.XAxis/131.0;
    float Io=m*D*D;
    float F=Io*Wx_deg_s;
    Serial.println(F);
//  Serial.print(" Xnorm = ");
//  Serial.print(normGyro.XAxis);
//  Serial.print(" Ynorm = ");
//  Serial.print(normGyro.YAxis);
//  Serial.print(" Znorm = ");
//  Serial.println(normGyro.ZAxis);
// 
  delay(500);
}
