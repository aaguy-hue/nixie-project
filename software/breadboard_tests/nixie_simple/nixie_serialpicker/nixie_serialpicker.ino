// Tube 1 constants
// const int C = 12;
// const int B = 11;
// const int D = 10;
// const int A = 9;

// Tube 2 constants
// const int A = 8;
// const int D = 7;
// const int B = 6;
// const int C = 5;

// Tube 3 constants
const int A{4}, B{2}, C{A7}, D{3};

bool scroll = false;
char num = 4;

const unsigned long intervalMillis = 50;
unsigned long previousMillis = 0;

void setup() {
  pinMode(C, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(A, OUTPUT);
  writeNumber(num);

  Serial.begin(9600);
  Serial.println("Enter a number between 0 and 9 to display on the nixie tube, or '10' to turn it off.");
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
  if (Serial.available()) {
    int val = Serial.read();

    if (val == -1) return;
    if (val == 16) {
      scroll = true;
    } else {
      scroll = false;
      Serial.println("Received value:" + String(val));
      num = (char) val;
      writeNumber(num);
    }

  }

  unsigned long currentMillis = millis();
  if (scroll && currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    num = (num+1)%10;
    writeNumber(num);
  }
}
