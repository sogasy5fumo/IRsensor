#include "option.hpp"

float normalizeAngle(float angle)
{
    while (angle > 180.0)
        angle -= 360.0;
    while (angle < -180.0)
        angle += 360.0;
    return angle;
}

void serialStart()
{
    while (!Serial)
        ;

    Serial.println("Serial start    ");
}

void dataSend(int data, int base)
{
    if (base == 2 || base == 8)
    {
        Serial1.write((uint8_t)(data & 0xFF));
    }
    else if (base == 16)
    {
        uint16_t _data = (uint16_t)data;
        Serial1.write((_data >> 8) & 0xFF);
        Serial1.write(_data & 0xFF);
    }else{
        Serial1.write(0xFF);
    }
}

void startSend() { Serial1.write(START); }
void finishSend() { Serial1.write(FINISH); }