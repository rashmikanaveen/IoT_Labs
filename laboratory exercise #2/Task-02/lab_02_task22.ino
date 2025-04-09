// Name: YAPA YMRNT
// Index Number: 220734B
// Arduino 2: Sound Controller
#include <Wire.h>

const int speakerPin = 4;
int receivedFreq = 0;

void receiveEvent(int howMany) {
  if (howMany == 2) {
    int highByte = Wire.read();
    int lowByte = Wire.read();
    receivedFreq = (highByte << 8) | lowByte;

    if (receivedFreq > 0) {
      tone(speakerPin, receivedFreq);
    } else {
      noTone(speakerPin);
    }
  }
}

void setup() {
  Wire.begin(8); // Slave address 8
  Wire.onReceive(receiveEvent);
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // Speaker is controlled inside receiveEvent()
}
