# Evidence ledger — accessed 2026-11-06

Labels: **C** = confirmed by named primary vendor, regulator, author or university page; **L** = likely, independent derivative/third-party evidence; **S** = speculative or context only; **U** = unverified / inaccessible. Links lead to sources, not unauthorized files. Access dates below are this review's date, not the documents' original dates. No copyrighted technical PDFs are copied into the repository.

| Ref | Classification | Authority and concise assessment | URL |
|---|---|---|---|
| S01 | C | HELLA 2021 manufacturer release: G30 facelift supplier matrix, **12 channels**, optional laser add-on, selective beam. | https://www.hella.com/hella-com/en/press/Technology-Products-27-01-2021-19305.html |
| S02 | C | HELLA technical: BDC-to-FLE **CAN**, local light and fan management, BDC fault storage, classification code/resistor. No CAN IDs listed. | https://www.hella.com/techworld/sg/technical/automotive-lighting/bmw-led-lamps/ |
| S03 | L | G30 training mirror: FLEL and FLER on **K-CAN3**; hosted by unaffiliated site, original BMW authenticity needs independent verification. | https://www.bmw5g30.com/control_units_on_the_k_can3-1875.html |
| S04 | L | 2021 aftermarket G30/F90 facelift retrofit manual: K-CAN3 high/low on **18-pin adapter connector**; **NOT a bare headlamp pinout**; screenshot checked page 5. | https://www.bmwcustomretrofit.com/Manuals/BMW%20G30_F90%20Facelift%20Headlights%20AdapterBrief%20Overview%20and%20Schematic%20Diagrams%20edition%201_01.pdf |
| S05 | L | G30 LCI trade listing for 63119479261 left; physical labels/photos guide part matching but vendor claim is not OEM validation. | https://salparts.com/bmw-5-series-g30-lci-headlamp-adaptive-led-left-63119479261/ |
| S06 | L | Same for 63119479262 right. | https://salparts.com/bmw-5-series-g30-lci-headlamp-adaptive-led-right-63119479262/ |
| S07 | C | TI 2019 architecture: shunt FET pixel dimming and fault retrieval from matrix manager; **not a HELLA BOM**. PDF screenshot checked page 2. | https://www.ti.com/lit/pdf/slyy170 |
| S08 | C | TI TPS92662-Q1 official product: 12-channel, UART, external CAN PHY **not CAN application layer**. | https://www.ti.com/product/TPS92662-Q1 |
| S09 | C | ADI MAX25608 manufacturer page; 12-channel manager, UART evaluation system. | https://www.analog.com/en/products/max25608.html |
| S10 | C | Author's BMW **U11** CAN lighting work; 0x1E4/0x1E6 claims **apply only to author's experiment**, not G30. Published 2024-08-27. | https://medium.com/@metlnt/lumino-bmw-headlight-control-via-ios-app-3f84eb26b417 |
| S11 | C | VŠB Ostrava 2022 university abstract: Teensy 4.1 host, CAN supervisory requests, UART MAX25608; no BMW specificity. | https://dspace.vsb.cz/items/25647d0a-967c-44b9-9da7-1e8250228837 |
| S12 | C | TU Dortmund 2025 dissertation abstract: real-time matrix optical simulation/HIL (up to 1.3 million pixels), no BMW protocol. | https://eldorado.tu-dortmund.de/items/8a14de69-9e92-45fd-9371-6f2b11bb237c |
| S13 | C | ST datasheet: STM32G474 FDCAN1/2/3 and performance. | https://www.st.com/resource/en/datasheet/stm32g474ve.pdf |
| S14 | C | ST NUCLEO-G474RE user manual; vendor schematics/board features. | https://www.st.com/resource/en/user_manual/dm00556337-stm32g4-nucleo64-boards-mb1367-stmicroelectronics.pdf |
| S15 | C | ST support: Nucleo G474 lacks integrated CAN transceiver. | https://community.st.com/stm32-mcus-embedded-software-32/stm32g474re-multiple-fdcan-firmware-166343 |
| S16 | C | NXP S32K1xx cookbook shows CAN FD demo for S32K144. | https://www.nxp.com/docs/en/application-note/AN5413.pdf |
| S17 | C | RealOEM independent catalog shows G05 552 vs 5AZ options. OEM part numbers need exact build match. | https://www.realoem.com/bmw/enUS/showparts?diagId=63_1996&id=JU21-EUR-07-2019-G05-BMW-X5_50iX |
| S18 | C | BMW USA FAQ says full LED standard on 2022/2026 iX; **does not** specify same 12-pixel topology. | https://faq.bmwusa.com/s/article/BMW-iX-from-112021-BMW-iX-from-032025-BMW-headlight-technology-MY22MY26-LPsH5 |
| S19 | L | ZKW 2019 products mention BMW headlamps generally, not the specific chosen G30 LCI matrix part. | https://zkw-group.com/wp-content/uploads/corporate/The-world-of-ZKW-2019.pdf |
| S20 | C | BMW E-series DBC user-maintained reference (MIT); **not G30/K-CAN3**. | https://github.com/dzid26/opendbc-BMW-E8x-E9x |
| S21 | C | Community CAN link index, with BMW category. No G30 12-channel solution verified. | https://github.com/iDoka/awesome-automotive-can-id |
| S22 | C | Offline camera/LED simulation via MAX7219, not OEM protocol; README says MIT. | https://github.com/Omniasherief/Adaptive_Headlights |
| S23 | C | Arduino MAX7219 simulation; no explicit repository license confirmed. | https://github.com/gnoLuV209/Adaptive-Headlights-System-AHS-using-Matrix-Led/ |
| S24 | C | SavvyCAN license is MIT, source code and log tooling. | https://github.com/collin80/SavvyCAN |
| S25 | C | python-can open-source SocketCAN installation/config details. | https://github.com/hardbyte/python-can |
| S26 | C | UN R149 road illumination formal page. | https://unece.org/transport/documents/2021/05/standards/un-regulation-no-149-road-illumination-devices-rid |
| S27 | C | Indian parliamentary answer: Rule 124, AIS010, AIS008, glare, fitting. | https://sansad.in/getFile/loksabhaquestions/annex/1712/AU2340.pdf?source=pqals |
| S28 | C | India copyright act §52(1)(ab),(ac) on interoperability/observation limitations. | https://www.indiacode.nic.in/bitstream/123456789/1367/1/a195714.pdf |
| S29 | C | 2009/24/EC Article 6 legal decompilation limits. | https://eur-lex.europa.eu/legal-content/EN/TXT/?uri=CELEX:32009L0024 |
| S30 | C | US exemption 37 CFR 201.40(b)(13) for vehicle repair/lawful modification; jurisdiction limited. | https://www.copyright.gov/title37/201/37cfr201-40.html |
| S31 | C | US patent by Tesla: LED strings, shunt management, topology background only. | https://patents.google.com/patent/US12426138B2/en |
| S32 | U | User-supplied Granada handle could not be fetched; no verified Audi Q8/Q5/Infiniti thesis identity. | https://hdl.handle.net/10481/80480 |
| S33 | U | Brno ON Semiconductor project identity not content-confirmed. | https://invenio.nusl.cz/record/221255?ln=en |
| S34 | U | US11541805 not content-reviewed; cannot support BMW-specific claims. | https://patents.google.com/patent/US11541805B2/en |
| S35 | L | India NUCLEO-G474RE price INR 2,615.35 including GST at sampled merchant. Pricing volatile. | https://findmychips.com/product/EC-B1A10C4C |
| S36 | L | India Teensy 4.1 price INR 3,545 at sampled merchant. Pricing volatile. | https://robocraze.com/products/teensy-4-1-development-board |
| S37 | C | ST FDCAN high-speed demo on NUCLEO-G474RE. | https://community.st.com/stm32-mcus-60/stm32-fdcan-running-at-8-mb-s-on-nucleo-boards-141121 |

## What the evidence does **not** support

No proof of an individual **BMW FLE silicon** part number, real bare-lamp connector pinout, secret-key scheme, actual frame IDs on G30 LCI, control of individual 12 channels from CAN, LIN or Ethernet between BDC and selected G30 LCI lamp, default CAN speed, DTC list or manufacturer firmware availability. **Do not fill these gaps from generic chip documentation.**

## Method

Names, dates, versions and claims were cross-checked against primary manufacturer/university documentation where available. Retail/retrofit sources were explicitly downgraded. A negative search result is a coverage statement, not proof of nonexistence. PDF references were visually inspected where their content informed specific conclusions; no image or text asset is redistributed.
