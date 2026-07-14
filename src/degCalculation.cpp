#include <Arduino.h>
#include "option.hpp"

#include "sensorCheck.hpp"
#include "degCalculation.hpp"

static const int NOT_BALL_FOUND = 900;

bool ball_found = false;
float theta = 0.0;

class IR // 個々のIRもろもろ
{
public:
    int _pin = -1;
    int _val = -1;
    float _deg = -1;
};

IR myIR[8];

const int IRsensor_pin[8] = {1, 2, 3, 4, 5, 8, 9, 10};

// 移動平均クラス新ファミリーの宣言
static MovingAverage vxMA;
static MovingAverage vyMA;

float ball_angle;
const int DAC_pin1 = A0;
const int DAC_pin2;

static float deg_radian(float degree)
{
    return degree * M_PI / 180.0;
}

void degCalculation()
{
    //
    //=======================================================================================
    // 値の更新
    //=======================================================================================
    //
    IR minIR; // 最小値の決定
    minIR._val = 1023;

    for (int i = 0; i < 8; i++)
    {
        myIR[i]._pin = IRsensor_pin[i];
        myIR[i]._val = analogRead(myIR[i]._pin);
        myIR[i]._deg = i * 45;

        if (myIR[i]._val < minIR._val)
        {
            minIR._pin = myIR[i]._pin;
            minIR._val = myIR[i]._val;
            minIR._deg = myIR[i]._deg;
        }
    }

    for (int i = 0; i < IR_COUNT; i++)
    {
        Serial.print(myIR[i]._val);
        Serial.print(" ");
    }
    Serial.print("最小値のピン");
    Serial.print("-> ");
    Serial.print(minIR._val);
    Serial.print(" ");

    // -minval900よりも小さいならball_foundがtrueにする-
    if (minIR._val > NOT_BALL_FOUND)
    {
        ball_found = false;
    }
    else
    {
        ball_found = true;
    }

    //
    //=======================================================================================
    // ベクトル合成
    //=======================================================================================
    //

    float vx = 0.0, vy = 0.0;

    for (int pin = 0; pin < IR_COUNT; pin++)
    {
        float w = 1.0 / (myIR[pin]._val + 1);
        float ang = deg_radian(myIR[pin]._deg);
        vx += w * cos(ang);
        vy += w * sin(ang);
    }

    float smoothVX = vxMA.update(vx);
    float smoothVY = vyMA.update(vy);

    theta = atan2(smoothVY, smoothVX) * 180.0 / M_PI;
    if (theta < 0.0)
        theta += 360.0;
    ball_angle = (theta / 360.0) * 1024; // C-styleに送る用

    if (ball_found)
    {
        Serial.print(theta);
        analogWrite(DAC_pin1, ball_angle); // DAC_pin1に値を送る。
    }
    else
    {
        Serial.print("ボールが見つかりません (No IR ball Signal)");
        analogWrite(DAC_pin2, ball_found);
    }
}