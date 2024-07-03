#define vel 9
#define dir 22
#define dir_pc 12

void setup() {
  // put your setup code here, to run once:
  pinMode(vel,OUTPUT);
  pinMode(dir,OUTPUT);
  pinMode(dir_pc,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(vel,20);
  digitalWrite(dir,0);
  digitalWrite(dir_pc,0);
  delay(200);

  analogWrite(vel,20);
  digitalWrite(dir,1);
  digitalWrite(dir_pc,1);
  delay(200);
}
