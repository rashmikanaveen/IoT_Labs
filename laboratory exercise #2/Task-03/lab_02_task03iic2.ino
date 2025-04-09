// Name: YAPA YMRNT
// Index Number: 220734B
// Arduino 2: Sound Controller
#include <Wire.h>

const int speakerPin = 4;
const int LED = 13;

int receivedFreq = 0;
unsigned long lastHeartbeatReceived = 0;
unsigned long lastToneTime = 0;

void receiveEvent(int howMany) {
  if (howMany == 2) {
    int highByte = Wire.read();
    int lowByte = Wire.read();
    receivedFreq = (highByte << 8) | lowByte;

    if (receivedFreq == 0xFFFF) {
      // Heartbeat signal
      lastHeartbeatReceived = millis();
    } else {
      if (receivedFreq > 0) {
        tone(speakerPin, receivedFreq);
        lastToneTime = millis();
      }
    }
  }
}

void setup() {
  Wire.begin(8); // Slave address
  Wire.onReceive(receiveEvent);
  pinMode(speakerPin, OUTPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // LED diagnostic
  if (millis() - lastHeartbeatReceived < 2000) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

  // Stop tone if it hasn’t been updated for 500 ms
  if (millis() - lastToneTime > 500) {
    noTone(speakerPin);
  }
}
