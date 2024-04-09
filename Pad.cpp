#include "Pad.hpp"

Pad::Pad(uint8_t upper, uint8_t left, uint8_t lower, uint8_t right) {
    setupPin(this->upper, upper);
    setupPin(this->left, left);
    setupPin(this->lower, lower);
    setupPin(this->right, right);
}

void Pad::setupPin(pin_t &pin, uint8_t number) {
    pin.number = number;
    pin.mode = INPUT_PULLUP;
    pinMode(pin.number, pin.mode);
}

int Pad::getUpper() {
    return digitalRead(upper.number);
}

int Pad::getLeft() {
    return digitalRead(left.number);
}

int Pad::getLower() {
    return digitalRead(lower.number);
}

int Pad::getRight() {
    return digitalRead(right.number);
}
