# FanRemote433

Biblioteca Arduino para reproduzir os 19 botões de um controle de ventilador de 433 MHz. O código e o endereço vêm do controle usado na bancada. A compatibilidade com outro ventilador depende do protocolo e do endereço dele.

## Placas e ligação

| Placa | Pino DATA no exemplo | Validação |
| --- | --- | --- |
| Arduino Uno (ATmega328P) | D10 | Compilação e teste de transmissão com o ventilador da bancada |
| ESP32 TTGO T7 V1.3 Mini32 | GPIO4 | Compilação com Arduino-ESP32 3.3.2 e teste da velocidade 1 no ventilador |
| ESP32-C3 SuperMini | GPIO4 | Compilação com Arduino-ESP32 3.3.2 e teste do comando Luz no ventilador |
| ESP8266 | GPIO4 | Compilação com Arduino Core for ESP8266 3.1.2 |

Ligue o pino DATA do transmissor RF de 433 MHz ao GPIO escolhido e compartilhe o GND entre o transmissor e a placa. Nos ESP, verifique se a entrada DATA do transmissor aceita lógica de 3,3 V e use a tensão de alimentação especificada para o módulo. Ajuste `txPin` se o GPIO do exemplo estiver indisponível na sua placa. [GPIO no Arduino-ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/api/gpio.html)

Nos testes com o FS1000A, o ESP32 acionou o pino DATA em 3,3 V e o transmissor foi alimentado em 5 V. Para usar o exemplo pelo USB nativo do ESP32-C3, habilite `USB CDC On Boot` na configuração da placa.

## Usar em um sketch

Copie a pasta `FanRemote433` para a pasta `libraries` do Arduino ou use `arduino-cli compile --library`. Abra o exemplo [SerialControl](examples/SerialControl/SerialControl.ino), ajuste o GPIO se necessário e envie uma das teclas da tabela pelo Monitor Serial a 115200 baud.

```cpp
#include <FanRemote433.h>

FanRemote433 fan(10); // D10 no Uno. Use o GPIO escolhido na sua placa.

void setup() {
    fan.begin();
}

void loop() {
    // Chame quando quiser transmitir:
    // fan.send(FanRemote433::Command::Speed1);
}
```

`send()` ocupa o sketch durante a rajada e retorna `true` quando envia um comando conhecido. A confirmação de recepção vem da resposta do ventilador. A biblioteca usa apenas o transmissor.

## Comandos

| Botões | API | Teclas do exemplo serial (115200 baud) |
| --- | --- | --- |
| Velocidades 1–6 | `Speed1` a `Speed6` | `1` a `6` |
| Desligar motor e luz, alternar luz, desligar só o motor | `Power`, `Light`, `FanOff` | `p`, `l`, `f` |
| Ventilação verão, brisa, exaustão inverno, dormir | `Summer`, `Breeze`, `Winter`, `Sleep` | `v`, `b`, `i`, `s` |
| Timer de 1h, 2h, 4h, 6h, 8h e desligar timer | `Timer1h`, `Timer2h`, `Timer4h`, `Timer6h`, `Timer8h`, `TimerOff` | `A`, `B`, `C`, `D`, `E`, `T` |

As funções dos botões estão descritas no [manual Arno New Ultimate VX13/VX14/VX15](https://lojaarno.vtexassets.com/arquivos/Manual-Arno-IFU_VX13-14-15.pdf#page=2).

No ESP32-C3, `Light` envia um único quadro por chamada. Na bancada, a rajada de cinco quadros às vezes acionava o motor ou alternava a luz duas vezes. A versão de um quadro foi validada no SuperMini.
