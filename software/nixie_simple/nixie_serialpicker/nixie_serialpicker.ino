const int C = 8;
const int B = 10;
const int D = 11;
const int A = 12;

bool scroll = false;
char num = 10;

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
    if (val == 16) scroll = true; return; // enable scrolling animation

    scroll = false;
    Serial.println("Received value:" + String(val));
    num = ((char) val) % 10;
    writeNumber(num);
  }

  unsigned long currentMillis = millis();
  if (scroll && currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    num = (num+1)%10;
    writeNumber(num);
  }
}
