# 04 — Legal, road safety and laboratory controls

**Not legal advice.** Bench interoperability is not a blanket permission to bypass access controls or redistribute firmware. Confirm project-specific obligations with counsel.

## Regulatory references

- **India**: Copyright Act 1957 §52(1)(ab) recognizes limited acts necessary to learn information essential to interoperability by lawful possessors when not readily available; subsection (ac) addresses observation/study/test. This does **not** automatically authorize defeating all technological measures or redistributing code. [India Code](https://www.indiacode.nic.in/bitstream/123456789/1367/1/a195714.pdf).
- **India road-use**: Government response confirms CMVR Rule 124, AIS:010 (headlamp performance) and AIS:008 (four-wheeler installation); glare restrictions apply on roads. [Lok Sabha answer](https://sansad.in/getFile/loksabhaquestions/annex/1712/AU2340.pdf?source=pqals). Also consult CMVR rules 105–106 and subsequent amendments ([text](https://indiankanoon.org/doc/28072254/)).
- **UNECE**: [UN R48](https://unece.org/transport/vehicle-regulations-wp29), [R149](https://unece.org/transport/documents/2021/05/standards/un-regulation-no-149-road-illumination-devices-rid), legacy [R123 AFS](https://unece.org/transport/vehicle-regulations-wp29) concern lighting installation/performance. Bench testing gives no homologation.
- **EU**: Directive 2009/24/EC Art. 6 limits decompilation for necessary interoperability under specific conditions. Jurisdiction and license matter. [EUR-Lex](https://eur-lex.europa.eu/legal-content/EN/TXT/?uri=CELEX:32009L0024).
- **US**: 37 CFR §201.40(b)(13) provides a *limited* vehicle software diagnosis/repair/lawful-modification exemption, not general safe harbor or authority to violate transport regulations. [U.S. Copyright Office](https://www.copyright.gov/title37/201/37cfr201-40.html).

## Do

- Work only on lawfully acquired and accurately identified **non-laser** lamp electronics, on an enclosed bench.
- Current-limit and fuse power according to **validated load data**, use a disconnect and isolate CAN instrumentation.
- Leave lamp thermal/fault shutdowns active; record power, housing temperature and elapsed-on time.
- Prefer read-only observation; write down consent, source, provenance and redaction of personal/vehicle IDs.
- Stop on heating, smoke, abnormal fan behavior, loss of bus, unexpected restart, or fixture temperature breach.

## Don't

- Do not install or operate altered beam output on public roads.
- Do not energize a BMW Laserlight emitter (or open its laser optical pathway); qualified laser professionals only.
- Do not connect unknown pins to 12 V because of a similarly shaped adapter connector.
- Do not bypass FLE thermal protection, lamp coding/security, BDC/CAS/immobilizer functions or secure boot.
- Do not share copyrighted firmware, protected calibrations, diagnostic keys, VINs, personal information or unauthorized OEM repair documentation.
- Do not perform brute-force/fuzzing on a live car bus. Even on a bench, only isolated, explicit allowlisted bounded tests after risk review.

## Protective controls and halt criteria

| Risk | Prevention | Immediate halt trigger |
|---|---|---|
| Electrical short | Proven pinout, inline fuse, current-limited supply and isolation | Current spike, fuse trip, supply voltage collapse |
| Optical harm | Closed flame-resistant enclosure, opaque baffles, no direct-view testing | Open enclosure or uncontrolled beam |
| Thermal damage | Preserve OEM fan/temperature monitoring, log thermocouples | Missing fan, temperature/voltage beyond measured safe envelope |
| ECU corruption | No diagnostics write, firmware programming, or speculative bus injection | Unexpected DTC or ECU reboot |
| Laser exposure | Non-laser variant only | Any laser caution marking or unknown variant |
