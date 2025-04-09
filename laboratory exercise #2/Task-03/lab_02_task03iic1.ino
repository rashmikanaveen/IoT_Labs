// Name: YAPA YMRNT
// Index Number: 220734B
// Arduino 1: Keyboard & Display Controller

#include <Wire.h>

const int buttonPins[8] = {12, 11, 10, 9, 8, 7, 6, 5};
const int frequencies[8] = {300, 400, 500, 600, 700, 800, 900, 1000};
const int segmentPins[7] = {3, 2, 1, 4, A3, A2, A1};

const int diagLEDPin = 13;

const byte digitPatterns[8] = {
  0b0111111, 0b0000110, 0b1011011, 0b1001111,
  0b1100110, 0b1101101, 0b1111101, 0b0000111
};

unsigned long lastHeartbeatSent = 0;

void displayDigit(int num) {
  if (num < 0 || num > 7) {
    for (int i = 0; i < 7; i++) digitalWrite(segmentPins[i], LOW);
    return;
  }

  byte pattern = digitPatterns[num];
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], (pattern >> i) & 1);
  }
}

void sendFreq(int freq) {
  Wire.beginTransmission(8);
  Wire.write((byte)(freq >> 8));
  Wire.write((byte)(freq & 0xFF));
  byte result = Wire.endTransmission();

  if (result == 0) {
    digitalWrite(diagLEDPin, HIGH); // Communication successful
  } else {
    digitalWrite(diagLEDPin, LOW); // Failed communication
  }
}

void sendHeartbeat() {
  Wire.beginTransmission(8);
  Wire.write(0xFF); // Special byte to indicate "heartbeat"
  Wire.write(0xFF);
  byte result = Wire.endTransmission();

  if (result == 0) {
    digitalWrite(diagLEDPin, HIGH);
  } else {
    digitalWrite(diagLEDPin, LOW);
  }
}

void setup() {
  Wire.begin(); // Master
  for (int i = 0; i < 8; i++) pinMode(buttonPins[i], INPUT_PULLUP);
  for (int i = 0; i < 7; i++) pinMode(segmentPins[i], OUTPUT);
  pinMode(diagLEDPin, OUTPUT);
}

void loop() {
  // Heartbeat every 1 sec
  if (millis() - lastHeartbeatSent > 1000) {
    sendHeartbeat();
    lastHeartbeatSent = millis();
  }

  int totalFreq = 0;
  int pressedKeys[8];
  int keyCount = 0;

  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      totalFreq += frequencies[i];
      pressedKeys[keyCount++] = i;
    }
  }

  if (keyCount > 0) {
    sendFreq(totalFreq);

    if (keyCount == 1) {
      displayDigit(pressedKeys[0]);
    } else {
      for (int j = 0; j < keyCount; j++) {
        displayDigit(pressedKeys[j]);
        delay(500);
      }
    }
  }

  delay(100);
}
