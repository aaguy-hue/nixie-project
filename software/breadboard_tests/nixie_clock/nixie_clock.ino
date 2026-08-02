#include <mbed.h>
// #include <time.h>
// mbed.h provides functions to get the current time

typedef struct {
  int A, B, C, D;
  char num;
} Tube;

// although I wish I could list in pin order, C++, unlike C, requires designated initializers to be in order
Tube Tube1 = {
  .A = 9,
  .B = 11,
  .C = 12,
  .D = 10,
  .num = 10
};

Tube Tube2 = {
  .A = 8,
  .B = 6,
  .C = 5,
  .D = 7,
  .num = 10
};

// the digit 4 is not connected here bc the leads were too short to connect to my jumper, so I just left it unconnected
Tube Tube3 = {
  .A = 4,
  .B = 2,
  .C = A7,
  .D = 3,
  .num = 10
};

// the digits 9 and 0 are not connected
Tube Tube4 = {
  .A = A0,
  .B = A2,
  .C = A3,
  .D = A1,
  .num = 10
};

Tube tubes[] = {Tube1, Tube2, Tube3, Tube4};


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

  Serial.begin(9600);
}

// Write a number to the nixie tube
// Digits above 9 will turn off the nixie tube bc of how the SN74141/K155ID1 works
void updateTube(Tube *tube) {
  digitalWrite(tube->D, (tube->num >> 3)&1);
  digitalWrite(tube->C, (tube->num >> 2)&1);
  digitalWrite(tube->B, (tube->num >> 1)&1);
  digitalWrite(tube->A, (tube->num     )&1);
}

// over serial, my python program will periodially send the current time (maybe every hour or so) by sending the seconds since the epoch
void readSerialData() {
  if (!Serial.available()) return;

  String input = Serial.readStringUntil('\n');
  input.trim();

  int time_since_epoch = input.toInt();
  if (time_since_epoch > 0) {
    set_time(time_since_epoch);
  }
}

// based on time since epoch set tube digits to the current time in HH:MM format
void updateTubeNumbers() {
    time_t current_time = time(NULL);
    struct tm *time_info = localtime(&current_time);
    
    int hour = time_info->tm_hour;
    int minute = time_info->tm_min;
    
    tubes[0].num = hour / 10;      // tens place of hour
    tubes[1].num = hour % 10;      // ones place of hour
    tubes[2].num = minute / 10;    // tens place of minute
    tubes[3].num = minute % 10;    // ones place of minute
}

void loop() {
  readSerialData();
  updateTubeNumbers();

  for (int i = 0; i < totalTubeCount(); i++) {
    Tube *tube = &tubes[i];
    updateTube(tube);
  }
}
