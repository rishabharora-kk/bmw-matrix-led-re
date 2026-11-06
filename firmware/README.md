# Fail-closed STM32G474 architecture (offline reference)

The present version compiles **only an offline host-based simulation** of an embedded state machine. `firmware/src/main.c` invokes the state machine with synthetic healthy/failed inputs and never opens a CAN controller, toggles a lamp, or generates real vehicle messages.

## Host demo

```bash
cc -std=c11 -Wall -Wextra -Werror -pedantic -Ifirmware/include \
  firmware/src/main.c firmware/src/state_machine.c -o /tmp/bmw-fle-sim
/tmp/bmw-fle-sim
```

## Hardware port after P0–P2 evidence gates

Select STM32G474 with STM32CubeIDE/HAL/LL, review the exact Nucleo schematic, then implement separately:

- `platform_observe_bus()`: CAN receive only until protocol and electrical bench review; hardware TX disabled by physical interlock.
- `platform_measure_power()`: ADC + independently tested OCP.
- `platform_measure_thermal()`: sensor readings and OEM FLE thermal checks.
- `platform_interlock_closed()`: hardwired physical safety switch, default open.
- `platform_watchdog_kick()` and shutdown on missed service period.

Do **not** merge a transmitter until authentic traces, physical constraints and operational design are validated. Do not forge BDC/FLE identity or diagnostic authentication. Use actual MCU board documentation [ST](https://www.st.com/resource/en/user_manual/dm00556337-stm32g4-nucleo64-boards-mb1367-stmicroelectronics.pdf).
