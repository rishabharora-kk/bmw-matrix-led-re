# Protocol workbench

`g30_lci_observed.dbc` contains **zero BMW frames** by design. `g30_lci_observed.ldf` is a no-frame declaration skeleton and should only be used if a LIN interface is **physically verified**, which is not the current expectation for external G30 LCI FLE commands. The `frame_catalog.csv` records hypotheses with confidence and explicit experiment references. Do not copy unrelated BMW U11 or older E-series IDs into a G30 DBC as facts.

Promote an item to **confirmed** only after repeated state-controlled captures, a verified target part, and negative-control experiments. No active transmit tools live in this repository.
