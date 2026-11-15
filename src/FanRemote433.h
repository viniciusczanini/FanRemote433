#pragma once

#include <Arduino.h>

class FanRemote433 {
public:
    enum class Command : uint8_t {
        Speed1 = '1',
        Speed2 = '2',
        Speed3 = '3',
        Speed4 = '4',
        Speed5 = '5',
        Speed6 = '6',
        FanOff = 'f',
        Light = 'l',
        Power = 'p',
        Summer = 'v',
        Breeze = 'b',
        Winter = 'i',
        Timer1h = 'A',
        Timer2h = 'B',
        Timer4h = 'C',
        Timer6h = 'D',
        Timer8h = 'E',
        TimerOff = 'T',
        Sleep = 's',
    };

    explicit FanRemote433(uint8_t txPin);
    void begin() const;
    bool send(Command command) const;

private:
    uint8_t txPin_;
};
