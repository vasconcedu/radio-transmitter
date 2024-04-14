#include "Pad.hpp"

Pad::Pad(uint8_t upper, uint8_t left, uint8_t lower, uint8_t right) {
    setupPin(this->upper, upper);
    setupPin(this->left, left);
    setupPin(this->lower, lower);
    setupPin(this->right, right);
}

void Pad::setupPin(pin_t &pin, uint8_t number) {
    pin.number = number;
    if (number != NULL) {
        pin.mode = INPUT_PULLUP;
        pinMode(pin.number, pin.mode);
    }
}

int Pad::getUpper() {
    if (upper.number != NULL) {
        return digitalRead(upper.number);
    } else {
        return -1;
    }
}

int Pad::getLeft() {
    if (left.number != NULL) {
        return digitalRead(left.number);
    } else {
        return -1;
    }
}

int Pad::getLower() {
    if (lower.number != NULL) {
        return digitalRead(lower.number);
    } else {
        return -1;
    }
}

int Pad::getRight() {
    if (right.number != NULL) {
        return digitalRead(right.number);
    } else {
        return -1;
    }
}
