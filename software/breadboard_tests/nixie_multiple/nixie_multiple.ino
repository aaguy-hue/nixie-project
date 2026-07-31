const unsigned long intervalMillis = 50;
unsigned long previousMillis = 0;

typedef struct {
  int A, B, C, D;
  char num;
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

Tube Tube3 = {
  .A = 4,
  .B = 2,
  .C = A7,
  .D = 3,
  .num = 10,
  .scroll = false
};

Tube tubes[] = {Tube1, Tube2, Tube3};


size_t totalTubeCount() {
  return sizeof(tubes)/sizeof(tubes[0]);
}

void initializeTubePins(Tube *tube) {
  pinMode(tube->A, OUTPUT);
  pinMode(tube->B, OUTPUT);
  pinMode(tube->C, OUTPUT);
  pinMode(tube->D, OUTPUT);
}

void setup() {
  for (int i = 0; i < totalTubeCount(); i++) {
    initializeTubePins(&tubes[i]);
  }
  
  for (int i = 0; i < totalTubeCount(); i++) {
    updateTube(&tubes[i]);
  }

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
  if (Serial.available() < 2) return;

  int tube_num = Serial.read();
  int val = Serial.read();

  Tube *tube;
  if (tube_num < 1 || tube_num > totalTubeCount()) {
    return;
  }
  tube = &tubes[tube_num-1];

  if (val == -1) return;
  if (val == 16) {
    tube->scroll = true;
  } else {
    tube->scroll = false;
    Serial.println("Received value:" + String(val));
    tube->num = (char) val;
    updateTube(tube);
  }
}

void loop() {
  readSerialData();

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= intervalMillis) {
    previousMillis = currentMillis;

    for (int i = 0; i < totalTubeCount(); i++) {
      if (tubes[i].scroll) {
        tubes[i].num = (tubes[i].num+1)%10;
        updateTube(&tubes[i]);
      }
    }
  }
}
