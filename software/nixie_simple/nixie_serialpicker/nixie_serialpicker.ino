const unsigned long intervalMillis = 50;
unsigned long previousMillis = 0;

typedef struct {
  int A, B, C, D;
  int num;
  bool scroll;
} Tube;

// although I wish I could list in pin order, C++, unlike C, requires designated initializers to be in order
Tube Tube1 = {
  .A = 9,
  .B = 11,
  .C = 12,
  .D = 10,
  .num = 10,
  .scroll = false
};

Tube Tube2 = {
  .A = 8,
  .B = 6,
  .C = 5,
  .D = 7,
  .num = 10,
  .scroll = false
};

void initializeTubePins(Tube *tube) {
  pinMode(tube->A, OUTPUT);
  pinMode(tube->B, OUTPUT);
  pinMode(tube->C, OUTPUT);
  pinMode(tube->D, OUTPUT);
}

void setup() {
  initializeTubePins(&Tube1);
  initializeTubePins(&Tube2);
  
  updateTube(&Tube1);
  updateTube(&Tube2);

  Serial.begin(9600);
  Serial.println("Enter a number between 0 and 9 to display on the nixie tube, or '10' to turn it off.");
}

// Write a number to the nixie tube
// Digits above 9 will turn off the nixie tube bc of how the SN74141/K155ID1 works
void updateTube(Tube *tube) {
  digitalWrite(tube->D, (tube->num >> 3)&1);
  digitalWrite(tube->C, (tube->num >> 2)&1);
  digitalWrite(tube->B, (tube->num >> 1)&1);
  digitalWrite(tube->A, (tube->num     )&1);
}

void readSerialData() {
  if (!Serial.available()) return;

  int tube_num = Serial.read();
  int val = Serial.read();

  Tube tube;
  if (tube_num == 1) {
    tube = Tube1;
  } else if (tube_num == 2) {
    tube = Tube2;
  } else {
    return;
  }

  if (val == -1) return;
  if (val == 16) {
    tube.scroll = true;
  } else {
    tube.scroll = false;
    Serial.println("Received value:" + String(val));
    tube.num = (char) val;
    updateTube(&tube);
  }
}

void loop() {
  readSerialData();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    if (Tube1.scroll) {
      Tube1.num = (Tube1.num+1)%10;
      updateTube(&Tube1);
    }
    if (Tube2.scroll) {
      Tube2.num = (Tube2.num+1)%10;
      updateTube(&Tube2);
    }
  }
}
