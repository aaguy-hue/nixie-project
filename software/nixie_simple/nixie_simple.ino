int C = 9;
int B = 10;
int D = 11;
int A = 12;

int digits [10][4] {
  {0,0,0,0},
  {0,0,0,1},
  {0,0,1,0},
  {0,0,1,1},
  {0,1,0,0},
  {0,1,0,1},
  {0,1,1,0},
  {0,1,1,1},
  {1,0,0,0},
  {1,0,0,1}
};

void setup() {
  // setup all the pins
  pinMode(C, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(A, OUTPUT);

  digitalWrite(D, LOW);
  digitalWrite(C, HIGH);
  digitalWrite(B, LOW);
  digitalWrite(A, LOW);
}

void loop() {
  // for(int i=0; i<10; i++) {
  //   digitalWrite(OUT_PIN_A,digits[i][3]);
  //   digitalWrite(OUT_PIN_B,digits[i][2]);
  //   digitalWrite(OUT_PIN_C,digits[i][1]);
  //   digitalWrite(OUT_PIN_D,digits[i][0]);
  //   delay(1000);
  // }
}
