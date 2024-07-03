#include <SPI.h>

const int slaveSelectEnc1 = 38;
signed long encoder1count = 0;
const int resolucaoEncoder = 1600;

#define DT_s 0.02
int dt = 1000; // intervalos de tempo para variação da posição desejada
 
unsigned long iniTime = 0; unsigned long pastTime = 0; unsigned long endTime = 0;// para o controlo do tempo de amostragem
unsigned long iTime = 0; unsigned long eTime = 0;
int i = 0;
double t = 0;
double s = 0;

void initEncoders() {
  pinMode(slaveSelectEnc1, OUTPUT);
  digitalWrite(slaveSelectEnc1, HIGH);
  SPI.begin();
  digitalWrite(slaveSelectEnc1, LOW);
  SPI.transfer(0x88);
  SPI.transfer(0x03);
  digitalWrite(slaveSelectEnc1, HIGH);
}

long readEncoder(int encoder) {
  unsigned int count_1, count_2, count_3, count_4;
  long count_value;  
  if (encoder == 1) {
    digitalWrite(slaveSelectEnc1, LOW);
    SPI.transfer(0x60);
    count_1 = SPI.transfer(0x00);
    count_2 = SPI.transfer(0x00);           
    count_3 = SPI.transfer(0x00);           
    count_4 = SPI.transfer(0x00);
    digitalWrite(slaveSelectEnc1, HIGH);
  }
  count_value = (count_1 << 8) + count_2;
  count_value = (count_value << 8) + count_3;
  count_value = (count_value << 8) + count_4;
  return count_value;
}

void clearEncoderCount() {
  digitalWrite(slaveSelectEnc1, LOW);  
  SPI.transfer(0x98);    
  SPI.transfer(0x00);
  SPI.transfer(0x00);           
  SPI.transfer(0x00);           
  SPI.transfer(0x00);  
  digitalWrite(slaveSelectEnc1, HIGH);
  delayMicroseconds(100);
  digitalWrite(slaveSelectEnc1, LOW);  
  SPI.transfer(0xE0);    
  digitalWrite(slaveSelectEnc1, HIGH);   
}

void setup() {
  Serial.begin(115200);
  //Serial3.begin(115200);
  initEncoders();
  //Serial.println("Encoders Initialized...");  
  clearEncoderCount();
  //Serial.println("Encoders Cleared...");
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

  delay(100);
  encoder1count = readEncoder(1);
  float graus = ((encoder1count * 360) / resolucaoEncoder) + 180;
  //float posicao = ((encoder1count*1000)/83832);
  //Serial.println(posicao); 
  Serial.println((float)t);
  Serial.println((float)graus);
}

void establishContact() {
     while (Serial.available() <= 0) {
       Serial.println('A');   // send a capital A
       delay(300);
     }
 }
