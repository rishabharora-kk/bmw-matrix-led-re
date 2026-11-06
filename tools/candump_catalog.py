#!/usr/bin/env python3
"""Offline-only candump-like logfile cataloger. No interfaces, sockets or TX.

Accepts lines '(unix-s) can0 ID#BYTES' in a simple classic CAN format.
Input must be explicit local file; comments starting # are ignored.
This is not a CAN protocol decoder or evidence of BMW message semantics.
"""
from __future__ import annotations
import argparse
import csv
import re
from collections import defaultdict
from pathlib import Path

LINE = re.compile(r"^\((\d+(?:\.\d+)?)\)\s+(\w+)\s+([0-9A-Fa-f]{1,8})#([0-9A-Fa-f]*)$")


def parse_log(text: str) -> list[tuple[float, str, int, bytes]]:
    result = []
    for index, line in enumerate(text.splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        match = LINE.fullmatch(line)
        if not match:
            raise ValueError(f"invalid classic-CAN line {index}: {line[:120]}")
        timestamp, bus, id_hex, data_hex = match.groups()
        if len(data_hex) % 2 or len(data_hex) > 16:
            raise ValueError(f"invalid CAN payload length line {index}")
        arbitration_id = int(id_hex, 16)
        if arbitration_id > 0x1FFFFFFF:
            raise ValueError(f"out-of-range arbitration ID line {index}")
        result.append((float(timestamp), bus, arbitration_id, bytes.fromhex(data_hex)))
    return result


def summarize(rows: list[tuple[float, str, int, bytes]]) -> list[dict[str, str]]:
    groups = defaultdict(list)
    for ts, bus, frame_id, payload in rows:
        groups[(bus, frame_id)].append((ts, payload))
    report = []
    for (bus, frame_id), samples in sorted(groups.items()):
        sample_times = [t for t, _ in samples]
        intervals = [b - a for a, b in zip(sample_times, sample_times[1:])]
        lengths = sorted({len(p) for _, p in samples})
        report.append({
            "bus": bus,
            "frame_id_hex": f"0x{frame_id:X}",
            "samples": str(len(samples)),
            "observed_dlcs": ";".join(map(str, lengths)),
            "mean_interarrival_ms": f"{1000 * sum(intervals) / len(intervals):.3f}" if intervals else "",
            "distinct_payloads": str(len({p for _, p in samples})),
            "first_payload_hex": samples[0][1].hex().upper(),
        })
    return report


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("input", type=Path)
    parser.add_argument("--out", type=Path, required=True)
    args = parser.parse_args()
    rows = summarize(parse_log(args.input.read_text(encoding="utf-8")))
    args.out.parent.mkdir(parents=True, exist_ok=True)
    fields = ["bus", "frame_id_hex", "samples", "observed_dlcs", "mean_interarrival_ms", "distinct_payloads", "first_payload_hex"]
    with args.out.open("w", encoding="utf-8", newline="") as target:
        writer = csv.DictWriter(target, fieldnames=fields)
        writer.writeheader()
        writer.writerows(rows)
    print(f"Wrote {len(rows)} hypothetical-ID frequency records to {args.out} (no TX)")


if __name__ == "__main__":
    main()
