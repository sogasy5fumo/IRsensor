#pragma once

#include <Arduino.h>

float normalizeAngle(float angle); // 角度を 0°~360° → -180°~180° に変換

void serialStart(); // シリアル起動確認

void dataSend(int data, int base);

#define START 0xFF
#define FINISH 0xFE

void startSend();
void finishSend();