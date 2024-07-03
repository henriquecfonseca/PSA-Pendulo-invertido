#include <SPI.h>

const int slaveSelectEnc1 = 8;
signed long encoder1count = 0;
signed long encod_pos = 0;

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
  initEncoders();
  clearEncoderCount();
}

void loop() {
  encoder1count = readEncoder(1);
  char buff[10];
  ltoa(encoder1count,buff,10);
  Serial.println(buff);
}
