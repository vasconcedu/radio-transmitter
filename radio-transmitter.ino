#include "Pad.hpp"
#include "Throttle.hpp"

/*
    Radio transmitter 

    This sketch is the firware for a radio transmitter based on 
    transceiver module nRF24L01. The controller has 2 input pads
    of 4 push buttons each, resulting in 8 digital inputs, as well 
    as a self-calibrating analog input based on a POT. All 9 inputs 
    are treated as channels and transmitted to the receiver
    independently. The board used is an Arduino Uno.

    The circuit:
    - TODO

    Created TODO add date e.g. 8 April 2024
    By Eduardo Vasconcelos 

*/

// Directional pad 
Pad dPad = Pad(2, 3, 4, 5);

// Button pad 
Pad bPad = Pad(A0, A1, A2, A3);

// Throttle
Throttle throttle = Throttle(A4);

// Indicator LED
uint8_t led = 6;

void setup() {
  // [begin] toggle comment for debugging
  Serial.begin(9600);
  // [end]

  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop() {
  /*
      Throttle calibration loop 
      
      1. LED blinks slowly indicating the transmitter
      is in stand by mode expecting the user to close 
      the throttle for from low calibration 
      
      2. LED stays lit for 1 second indicating that
      from low calibration is done
      
      3. LED blinks slowly indicating the transmitter
      is in stand by mode expecting the user to open 
      the throttle for from high calibration
      
      4. LED stays lit for 1 second indicating that
      from high calibration is done
      
      5. LED blinks quickly indicating the transmitter
      is ready

  */
  if (!throttle.isCalibratedFromLow()) {
    blinkStandBy();
    throttle.calibrateFromLow();
    delay(1000);
  } else if (!throttle.isCalibratedFromHigh()) {
    blinkStandBy();
    throttle.calibrateFromHigh();
    delay(1000);
    blinkReady();
  } else {

    /*
        Transmission loop 

        1. Read all input states and store them in a 
        transmission buffer

        2. Transmit the buffer to the receiver
    */

    // [begin] toggle comment for debugging
    logState();
    // This prevents flooding the serial monitor 
    delay(1000);
    // [end]

    // TODO add firware code here
  }
}

void blinkStandBy() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led, LOW);
    delay(500);
    digitalWrite(led, HIGH);
    delay(500);
  }
}

void blinkReady() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led, LOW);
    delay(50);
    digitalWrite(led, HIGH);
    delay(50);
  }
}

void logState() {
  Serial.println("=== Transmitter state ===");

  // dPad state
  Serial.println("\nDirectional pad:");
  Serial.print("- upper: ");
  Serial.println(dPad.getUpper());
  Serial.print("- left: ");
  Serial.println(dPad.getLeft());
  Serial.print("- lower: ");
  Serial.println(dPad.getLower());
  Serial.print("- right: ");
  Serial.println(dPad.getRight());

  // bPad state 
  Serial.println("\nButton pad:");
  Serial.print("- upper: ");
  Serial.println(bPad.getUpper());
  Serial.print("- left: ");
  Serial.println(bPad.getLeft());
  Serial.print("- lower: ");
  Serial.println(bPad.getLower());
  Serial.print("- right: ");
  Serial.println(bPad.getRight());

  // Throttle state
  Serial.print("\nThrottle analog: ");
  Serial.println(throttle.getAnalog());

  Serial.println("========================");
}
