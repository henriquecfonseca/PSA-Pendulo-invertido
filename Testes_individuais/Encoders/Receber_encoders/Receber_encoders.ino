#include <SPI.h>

#define vel_int 9
#define vel_dec 10
#define dir 11
#define enable 8

#define DT_s 0.02

signed long Angulo = 0;
signed long Posicao = 0;

String recivedPos = ""; 
String recivedAng = ""; 

float graus = 0;
double PDes = -200;
double ADes = 0;


void setup() {
  Serial.begin(115200);
  Serial3.begin(115200);
  Serial2.begin(115200);
}

void loop() {

  //IMPORTAR VALORES Angulo
  while (Serial2.available() > 0){
    char ibyte = Serial2.read();
    recivedAng += ibyte;
    if (ibyte == '\n'){
      Angulo = recivedAng.toInt();
      //Serial.println(recivedAng);
      recivedAng = "";
      
    }
  }

  float graus = ((Angulo * 360.0) / 1600)-180;

  //IMPORTAR VALORES POSICAO
  while (Serial3.available() > 0){
    char ibyte = Serial3.read();
    recivedPos += ibyte;
    if (ibyte == '\n'){
      Posicao = recivedPos.toInt();
      recivedPos = "";
    }
  }

  double PosReal = ((Posicao*1000)/85832);

  Serial.print(graus); 
  Serial.print("  "); 
  Serial.println(PosReal); 
}
