#include <SPI.h>

#define vel_int 9
#define vel_dec 10
#define dir 22
#define enable 8
#define dir_pc 12

#define DT_s 0.001

signed long Angulo = 0;
signed long Posicao = 0;

String recivedPos = ""; 
String recivedAng = ""; 

float graus = 0;
double PDes = 0; 
double ADes = 0;
double PIDOut = 0;
double PID1 = 0;
int PIDAux = 0;

bool flag = HIGH;

double errAnt_a = 0;
double ErrInt_a = 0;
double ErrIntAnt_a = 0;
double graus_a = 0;

double errAnt_p = 0;
double ErrInt_p = 0;
double ErrIntAnt_p = 0;
double graus_p = 0;


double Ka = 18;
double a = 0.3686; 
double b = 5.276; 

double Kp = 0.005;//26.257;
double a_p = -6;
double b_p = 0;


void setup() {

  Serial.begin(115200);
  Serial3.begin(115200);
  Serial2.begin(115200);

  pinMode(vel_int,OUTPUT);
  pinMode(vel_dec,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(dir_pc,OUTPUT);
  pinMode(enable,OUTPUT);
}

void loop() {

  //IMPORTAR VALORES Angulo
  while (Serial2.available() > 0){
    char ibyte = Serial2.read();
    recivedAng += ibyte;
    if (ibyte == '\n'){
      Angulo = recivedAng.toInt();
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

  if (PosReal > -400 && PosReal < 400){
    digitalWrite(enable,LOW);
  }
  else{
    digitalWrite(enable,HIGH);
  }

  ////////////////ESCREVER OS KPS///////////////////////
  if (Serial.available() > 0) {
    // Read the incoming serial message
    String message = Serial.readStringUntil('\\');
    
    // Ensure message starts with 'a-'
    if (message.startsWith("a-")) {
      message.remove(0, 2); // Remove the leading 'a-'
      
      // Parse the message and extract the variables
      Ka = getValue(message, '-', 0).toFloat();
      Kp = getValue(message, '-', 1).toFloat();
      
      // Print the extracted values
      Serial.println(" ");
      Serial.print("Ka: "); Serial.println(Ka);
      Serial.print("Kp: "); Serial.println(Kp);
      Serial.println(" ");
    }
  }
  ////////////////////////////////////////////////////////////////

  PIDOut = PIDControlAng(ADes - graus) - PIDControlPos(PDes - PosReal);

  if (PIDOut > 0.0){
    flag = HIGH;
    PIDAux = (float)( PIDOut);
    digitalWrite(dir, HIGH);
    digitalWrite(dir_pc, HIGH);
    }
  else { 
    flag = LOW;
    PIDAux = (float)(-PIDOut);
    digitalWrite(dir, LOW);
    digitalWrite(dir_pc, LOW);
  }

  if (PIDAux>800){
    PIDAux = 800;
  }
  else{
    PIDAux = PIDAux;
  } 

  int PID_int = PIDAux/10;
  analogWrite(vel_int, PID_int);

  int PID_dec = PIDAux*10;
  int PID_2digitos = PID_dec % 100;
  analogWrite(vel_dec, PID_2digitos);

  Serial.print(graus); 
  Serial.print("  "); 
  Serial.println(PosReal); 
}


String getValue(String data, char separator, int index) {
  int startIndex = 0;
  int endIndex = -1;
  int currentIndex = 0;
  
  while (currentIndex <= index) {
    startIndex = endIndex + 1;
    endIndex = data.indexOf(separator, startIndex);
    if (endIndex == -1) {
      endIndex = data.length();
    }
    currentIndex++;
  }
  return data.substring(startIndex, endIndex);
}


////////////// PID Angulo ///////////////////////
double PIDControlAng(double err_a) {
  // para criar o código do controlador   
  double dErr_a = (err_a - errAnt_a)/DT_s;

  if (graus < -20 || graus > 20) {
    double ErrInt_a = 0;
  } else {
    double ErrInt_a = ErrIntAnt_a + err_a * DT_s;
  }

  double Cout = Ka*(a+b)*err_a + Ka*dErr_a + Ka*a*b*ErrInt_a;

  errAnt_a = err_a;
  ErrIntAnt_a = ErrInt_a;
  return Cout;
}


////////////// PID POSICAO ///////////////////////
double PIDControlPos(double err_p) {
  // para criar o código do controlador   
    double dErr_p = (err_p - errAnt_p)/DT_s;

  if (graus < -10 || graus > 10) {
    double ErrInt_p = 0;
  } else {
    double ErrInt_p = ErrIntAnt_p + err_p * DT_s;
  }

  double Cout = Kp*(a_p+b_p)*err_p + Kp*dErr_p;
  
  errAnt_p = err_p;
  ErrIntAnt_p = ErrInt_p;

  return Cout;
}
