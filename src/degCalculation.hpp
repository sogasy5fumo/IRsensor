#pragma once
#include <Arduino.h>
#include "option.hpp"
#include "moveAverage.hpp"

#include "sensorCheck.hpp"

class IRcalculation
{
private:
    static const int IR_COUNT = 8;
    EMAfilter _sensors[IR_COUNT];
    float _theta = 0.0f;
public:
    void IRinit();
    void degCalculation();
};