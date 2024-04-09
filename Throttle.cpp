#include "Throttle.hpp"

Throttle::Throttle(uint8_t analog) {
    calibratedFromLow = false; 
    calibratedFromHigh = false; 
    this->analog.number = analog;
}

void Throttle::calibrateFromLow() {
    fromLow = analogRead(this->analog.number);
    calibratedFromLow = true;
}

void Throttle::calibrateFromHigh() {
    fromHigh = analogRead(this->analog.number);
    calibratedFromHigh = true;
}

bool Throttle::isCalibratedFromLow() {
    return calibratedFromLow;
}

bool Throttle::isCalibratedFromHigh() {
    return calibratedFromHigh;
}

int Throttle::getAnalog() {
    int value = analogRead(analog.number);
    return map(value, fromLow, fromHigh, 0, 255); 
}
