# 07 — Risk register, updated 2026-11-06

Severity / likelihood 1 low–5 high; risk score product. Residual risks need real bench measurements before reprioritization.

| ID | Risk | Sev. | Like. | Score | Mitigation / owner | Gate |
|---|---|---:|---:|---:|---|---|
| R01 | Incorrect power/connector pins destroy rare OEM lamp | 5 | 4 | 20 | Photograph, match exact part, validated wiring, continuity test, independent review | No power until P0 sign-off |
| R02 | Incorrect current/fuse or failed fan causes heating/fire | 5 | 3 | 15 | OCP, fuse, physical E-stop, opaque enclosure, thermocouples, fan fault timeout | P0 & P6 |
| R03 | Laserlight mistaken for LED variant | 5 | 3 | 15 | Exclude units with laser source/class labeling; visual supplier-ID review | P0 |
| R04 | Vehicle interface uses unsupported/secured messaging | 4 | 4 | 16 | Passive evidence; stop at access-control boundary; seek licensed interface | P2 stop/go |
| R05 | 12 matrix channels not independently commandable externally | 4 | 4 | 16 | Validate with controlled capture, limit claims to verified functions | P2 exit |
| R06 | Wrong CAN/K-CAN3 rate/termination corrupts network | 4 | 3 | 12 | Hardware listen-only; scope; verify physical network; avoid car-side injection | P1 |
| R07 | Captured frames expose VIN or proprietary firmware | 4 | 3 | 12 | Private originals, redaction, explicit contribution screening | P7 |
| R08 | Debug read corrupts controller or breaches license | 5 | 3 | 15 | Visual inspection first, legal review, no RDP defeat or flash writes | Optional P3 |
| R09 | Donor supply/region/headlight part differs | 3 | 4 | 12 | Identity sheet including LHD/RHD, build year and software version | P0 |
| R10 | Experimental beam enters road traffic | 5 | 2 | 10 | No road installation, enclosed testbox, labeling and transport protocol | All phases |
| R11 | Cheap USB-CAN lacks galvanic isolation or CAN-FD | 4 | 3 | 12 | Verify vendor datasheet, host isolation and listen-only before purchase | P1 |
| R12 | Scope expansion into custom high-current LED driver | 5 | 4 | 20 | Keep original FLE; separate funded and qualified independent project | P4 |

## Stop conditions

Stop and disconnect lamp supply on unexpected brightness, restart loops, heat, power abnormality, fan loss, unknown function change, diagnostic corruption, unlocked optical enclosure or a security challenge. Log before any reattempt; never normalize a fault by emulating 'healthy' status.
