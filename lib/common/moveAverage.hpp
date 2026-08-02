#pragma once
#include <Arduino.h>

class MovingAverage
{
private:
    static const int num_elements = 10;      // サイズ定数(回数)
    float storage[num_elements] = {0}; // バッファを0で初期化
    int current_target = 0;
    int count = 0;

public:
    float update(float now_val);
};

class EMAfilter
{
private:
    float _filtered = 0.0f;
    float _now_data = 0.0f;
    float _alpha = 0.0f;
    int _count;
public:
    void EMA_init(float alpha);
    void EMA_calculate(float now_data);
    float getFiltered() const { return _filtered; }
};
