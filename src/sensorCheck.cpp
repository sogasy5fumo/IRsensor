// #include <Arduino.h>
// #include "sensorCheck.hpp"


// const int IR_FIRST_PIN = 1;
// const int IR_LAST_PIN = 10;
// const int IR_COUNT = 8;

// void sensorCheck(){
//     for (int pin = IR_FIRST_PIN; pin <= IR_LAST_PIN; pin++) // センサごとの値チェックプログラム
//     {
//     if (pin == 6 || pin == 7)
//     {
//         continue;
//     }
//     Serial.print(String(" ") + pin + String(" : "));
//     Serial.print(analogRead(pin));
//     }
// }