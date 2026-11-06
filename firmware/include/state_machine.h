#ifndef BMW_FLE_RE_STATE_MACHINE_H
#define BMW_FLE_RE_STATE_MACHINE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    FLE_SAFE_OFF = 0,
    FLE_OBSERVING,
    FLE_ARMED_PENDING_PROOF,
    FLE_BENCH_READY_SIMULATED,
    FLE_FAULT_LATCHED
} fle_state_t;

typedef struct {
    bool power_path_verified;
    bool enclosure_closed;
    bool physical_interlock_closed;
    bool temperature_ok;
    bool supply_ok;
    bool protocol_proof_recorded;
    bool request_arm;
    bool request_ready;
    bool explicit_reset;
    uint32_t elapsed_since_heartbeat_ms;
} fle_inputs_t;

typedef struct {
    fle_state_t state;
    bool tx_hardware_enabled; /* Always false in this research release. */
    uint32_t faults;
} fle_context_t;

void fle_init(fle_context_t *context);
void fle_step(fle_context_t *context, fle_inputs_t input);
const char *fle_state_name(fle_state_t state);

#endif
