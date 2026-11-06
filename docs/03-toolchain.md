# 03 — Minimal sufficient bench instrumentation

## Buy in stages, not all at once

| Phase | Tool | Budget in India (indicative, INR) | Why / check |
|---|---|---:|---|
| P0 | Adjustable current-limited 0–30 V supply, **real OCP and output OFF** (10 A capacity conditional on validated nameplate/fuse) | 7,000–15,000 | No unprotected automotive battery. Example [OWON SPE3102 listing](https://robocraze.com/) or equivalent; independently check OCP functionality. |
| P0 | Inline DC fuse, emergency disconnect, shrouded terminals, proper gauge wiring, fire-resistant bench | 1,000–4,000 | **Mandatory** protection; fuse rating chosen from verified lamp data, not guessed. |
| P1 | Linux host + **isolated USB-CAN/CAN-FD adapter supporting SocketCAN/listen-only** | 4,000–15,000+ | Buy only verified galvanic isolation and listen-only support; cheap CANable clones often differ. [SocketCAN/python-can](https://python-can.readthedocs.io/en/stable/interfaces/socketcan.html). |
| P1 | Logic analyzer (10–24 MHz or higher), multimeter, breakout harness | 1,500–5,000 | Identify *unpowered* pins and observe logic; never bridge unknown high-power outputs. |
| P2 | SavvyCAN (free), can-utils (free), python-can (free), cantools (free), canmatrix (free) | 0 | Receive-only analysis, plotting, DBC editing; [SavvyCAN](https://github.com/collin80/SavvyCAN), [python-can](https://github.com/hardbyte/python-can), [cantools](https://github.com/cantools/cantools). |
| P3 optional | SWD/JTAG debugger, board microscopy, EEPROM-safe tooling | 1,000–15,000+ | Only after explicit legal and technical gate; avoid destructive attack/readout bypass. |
| P4 | NUCLEO-G474RE (ST-LINK on board) | ~2,600–4,000 | STM32G474's FDCAN support; [ST manual](https://www.st.com/resource/en/user_manual/dm00556337-stm32g4-nucleo64-boards-mb1367-stmicroelectronics.pdf), [local price](https://findmychips.com/product/EC-B1A10C4C). |
| P4 | Automotive-suitable CAN(-FD) transceiver & passives, ESD/TVS and connector prototypes | 1,000–4,000 | **NUCLEO board does not include a CAN transceiver**. [ST support](https://community.st.com/stm32-mcus-embedded-software-32/stm32g474re-multiple-fdcan-firmware-166343). |
| P6 | Thermal camera/thermocouples, nonflammable light enclosure + diffusor, lux meter or calibrated camera | 3,000–20,000+ | Thermal and output distribution; lux data is not type approval. |

**Price warning:** These are order-of-magnitude planning bands, not binding quotations; listing country, inventory, GST, certification and adapter isolation differ. Minimum P0–P2 spend excluding donor lamp/host: **~₹13.5k–₹39k**. A full engineering-grade setup can cost substantially more. Add customs and replacement lamp liability. Never buy a '₹548 30V/10A PSU' based only on an unverified marketplace search result.

## Read-only workflow

1. Photograph and record harness + target part. Validate supply pins from matching authenticated wiring documentation and multimeter continuity with unit unpowered.
2. Attach an isolation-rated adapter to the **verified differential pair**; hardware listen-only mode; no in-car active perturbations.
3. Record monotonic timestamp, arbitration ID, DLC, payload, bus type, speed with source and state-of-lamp metadata.
4. Store unmodified raw logs in private secured storage; publish **scrubbed, consented derived data** only.
5. Examine with can-utils `candump`, SavvyCAN, `cantools`, `python-can`, scripts in `tools/` and hypotheses in `protocol/frame_catalog.csv`.

Tools for later authorized analysis: Ghidra for legally obtained firmware, binwalk for container inspection, OpenOCD for supported board debug, `udsoncan`/`can-isotp` for *read-only* diagnostics after a separate legality review. No firmware dumping/defeat script is supplied.

## A bus protocol is not a CAN physical layer

TI's TPS92662-Q1 **uses multi-drop UART with an optional CAN transceiver as a physical layer** ([TI](https://www.ti.com/product/TPS92662-Q1)). That is *not* proof the LED manager itself accepts CAN frames. Separate **vehicle-side FLE CAN** from **internal FLE-to-matrix serial communications**.
