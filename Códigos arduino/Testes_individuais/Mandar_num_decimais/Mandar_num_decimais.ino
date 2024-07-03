#define vel_int 9
#define vel_dec 10

float teste = 10;

void setup() {
  pinMode(vel_int, OUTPUT);
  pinMode(vel_dec, OUTPUT);
  Serial.begin(115200);
}

void loop() {

  int T_int = teste/10;
  analogWrite(vel_int,T_int);
  //Serial.print(T_int);
  //Serial.print("  ");
  
  int T_dec = teste*10;
  int T_2digitos = T_dec % 100;
  analogWrite(vel_dec,T_2digitos);
  //Serial.println(T_2digitos);
}
