// Name: YAPA YMRNT
// Index Number: 220734B

const int buttonPins[8] = {12, 11, 10, 9, 8, 7, 6, 5}; // Push button pins
const int frequencies[8] = {300, 400, 500, 600, 700, 800, 900, 1000}; // Frequencies
const int speakerPin = 4; // Speaker output pin

// 7-segment display pins (Common Cathode)
const int segmentPins[7] = {3, 2, A5, A4, A3, A2, A1}; 

// Digit patterns for 0-7 (assuming common cathode)
const byte digitPatterns[8] = {
    0b0111111, // 0
    0b0000110, // 1
    0b1011011, // 2
    0b1001111, // 3
    0b1100110, // 4
    0b1101101, // 5
    0b1111101, // 6
    0b0000111  // 7
};

void displayDigit(int num) {
    if (num < 0 || num > 7) {
      	
        // Turn off all segments
        for (int i = 0; i < 7; i++) {
            digitalWrite(segmentPins[i], LOW);
        }
        return;
    }
  Serial.println(num);
    byte pattern = digitPatterns[num];
    
    for (int i = 0; i < 7; i++) {
      Serial.println(pattern);
        digitalWrite(segmentPins[i], (pattern >> i) & 1);
    }
}

void setup() {
    Serial.begin(9600);
    pinMode(speakerPin, OUTPUT);
    
    for (int i = 0; i < 8; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP);
    }
    
    for (int i = 0; i < 7; i++) {
        pinMode(segmentPins[i], OUTPUT);
    }
}

void loop() {
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
        tone(speakerPin, totalFreq);
        
        if (keyCount == 1) {
          
            displayDigit(pressedKeys[0]);
        } else {
            for (int j = 0; j < keyCount; j++) {
              	Serial.println(pressedKeys[j]);
                displayDigit(pressedKeys[j]);
              	
                delay(500);
            }
        }
    } else {
        Serial.println("No key pressed");
        noTone(speakerPin);
        
    }
  for (int i = 0; i < keyCount; i++) {
        pressedKeys[i] = -1;
    }

    delay(100);
}