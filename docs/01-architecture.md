# 01 — Target architecture and evidence ledger

## Target selection

**Primary research target:** non-laser HELLA matrix-adaptive LED headlamp for BMW G30/G31 **LCI (facelift 2020–)**, a 12-channel matrix. This is **not** a generic BMW adaptive headlamp and should not be conflated with swivel/stepper Adaptive LED (earlier G30 or other models), X5 G05 (separate variant and supplier validation), iX, or BMW Laserlight. [HELLA, Jan 2021](https://www.hella.com/hella-com/en/press/Technology-Products-27-01-2021-19305.html).

| Technology | Supported claim | Confidence | Implication |
|---|---|---|---|
| Legacy adaptive/swiveling assemblies | Motor/reflector steering exists on certain BMW adaptations; FLE can actuate levelling motors | Likely (secondary training / repair) | Mechanical actuation != LED matrix segmentation. [G30 G-series training mirror](https://www.bmw5g30.com/control_units_on_the_k_can3-1875.html) |
| G30 LCI HELLA matrix LED | Twelve controllable channels, Selective Beam anti-glare lighting | **Confirmed (supplier)** | Adopt as primary hardware target. [HELLA 2021](https://www.hella.com/hella-com/en/press/Technology-Products-27-01-2021-19305.html) |
| G30 LCI Laserlight | Matrix module **plus** laser light source | **Confirmed (supplier)** | Exclude from powered experiments. [HELLA 2021](https://www.hella.com/hella-com/en/press/Technology-Products-27-01-2021-19305.html) |
| G05 X5 LED / Laserlight | Distinct option codes 552 and 5AZ and separate catalog parts | Likely (secondary catalog) | Do not assume G30 messages/parts transfer. [RealOEM G05 catalog](https://www.realoem.com/bmw/enUS/showparts?diagId=63_1996&id=JU21-EUR-07-2019-G05-BMW-X5_50iX) |
| iX / high-definition | BMW says iX 2022 and 2026 full LED is standard; **no verified G30-equivalent driver topology** | Confirmed for generic LED only / unknown for pixel design | Separate project until a teardown. [BMW iX FAQ](https://faq.bmwusa.com/s/article/BMW-iX-from-112021-BMW-iX-from-032025-BMW-headlight-technology-MY22MY26-LPsH5) |
| ZKW, Marelli, other supplier variants | Suppliers operate in BMW lighting, but **not established for the exact chosen part** | Speculative for this lamp | Supplier must be read from the physical label; do not equate supplier brand with bus/driver architecture. [ZKW product overview](https://zkw-group.com/wp-content/uploads/corporate/The-world-of-ZKW-2019.pdf) |

## Existing-lamp system boundary

```
Vehicle camera / sensor fusion (outside scope)
               |
      BDC: decides lighting requests
               |
        K-CAN3? (CAN confirmed; specific network likely)
               |
       FLEL / FLER (headlamp ECU)
       /  |       |       \
     Matrix  Bi-LED   fan/temp   levelling actuator
     12-ch   optics   supervision
               |
          optical light output
```

- **Confirmed (supplier):** BDC → FLE via CAN request, FLE controls functions and reports faults back through vehicle diagnostics. Heat/fan support and data-matrix LED classification discussed in [HELLA technical note](https://www.hella.com/techworld/sg/technical/automotive-lighting/bmw-led-lamps/).
- **Likely:** G30 K-CAN3 hosts FLEL/FLER ([G30 training mirror](https://www.bmw5g30.com/control_units_on_the_k_can3-1875.html)). **Unknown:** exact G30 LCI frame set and bitrate. **DO NOT** inherit older E-series 100 kbps K-CAN measurements; they describe a different bus ([E-series opendbc](https://github.com/dzid26/opendbc-BMW-E8x-E9x)).
- **Crucial distinction:** HELLA's *12 channels* are lighting channels, not proven externally addressable CAN signals. There might only be requests for low/high beam and anti-dazzle modes.
- **Do not infer wiring:** a third-party retrofit document maps the **18-pin retrofit adapter** K-CAN3 pins, not bare-lamp pins ([retrofit adapter PDF](https://www.bmwcustomretrofit.com/Manuals/BMW%20G30_F90%20Facelift%20Headlights%20AdapterBrief%20Overview%20and%20Schematic%20Diagrams%20edition%201_01.pdf)). The physical lamp pinout stays `UNKNOWN` until confirmed for the photographed part.

## Hardware identity gating

Record, without publishing vehicle identifiers: assembly label photos, RHD/LHD, left/right, supplier, BMW service number, hardware index, build date, options, integral driver modules, connector count/keying, failure history and whether a **Class 1/laser caution** label is present. A third-party listing advertises **63119479261/63119479262** as G30 LCI adaptive LED assemblies, but this is **not a verified universal interchange number** ([left](https://salparts.com/bmw-5-series-g30-lci-headlamp-adaptive-led-left-63119479261/), [right](https://salparts.com/bmw-5-series-g30-lci-headlamp-adaptive-led-right-63119479262/)). Validate the actual sticker and VIN-specific parts catalog before purchasing anything.

## Driver IC decision

Examples of publicly documented 12-channel matrix managers: [TI TPS92662-Q1](https://www.ti.com/product/TPS92662-Q1), [ADI MAX25608](https://www.analog.com/en/products/max25608.html). Each supports serial command/control and LED fault detection. TI's reference architecture puts shunt switches across pixels ([TI white paper](https://www.ti.com/lit/pdf/slyy170)). **No source establishes which IC HELLA placed inside this BMW assembly.** The number '12' alone is not a chip identification. An internal-chip replacement is **out of scope unless authorized and protected firmware is not defeated**.

## Evidence gate: identify external command abstraction

1. Capture on/off, DRL, indicators, low beam, high beam, cornering and selective-beam transitions on a donor/fully isolated lab harness, **passive listen first**.
2. Separate periodic state/fault messages from the actual lamp requests using state correlation; log temperature, voltage, order and timings.
3. Determine whether Selective Beam is commanded as a mode, a mask field, or light distribution encoded indirectly. Mark every signal with a hypothesis and falsification test.
4. If only functions are externally exposed, **do not promise 12-zone direct addressing**. Consider independent driver redesign as a separate project requiring a full thermal/optical safety case.

## Diagnostics and coding

HELLA describes FLE fault storage read through BDC and data matrix/classification coding with dedicated diagnostic equipment ([HELLA](https://www.hella.com/techworld/sg/technical/automotive-lighting/bmw-led-lamps/)). A diagnostic transport such as UDS over ISO-TP is a **hypothesis** for this exact unit, not a confirmed service list. Capture diagnostics **read-only** during controlled sessions; avoid security access, coding writes, firmware programming and repair-override functions. No working DTC mapping is presently known.
