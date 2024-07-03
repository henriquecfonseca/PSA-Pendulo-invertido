#include <SPI.h>

#define vel 9
#define dir 22
#define enable 8

#define DT_s 0.02

int vDes1 = 1000;
int vDes2 = -1000;

int vDes = 0;
bool flag = HIGH;
double PIDOut = 0;
int PIDAux = 0;
volatile int count = 0;
double Pos = 0;
unsigned long iniTime = 0; unsigned long pastTime = 0; unsigned long endTime = 0;// para o controlo do tempo de amostragem
unsigned long iTime = 0; unsigned long eTime = 0;
signed long Posicao = 0;

int dt = 1000; // intervalos de tempo para variação da posição desejada
 
int i = 0;
double t = 0;
double s = 0;

String recivedPos = ""; 

void setup() {

  pinMode(vel,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(enable,OUTPUT);

  Serial.begin(115200);
  Serial3.begin(115200);

  s=millis(); // inicio do tempo
  establishContact();
}


void loop() {

  t=millis()-s;

  iniTime = millis();
  float iniT = float(iniTime) * 0.001;

   while (eTime < iTime + DT_s*1000) { // espera para manter o tempo de amostragem fixo em DT_s
    eTime  = millis();
   }
    // define um conjunto de pulsos para definir a posição angular desejada
    endTime  = millis();  


  //IMPORTAR VALORES POSICAO
  while (Serial3.available() > 0){
    char ibyte = Serial3.read();
    recivedPos += ibyte;
    if (ibyte == '\n'){
      Posicao = recivedPos.toInt();
      //Serial.println(recivedPos);
      recivedPos = "";
      
    }
  }

  double PosReal = ((Posicao*1000)/85832);

  if (PosReal > -100 && PosReal < 700){
    digitalWrite(enable,LOW);
  }
  else{
    digitalWrite(enable,HIGH);
  }

  if (endTime <dt){ vDes=0; }
  if (endTime >=dt && endTime < 2*dt){ vDes=0; }
  if (endTime >=2*dt && endTime < 2.25*dt){ vDes=vDes1; } 
  if (endTime >=2.25*dt && endTime < 4*dt){ vDes=0; } 
  if (endTime >=4.25*dt && endTime < 4.5*dt){ vDes=vDes2; } 
  if (endTime >=4.5*dt && endTime < 8*dt){ vDes=0; }


  if (vDes >= 0.0){
    flag = HIGH;
    PIDAux = (float)(vDes);
    digitalWrite(dir,0);
    }
  else { 
    flag = LOW;
    PIDAux = (float)(-vDes);
    digitalWrite(dir,1);
  }
  analogWrite(vel,PIDAux/10);
  
  Serial.println((float)t); //T
  Serial.println((float)vDes); //Vin
  Serial.println((float)PosReal); //p
}

void establishContact() {
     while (Serial.available() <= 0) {
       Serial.println('A');   // send a capital A
       delay(300);
     }
 }



