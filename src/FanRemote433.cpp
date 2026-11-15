#include "FanRemote433.h"

#if defined(ARDUINO_ARCH_AVR)
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

namespace {

#include "recordings/Speed1.h"
#include "recordings/Speed2.h"
#include "recordings/Speed3.h"
#include "recordings/Speed4.h"
#include "recordings/Speed5.h"
#include "recordings/Speed6.h"
#include "recordings/FanOff.h"
#include "recordings/Light.h"
#include "recordings/Power.h"
#include "recordings/Summer.h"
#include "recordings/Breeze.h"
#include "recordings/Winter.h"
#include "recordings/Timer1h.h"
#include "recordings/Timer2h.h"
#include "recordings/Timer4h.h"
#include "recordings/Timer6h.h"
#include "recordings/Timer8h.h"
#include "recordings/TimerOff.h"
#include "recordings/Sleep.h"

// Delay the next edge to an absolute deadline so software overhead does not
// accumulate across the pulses. The unsigned subtraction handles micros wrap.
template <size_t Count>
void sendRecording(uint8_t pin, const uint16_t (&ticks)[Count]) {
    uint32_t deadline = micros();
    uint8_t level = HIGH;
    for (size_t i = 0; i < Count; ++i) {
        digitalWrite(pin, level);
        deadline += static_cast<uint32_t>(pgm_read_word(&ticks[i])) * 25;
        while (static_cast<int32_t>(micros() - deadline) < 0) {
        }
        level ^= 1;
    }
    digitalWrite(pin, LOW);
}

} // namespace

FanRemote433::FanRemote433(uint8_t txPin) : txPin_(txPin) {}

void FanRemote433::begin() const {
#if defined(ARDUINO_ARCH_AVR)
    // Preload the AVR output latch before enabling the pin.
    digitalWrite(txPin_, LOW);
    pinMode(txPin_, OUTPUT);
#else
    pinMode(txPin_, OUTPUT);
    digitalWrite(txPin_, LOW);
#endif
}

bool FanRemote433::send(Command command) const {
    switch (command) {
        case Command::Speed1:
            sendRecording(txPin_, Speed1);
            return true;
        case Command::Speed2:
            sendRecording(txPin_, Speed2);
            return true;
        case Command::Speed3:
            sendRecording(txPin_, Speed3);
            return true;
        case Command::Speed4:
            sendRecording(txPin_, Speed4);
            return true;
        case Command::Speed5:
            sendRecording(txPin_, Speed5);
            return true;
        case Command::Speed6:
            sendRecording(txPin_, Speed6);
            return true;
        case Command::FanOff:
            sendRecording(txPin_, FanOff);
            return true;
        case Command::Light:
            sendRecording(txPin_, Light);
            return true;
        case Command::Power:
            sendRecording(txPin_, Power);
            return true;
        case Command::Summer:
            sendRecording(txPin_, Summer);
            return true;
        case Command::Breeze:
            sendRecording(txPin_, Breeze);
            return true;
        case Command::Winter:
            sendRecording(txPin_, Winter);
            return true;
        case Command::Timer1h:
            sendRecording(txPin_, Timer1h);
            return true;
        case Command::Timer2h:
            sendRecording(txPin_, Timer2h);
            return true;
        case Command::Timer4h:
            sendRecording(txPin_, Timer4h);
            return true;
        case Command::Timer6h:
            sendRecording(txPin_, Timer6h);
            return true;
        case Command::Timer8h:
            sendRecording(txPin_, Timer8h);
            return true;
        case Command::TimerOff:
            sendRecording(txPin_, TimerOff);
            return true;
        case Command::Sleep:
            sendRecording(txPin_, Sleep);
            return true;
    }
    return false;
}
