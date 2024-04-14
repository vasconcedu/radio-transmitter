#include <RF24.h>
#include <RF24_config.h>
#include <nRF24L01.h>
#include <printf.h>

#include "Pad.hpp"
#include "Throttle.hpp"

/*
    Radio transmitter 

    This sketch is the firware for a radio transmitter based on 
    transceiver module nRF24L01. The controller has 2 input pads,
    one with 4 push buttons, and the other with 2 push buttons,
    resulting in 6 digital inputs. All 6 inputs are treated as 
    channels and transmitted to the receiver independently. The 
    board used is an Arduino Nano.

    The circuit:
    - TODO 

    Created 10 April 2024 
    By Eduardo Vasconcelos 
    Modified 14 April 2024
    By Eduardo Vasconcelos

*/

// Directional pad 
Pad dPad = Pad(2, 3, 4, 5);

// Button pad 
Pad bPad = Pad(NULL, A0, NULL, A1);

// Indicator LED
uint8_t led = 6;

// Transmitter radio
RF24 radio(8, 7);
uint8_t address[6] = "wolf0";
int radioBuffer[9] = {
  -1, -1, -1, 
  -1, -1, -1
};

void setup() {
  // [begin] toggle comment for debugging
  Serial.begin(9600);
  // [end]

  // Indicator LED setup 
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  // Radio setup 
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
}

void loop() {
  /*
      Transmission loop 

      1. Read all input states and store them in a 
      transmission buffer

      2. Transmit the buffer to the receiver
  */

  // Read controller state to radio buffer 
  readDPad();
  readBPad();

  // Transmit radio buffer to receiver 
  radio.write(&radioBuffer, sizeof(radioBuffer));

  // // [begin] toggle comment for debugging
  // logState();
  // // This prevents flooding the serial monitor 
  // delay(1000);
  // // [end]
}

void readDPad() {
  radioBuffer[0] = dPad.getUpper();
  radioBuffer[1] = dPad.getLeft();
  radioBuffer[2] = dPad.getLower();
  radioBuffer[3] = dPad.getRight();
}

void readBPad() {
  radioBuffer[4] = bPad.getLeft();
  radioBuffer[5] = bPad.getRight();
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
  Serial.print("- left: ");
  Serial.println(bPad.getLeft());
  Serial.print("- right: ");
  Serial.println(bPad.getRight());

  // Radio buffer 
  Serial.println("\nRadio buffer:");
  Serial.println("* READINGS MAY DIFFER TRANSITORILY FROM THE ONES ABOVE *");
  for (int i = 0; i < 6; i++) {
    Serial.print("- radioBuffer[");
    Serial.print(i);
    Serial.print("]: ");
    Serial.println(radioBuffer[i]);
  }

  Serial.println("========================");
}
