int C = 8;
int B = 10;
int D = 11;
int A = 12;

int num = 0;

void setup() {
  pinMode(C, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(A, OUTPUT);
}

void writeNumber(char num) {
  digitalWrite(D, (num >> 3)&1);
  digitalWrite(C, (num >> 2)&1);
  digitalWrite(B, (num >> 1)&1);
  digitalWrite(A, (num     )&1);
}

void loop() {
  writeNumber(num);
  num = (num+1)%10;
  delay(50);
}
