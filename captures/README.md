# Capture submission protocol

Raw logs belong in **private** storage until rights and identifier-scrubbing have been reviewed. Do not commit donor VIN, location, owner-identifying details, diagnostic keys, protected firmware or copyrighted OEM files.

## Format

Preferred `candump -L` output with monotonic-synchronized study time logged separately, e.g. `(<timestamp>) can0 <id>#<hexbytes>`; CAN-FD extended notation allowed after identifying capture adapter dialect. Use `capture_manifest.template.yaml` for hash of raw file, hardware variant, lamp state, bus physical bitrate (measured, not assumed), trigger timestamp, environment and whether optical box was closed.

Run offline analysis with:

```sh
python3 tools/candump_catalog.py examples/synthetic_can.log --out /tmp/catalog.csv
```

> The `examples/` file contains **fabricated** frame IDs and values for parser demonstration. It is **not BMW CAN traffic**.

Do not submit traces taken by injecting onto public-road vehicles. A minimal, derivative frame table is preferred for collaboration; retain a private chain of custody for the raw original.
