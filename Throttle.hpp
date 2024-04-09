#include <Arduino.h>
#include "pin.h"

using namespace std;

class Throttle {
    private:
        pin_t analog;
        long fromLow; 
        long fromHigh;
        bool calibratedFromLow;
        bool calibratedFromHigh;
    public:
        Throttle(uint8_t analog);
        void calibrateFromLow();
        void calibrateFromHigh();
        bool isCalibratedFromLow();
        bool isCalibratedFromHigh();
        int getAnalog();
};
