int C = 8;
int B = 10;
int D = 11;
int A = 12;

char num = 0;

void setup() {
  pinMode(C, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(A, OUTPUT);
  writeNumber(num);
}

// Write a number to the nixie tube
// Digits above 9 will turn off the nixie tube bc of how the SN74141/K155ID1 works
void writeNumber(char num) {
  digitalWrite(D, (num >> 3)&1);
  digitalWrite(C, (num >> 2)&1);
  digitalWrite(B, (num >> 1)&1);
  digitalWrite(A, (num     )&1);
}

void loop() {
  num = (num+1)%10;
  writeNumber(num);
  delay(50);
}
