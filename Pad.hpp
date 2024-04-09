#include <Arduino.h>
#include "pin.h"

using namespace std;

class Pad {
    private:
        pin_t upper;
        pin_t left;
        pin_t lower;
        pin_t right;
        void setupPin(pin_t &pin, uint8_t number);
    public:
        Pad(uint8_t upper, uint8_t left, uint8_t lower, uint8_t right);
        int getUpper();
        int getLeft();
        int getLower();
        int getRight();
};
