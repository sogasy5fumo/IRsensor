#include "multiplexer.hpp"

void multiplexer::set_pin(int b1_pin, int b2_pin, int b3_pin, int b4_pin, int receive_pin)
{
    _b1_pin = b1_pin;
    _b2_pin = b2_pin;
    _b3_pin = b3_pin;
    _b4_pin = b4_pin;
    _recieve_pin = receive_pin;
}

void multiplexer::init(int last_pin)
{
    pinMode(_b1_pin, OUTPUT);
    pinMode(_b2_pin, OUTPUT);
    pinMode(_b3_pin, OUTPUT);
    pinMode(_b4_pin, OUTPUT);
    pinMode(_recieve_pin, INPUT);

    _last_pin = last_pin;
}

unsigned int multiplexer::read(int index)
{
    Parts b1; // 0ピン
    Parts b2; // 1ピン
    Parts b3; // 2ピン
    Parts b4; // 3ピン

    Pin sensorpin[_last_pin];

    bool output_data[4];
    for (int i = 0; i < 16; i++)
    {
        output_data[0] = (sensorpin[i]._pin >> 0) & 0b0001; // (i >> x):iを右に一つずらし、0以下のものを消去 &:かつ。一桁目が一致していたら0b0001ｓ(正)になる
        output_data[1] = (sensorpin[i]._pin >> 1) & 0b0001;
        output_data[2] = (sensorpin[i]._pin >> 2) & 0b0001;
        output_data[3] = (sensorpin[i]._pin >> 3) & 0b0001;

        digitalWrite(b1._pin, b1._number_parts);
        digitalWrite(b2._pin, b2._number_parts);
        digitalWrite(b3._pin, b3._number_parts);
        digitalWrite(b4._pin, b4._number_parts);

        delayMicroseconds(20);

        sensorpin[sensorpin[i]._pin]._val = analogRead(_recieve_pin);

        Serial.print(sensorpin[i]._val);
        Serial.print(", ");

        // // 送信側
        // uint16_t data = 346;
        // uint8_t d1 = uint8_t(data & 0b11111111);
        // uint8_t d2 = uint8_t((data >> 8) & 0b11111111);
        // Serial.write(d1);
        // Serial.write(d2);

        // Serial.println(String(data));

        // if (Serial.available())
        // {
        //   String a = Serial.readStringUntil('/n');
        //   uint16_t b = a.toInt();
        // }

        // // 受信側
        // if (Serial.available() >= 2)
        // {
        //   uint8_t a = Serial.read();
        //   uint8_t b = Serial.read();

        //   uint16_t fixed_data = (uint16_t(b) << 8) | uint16_t(a);
        // }
    }
}