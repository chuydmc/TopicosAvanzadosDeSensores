#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int pitch=0;
int roll=0;
unsigned long past_time=0;

///////////////////////////////// Variables Red Neuronal ////////////////
const int node = 2;
const int input = 2;
const int outputs = 2;

float P[input][1];

float W1[node][input]={{0.589126343034730,0.631809411528709},
                      {6.87381904736029,0.149256513698125}};
   
float b1[node][1]={{-1.47238946983192},
                   {-0.600758415514133}};

float a1[node][1];

float W2[outputs][node]={{-1.04785469340080,3.42699228349477},
                        {2.22453626406980,-3.91380468685555}};


float b2[outputs][1]={{1.64381360693968},
                      {0.538490222206943}};
                      
float a2[outputs][1];

float aux=0.0;

int maxValue = 1023;
int minValue = 0;


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    delay(500);
  }
}

void loop() {

  /////////////////////////////// Primera Capa Entrada ///////////////////
  Vector normAccel = mpu.readNormalizeAccel();
  pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  roll = ((atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI);

  pitch=map(pitch,-180,180,0,1023);
  roll=map(roll,-180,180,0,1023);

  
  P[0][0]=dataNormalized((float) pitch,minValue,maxValue);
  P[1][0]=dataNormalized((float) roll,minValue,maxValue);

  ///////////////////////////// Segunda Capa //////////////////////////
  
  for(int i = 0 ; i<node; i++ ) {  
    aux=0.0;  
    for(int j = 0 ; j < input ; j++ ) { 
     aux=aux+W1[i][j]*P[j][0];
    }
    a1[i][0]=tansig(aux+b1[i][0]);
  }

    ///////////////////////////// Tercera Capa //////////////////////////
  
    for(int i = 0 ; i<outputs; i++ ) {  
    aux=0.0;  
    for(int j = 0 ; j < node ; j++ ) { 
     aux=aux+W2[i][j]*a1[j][0];
    }
    a2[i][0]=tansig(aux+b2[i][0]);
    }

//    if (a2[0][0]<=0 && a2[1][0]<=0){
//      Serial.println("Atras");
//     }
    if(a2[0][0]<=0 && a2[1][0]>0){
        Serial.println("Atras");
      } 
    else if(a2[0][0]>0 && a2[1][0]<=0){
        Serial.println("Adelante");
      }
    else
      {
        Serial.println("Estático");
      }

    delay(500);
  }

    
float tansig(float n)
{
  float a = exp(n);
  float b = exp(-n);
  return (a-b)/(a+b);
}

float dataNormalized(int inputData, int minData, int maxData) 
{
  float valueNorm;
  valueNorm = 2.0*(inputData-minData)/(maxData-minData)-1.0;
  return valueNorm;
}
