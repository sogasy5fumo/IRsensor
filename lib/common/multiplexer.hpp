#pragma once

#include <Arduino.h>
class multiplexer
{
private:
    int _b1_pin, _b2_pin, _b3_pin, _b4_pin;
    int _recieve_pin, _last_pin;
public:
    void set_pin(int b1_pin, int b2_pin, int b3_pin, int b4_pin, int receive_pin);
    void init(int last_pin);
    unsigned int read(int index);
};

class Parts
{
public:
  int _pin = -1;
  bool _number_parts = 0;
};

class Pin
{
public:
    int _pin;
    int _val;
    int _deg;
    bool _caught;
};