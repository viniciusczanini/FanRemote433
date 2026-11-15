#include <FanRemote433.h>

#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_ARCH_ESP8266)
constexpr uint8_t txPin = 4; // GPIO number. Change it to match your board.
#else
constexpr uint8_t txPin = 10; // D10 on Arduino Uno.
#endif

FanRemote433 fan(txPin);

void setup() {
    fan.begin();
    Serial.begin(115200);
    Serial.println(F("FAN433 READY"));
}

void loop() {
    const int input = Serial.read();
    if (input == '?') {
        Serial.println(F("FAN433 READY"));
        return;
    }
    if (input >= 0 && fan.send(static_cast<FanRemote433::Command>(input))) {
        Serial.print(F("SENT "));
        Serial.println(static_cast<char>(input));
    }
}
