Task #1: Communication between two Arduino boards
Modify the exercise #1 design such that the keyboard input and the sound output are handled by two different Arduino Uno boards.  You need to have the keyboard, and the key number display connected to one of the Arduino boards while speaker is connected to separate Arduino board.  The two boards should communicate with each other using a serial (UART) interface.  


Task #2:  Using i2c Communication
Change the communication between the two Arduino boards to i2c interface.  Test your design and upload the following through the links provided. 

Task #3: Adding onboard diagnostics
Modify the design to include some onboard diagnostic features.  Add an LED to each of the two Arduino boards.  The LED should light up and remain continuously on when the two bords are connected through the i2c interface.  If the communication breaks down the LED should be switched off.  The diagnostic LED function should work regardless of whether the any keys are pressed or not. 
