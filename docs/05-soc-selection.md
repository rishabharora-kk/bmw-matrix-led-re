# 05 — MCU selection and electrical partition

**Design objective**: send verified, bounded vehicle-side requests over **CAN** to the original FLE, after passive baseline capture. Do *not* assume direct communication to an internal LMM is necessary.

## Scored engineering decision (1 poor – 5 strong; subjective engineering assessment)

Weights: CAN/CAN-FD capability 30%; deterministic scheduling 20%; development ecosystem 20%; total cost 15%; automotive migration 15%.

| Platform | CAN(-FD) 30% | Timing 20% | Tooling 20% | Cost 15% | Automotive path 15% | Weighted /5 | Decision |
|---|---:|---:|---:|---:|---:|---:|---|
| **STM32G474 Nucleo** | 5 | 5 | 5 | 4 | 3 | **4.55** | Chosen for initial standalone FLE emulator |
| NXP S32K144 EVB | 5 | 5 | 3 | 2 | 5 | 4.15 | Strong automotive migration; EVB + tools cost more |
| STM32H7 (model-specific) | 5 | 5 | 4 | 2 | 3 | 4.05 | More CPU/RAM than a 12-channel command relay warrants |
| Teensy 4.1 | 4 | 5 | 5 | 3 | 2 | 3.95 | Excellent PoC, less obvious production migration |
| ESP32-S3 + external CAN-FD controller | 2 | 3 | 5 | 5 | 2 | 3.25 | Internal TWAI is classic CAN; adds FD bridge/latency |
| RP2040 / RP2350 + external CAN(-FD) | 2 | 4 | 4 | 5 | 2 | 3.25 | Good low-cost lab host but external FD controller needed |

Values are comparative, not official vendor benchmarks. Verified foundations: STM32G474 has multiple FDCAN controllers ([ST datasheet](https://www.st.com/resource/en/datasheet/stm32g474ve.pdf)); S32K144 CAN FD support ([NXP app note](https://www.nxp.com/docs/en/application-note/AN5413.pdf)); Teensy 4.1 CAN-dependent proof of concept ([VŠB thesis](https://dspace.vsb.cz/items/25647d0a-967c-44b9-9da7-1e8250228837)). **LIN, UART, SPI and PWM only become requirements if a new internal driver architecture is validated.**

## Block diagram

```mermaid
flowchart LR
  USB[Host logger / config - isolated] --> MCU[STM32G474 + firmware watchdog]
  PWR[12 V current-limited bench PSU / fuse / E-stop] --> LAMP[OEM G30 LCI HELLA FLE + LED array]
  MCU --> SAFE[Tx hard interlock / signed-off allowlist]
  SAFE --> CAN[Protected CAN(-FD) transceiver / isolation]
  CAN --> LAMP
  LAMP --> SHIELD[Opaque light box / temp sensors / fan monitoring]
  LAMP -. verified CAN receive .-> CAN
  SAF[Undervoltage / overtemp / watchdog] --> MCU
```

Important: hardware photo and verified diagram are needed before specifying actual connectors or transceiver wiring. Bench isolation may reside in the USB–CAN capture adapter rather than MCU leg; final grounding requires electrical review.

## Electronics requirements

- Microcontroller: dual-function bring-up interface (USB debug) and verified FDCAN connection; watchdog, brownout reset and startup disarmed.
- Front-end: appropriate CAN-FD transceiver (if FD measured), ESD/TVS, switchable termination **only after bus topology confirmed**, proper common-mode range, failsafe CAN line impedance and reverse polarity protection.
- Power: no direct high-power LED current switching in controller; OEM FLE retains LED current and fan safety. Provide protected 12 V input to lamp separately and regulator to MCU; reverse-polarity and input transient measures.
- Sensing: supply voltage and current, isolated heat probe, fan status where feasible, hardware emergency-stop that physically opens lamp supply.
- Connector: matching OEM mating shell + terminals from measured part identity; never use improvised flying leads on an energized lamp.

## BOM

See [`hardware/bom.csv`](../hardware/bom.csv) for itemized indicative INR and rough USD reference (USD estimates assume **₹85/USD solely for costing comparability**, not a current FX quote). Budget bands are not a design authorization.

## PCB plan (after bus identity)

Rev A: no PCB. Use NUCLEO-G474RE with isolated USB-CAN to capture and confirm the bus and an interface breakout with tested connector. Rev B: two-layer *logic-only* protected transceiver carrier, removable termination, jumpers, measuring points, E-stop input. Rev C: four-layer board for robust ground segregation, high-frequency transient testing, supply supervision, harness connector, mounting and thermals. OEM LEDs and matrix supply drivers remain untouched.
