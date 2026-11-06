# 02 — Ranked prior art (relevance is not BMW G30 protocol completeness)

| Rank | Work | Verified result / reusable material | License / limitation | Evidence |
|---:|---|---|---|---|
| 1 | **Lumino / BMW U11 (2024)** | G-series-adjacent active BMW lighting CAN observations; claims ID `0x1E6` varies with indicator and `0x1E4` varies with DRL. Describes a BDC command conflict from in-car injection. **U11 only; not a G30 DBC, not a safe bench recipe.** | Article; associated code license/repository not verified | [Author article](https://medium.com/@metlnt/lumino-bmw-headlight-control-via-ios-app-3f84eb26b417) |
| 2 | **G30/F90 LCI retrofit adapter (2021)** | A commercial retrofit bridge explicitly connects a BDC K-CAN3 pair to a headlight-side K-CAN3 pair, strengthening *transport choice*. Adapter connector is not the lamp connector! | Third-party proprietary document; no firmware/code license | [Adapter PDF](https://www.bmwcustomretrofit.com/Manuals/BMW%20G30_F90%20Facelift%20Headlights%20AdapterBrief%20Overview%20and%20Schematic%20Diagrams%20edition%201_01.pdf) |
| 3 | **VŠB Ostrava / Drozd (2022)** | Thesis documents Teensy 4.1 light control unit receiving CAN from vehicle controller and talking UART to MAX25608. Strong **generic architecture** precedent. | University thesis, reuse permissions not assumed; *not BMW*. | [University abstract](https://dspace.vsb.cz/items/25647d0a-967c-44b9-9da7-1e8250228837) |
| 4 | **TI LMM ECU architecture (2019)** | Generic 6/12-pixel shunt topology; LED fault reporting over UART. Helpful for evaluating internal architecture, **not a BMW teardown**. | TI publication, copyright retained | [TI](https://www.ti.com/lit/pdf/slyy170) |
| 5 | **TU Dortmund / Waldner (2025)** | Real-time headlamp simulation, HIL and lighting-function testing, up to 1.3m controllable sources. Useful validation concepts, not G30 control frames. | Dissertation, no code license confirmed | [University record](https://eldorado.tu-dortmund.de/items/8a14de69-9e92-45fd-9371-6f2b11bb237c) |
| 6 | **BMW E-series DBC (dzid26)** | Good DBC annotation conventions and general BMW decoding process; **old E-series 100 kbps K-CAN cannot supply G30 K-CAN3 IDs or speed**. | MIT per repository | [GitHub](https://github.com/dzid26/opendbc-BMW-E8x-E9x) |
| 7 | **iDoka automotive CAN IDs** | Discovery index containing BMW references; cross-platform context, no validated G30 matrix commands found. | Curated links; per-target license varies | [GitHub](https://github.com/iDoka/awesome-automotive-can-id) |
| 8 | **Omniasherief/Adaptive_Headlights** | Video object detection + matrix simulation; useful fixture/UI demonstration but MAX7219 != BMW pixel driver. | MIT per repo | [GitHub](https://github.com/Omniasherief/Adaptive_Headlights) |
| 9 | **gnoLuV209 AHS** | Arduino, camera and MAX7219 testbed. Not a BMW or Audi OEM protocol RE. | No explicit LICENSE confirmed; don't copy | [GitHub](https://github.com/gnoLuV209/Adaptive-Headlights-System-AHS-using-Matrix-Led/) |
| 10 | **US12426138B2 (Tesla)** | Public LED string/shunt pairing concept; *not* evidence of BMW part selection. | Patent; licensing not granted by publication | [Patent](https://patents.google.com/patent/US12426138B2/en) |

## Unverified leads held outside the evidence core

- University of Granada handle [10481/80480](https://hdl.handle.net/10481/80480) was **not retrievable in this review**, and an Audi Q8/Q5/Infiniti thesis matching the prompt's description could not be independently confirmed from the handle. Do **not** cite its claimed LIN capture, IC, or PCB as verified. Need metadata/title/author and the actual document before ranking it. A distinct Granada thesis titled *Design of PWM automotive lights tester* is available but is **not evidence** of the claimed Audi LIN work ([PDF](https://digibug.ugr.es/bitstream/handle/10481/80477/TFG__Gregorio_Luces_Valeo%20%289%29.pdf?sequence=1)).
- Brno record [221255](https://invenio.nusl.cz/record/221255?ln=en), patent [US11541805](https://patents.google.com/patent/US11541805B2/en) and `Champ00155/Matrix-adaptive-HL` require content-level confirmation before technical conclusions are taken from them.
- Forum wiring posts are *leads*, not electrically safe pinouts, until measured on a documented **matching assembly**.

## Search coverage / negative result

As of **2026-11-06**, targeted searches across GitHub, supplier documentation, BMW forum references, university results and CAN tool repositories yielded **no independently verified public complete G30 LCI BMW Selective Beam FLE firmware/protocol implementation**. That is *not proof none exists*. Search improvements: exact FLE HW number, supplier markings, donor-year parts, `K-CAN3 FLEL FLER` and frame/counter terms after hardware identity is established.
