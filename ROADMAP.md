# Milestones, evidence gates and issue backlog

The following are **proposed** issues, not issues already created on GitHub. The matching `.github/ISSUE_TEMPLATE` files can be used once the repo is published. Do not conflate checklist completion with a validated BMW device.

| Issue ID | Milestone | Priority | Deliverable | Exit criterion |
|---|---|---|---|---|
| BMW-001 | P0 – Safety | P0 | Acquire and photograph exact **non-laser** HELLA G30 LCI lamp | Part/option/supplier/revision logged |
| BMW-002 | P0 – Safety | P0 | Validate **lamp** electrical connector (not retrofit adapter) | Independent signoff; unverified pins remain unpowered |
| BMW-003 | P0 – Safety | P0 | Current-limited closed bench, E-stop and temp logging | Safety checkout with forced failure |
| BMW-004 | P1 – Passive | P0 | Record consented K-CAN3 donor/harness traces | 3 independent repeated traces per state |
| BMW-005 | P1 – Passive | P1 | Confirm transport/bitrate/termination/wake | Measurement provenance and scope captures |
| BMW-006 | P2 – Protocol | P0 | Catalog message hypotheses/counters/checksums | Trace-linked entries, no borrowed U11 IDs |
| BMW-007 | P2 – Protocol | P0 | First safe isolated function test, if legal | Repeatable result, zero unexpected faults |
| BMW-008 | P2 – Protocol | P1 | Determine mode-level vs channel-level control | Supported claim or explicit negative result |
| BMW-009 | P3 – Optional board | P2 | PCB optical photo + component marking ledger | No access-protection bypass |
| BMW-010 | P4 – Controller | P1 | NUCLEO-G474RE + protected CAN interface review | Bench electrical signoff |
| BMW-011 | P4 – Controller | P1 | Carrier PCB and watchdog design | Fault and power validation |
| BMW-012 | P5 – Firmware | P0 | Offline fail-closed scheduler and tests | CI tests prove no TX by default |
| BMW-013 | P5 – Firmware | P1 | Versioned validated message schema | Hypothesis-to-capture traceability |
| BMW-014 | P6 – HIL | P1 | Optical lightbox measurements | Repeatable enclosed measurements |
| BMW-015 | P6 – HIL | P1 | Thermal soak, power cycling, fault injection | No uncontrolled output |
| BMW-016 | P7 – Release | P0 | Provenance, privacy and license audit | Public-safe source log and reproducible tests |

## Definition of done for the project

A bench-mounted *specified physical assembly* can reproduce at least one authorized function from standalone equipment **without** proprietary dumps, on-road usage, laser exposure, hidden safety/thermal overrides or untracked dependencies. A separate, harder milestone is independently addressable matrix sectors; it must not be claimed without direct evidence.

## What if authentication blocks the project?

**Stop** active protocol replication, document which observable states are possible, seek officially documented/supplier channels, or pivot to a separately designed generic 12-channel simulation. Do not put access-control circumvention on the roadmap.
