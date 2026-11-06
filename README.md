# BMW Matrix LED: bench-only interoperability research

> **Research scaffold, not a working BMW headlight controller.** No authentic G30 LCI capture, confirmed lamp connector pinout, BMW DBC/LDF or firmware dump is included. The runnable demonstration is entirely offline.

This project studies how to operate an **owned BMW G30 LCI HELLA 12-channel adaptive matrix LED headlamp** on a current-limited bench, retaining its original Front Light Electronics (FLE). The eventual goal is an independent host MCU communicating over the verified lamp-side vehicle interface. **No use on public roads, no headlight anti-dazzle claims, no security circumvention, no Laserlight activation.**

## Evidence-backed starting point

- **Confirmed (supplier):** HELLA supplied a 12-channel matrix module for the 2020-on facelift BMW 5 Series adaptive LED option; its laser premium variant adds another light source. [HELLA press release, 2021](https://www.hella.com/hella-com/en/press/Technology-Products-27-01-2021-19305.html).
- **Confirmed (supplier):** The BDC requests lighting functions over CAN from the FLE; an FLE drives LEDs and supervises failures, fans and components. [HELLA technical guide](https://www.hella.com/techworld/sg/technical/automotive-lighting/bmw-led-lamps/).
- **Likely (secondary service/training copy):** FLEL and FLER are on G30 **K-CAN3**. [G30 training-material mirror](https://www.bmw5g30.com/control_units_on_the_k_can3-1875.html). A third-party G30 LCI retrofit adapter documents K-CAN3 on **its own adapter connector**, *not the lamp connector*. [Adapter manual](https://www.bmwcustomretrofit.com/Manuals/BMW%20G30_F90%20Facelift%20Headlights%20AdapterBrief%20Overview%20and%20Schematic%20Diagrams%20edition%201_01.pdf).
- **Unknown:** BMW G30 LCI message IDs, bus bitrate, wake sequencing, ECU security/access requirements, external per-pixel commandability, precise internal LED-driver silicon, actual headlamp mating-connector pinout.

## Scope and status

| Milestone | Status | Evidence required to move on |
|---|---|---|
| P0 Safety + asset selection | Planning | Non-laser lamp part/label and protection checklist |
| P1 Passive bus capture | Not started | Verified wiring + captures with test notes |
| P2 Message catalog | Not started | Repeatable captures, bounded isolated replay proof |
| P3 Optional owned-hardware inspection | Gated | Legal review, permission, no protection bypass |
| P4 MCU bench controller | Offline skeleton | Verified lamp-side interface, simulated tests |
| P5 Application firmware | Offline state machine | Verified safe state/fault handling |
| P6 HIL / thermal / optical verification | Not started | Golden fixture, scope, thermal and optical reports |
| P7 Community release | Scaffold | Provenance review, scrub logs, published issues |

**Start here:** [Architecture](docs/01-architecture.md) → [Prior art](docs/02-prior-art.md) → [Toolchain](docs/03-toolchain.md) → [Safety](docs/04-legal-safety.md) → [SoC selection](docs/05-soc-selection.md) → [Implementation](docs/06-implementation-plan.md) → [Risks](docs/07-risk-register.md).

## Safe, hardware-free demo

Requires Python 3.10+ and a C compiler. The Python tools use the standard library only.

```sh
python3 -m unittest discover -s tests -v
python3 tools/candump_catalog.py examples/synthetic_can.log --out /tmp/bmw-frames.csv
cc -std=c11 -Wall -Wextra -Werror -Ifirmware/include firmware/src/state_machine.c firmware/src/main.c -o /tmp/bmw-fle-sim
/tmp/bmw-fle-sim
```

This simulates a controller's safety lifecycle and demonstrates frame cataloging on **synthetic data**. It does not talk to a real CAN adapter, generate BMW messages, operate LEDs, or validate BMW hardware compatibility. The tools intentionally provide **no transmit mode**.

## Critical architecture choice

**Phase 1 uses an STM32G474 / NUCLEO-G474RE for bench-control prototypes**, after passive observation with a known-good isolated USB–CAN adapter. Its multiple FDCAN peripherals provide headroom while retaining deterministic MCU timing ([ST datasheet](https://www.st.com/resource/en/datasheet/stm32g474ve.pdf)). No MCU is sufficient until the actual transport and startup dependencies are measured. **Do not buy or connect a lamp based on inferred pinouts.**

## Repository map

- `research/sources.md`: dated evidence ledger, uncertainty and attribution.
- `hardware/`: functional block diagram, preliminary cost model, unverified pinout worksheet.
- `captures/`: data-sharing/privacy rules and capture schema; no private or copyrighted ECU dumps.
- `protocol/`: zero-message DBC/LDF scaffolds and hypothesis catalog.
- `firmware/`: platform-independent fail-closed state machine, STM32 porting specification, host demo.
- `tools/`: **receive-only/offline** capture cataloging.
- `ROADMAP.md`: phases and atomic issues; `.github/ISSUE_TEMPLATE/` reusable issue forms.

## Contributing

Research is **bench-only and read-only by default**. No forged cryptographic responses, proprietary dumps, road-use modifications, VINs, keys, or personal data in issues. See [CONTRIBUTING.md](CONTRIBUTING.md). License: Apache-2.0 for *original code and writing only*; patents and third-party data retain their original rights. Not affiliated with BMW or HELLA.

Research snapshot: **2026-11-06**. No representation that the full automotive platform has been reverse engineered.