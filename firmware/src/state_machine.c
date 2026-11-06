#include "state_machine.h"

#define MAX_HEARTBEAT_AGE_MS 500U
#define FAULT_SAFETY 1U
#define FAULT_TIMEOUT 2U

void fle_init(fle_context_t *context) {
    if (context == 0) return;
    context->state = FLE_SAFE_OFF;
    context->tx_hardware_enabled = false;
    context->faults = 0U;
}

void fle_step(fle_context_t *context, fle_inputs_t in) {
    if (context == 0) return;
    /* No path to TX enable in this version, including simulated ready state. */
    context->tx_hardware_enabled = false;
    if (context->state == FLE_FAULT_LATCHED) {
        if (in.explicit_reset && !in.request_arm && !in.request_ready &&
            !in.physical_interlock_closed) {
            fle_init(context);
        }
        return;
    }
    if (!in.temperature_ok || !in.supply_ok ||
        (context->state != FLE_SAFE_OFF && in.elapsed_since_heartbeat_ms > MAX_HEARTBEAT_AGE_MS)) {
        context->faults |= FAULT_SAFETY;
        if (in.elapsed_since_heartbeat_ms > MAX_HEARTBEAT_AGE_MS)
            context->faults |= FAULT_TIMEOUT;
        context->state = FLE_FAULT_LATCHED;
        return;
    }
    /* A lost verified power path or opened optical enclosure must revoke readiness. */
    if (context->state != FLE_SAFE_OFF &&
        (!in.power_path_verified || !in.enclosure_closed)) {
        context->faults |= FAULT_SAFETY;
        context->state = FLE_FAULT_LATCHED;
        return;
    }
    if ((context->state == FLE_ARMED_PENDING_PROOF ||
         context->state == FLE_BENCH_READY_SIMULATED) &&
        (!in.physical_interlock_closed || !in.protocol_proof_recorded)) {
        context->faults |= FAULT_SAFETY;
        context->state = FLE_FAULT_LATCHED;
        return;
    }
    switch (context->state) {
    case FLE_SAFE_OFF:
        if (in.power_path_verified && in.enclosure_closed)
            context->state = FLE_OBSERVING;
        break;
    case FLE_OBSERVING:
        if (!in.power_path_verified || !in.enclosure_closed) {
            context->state = FLE_SAFE_OFF;
        } else if (in.request_arm && in.physical_interlock_closed &&
                   in.protocol_proof_recorded) {
            context->state = FLE_ARMED_PENDING_PROOF;
        }
        break;
    case FLE_ARMED_PENDING_PROOF:
        if (!in.physical_interlock_closed || !in.enclosure_closed)
            context->state = FLE_SAFE_OFF;
        else if (in.request_ready && in.protocol_proof_recorded)
            context->state = FLE_BENCH_READY_SIMULATED;
        break;
    case FLE_BENCH_READY_SIMULATED:
        if (!in.physical_interlock_closed || !in.enclosure_closed)
            context->state = FLE_SAFE_OFF;
        break;
    case FLE_FAULT_LATCHED:
    default:
        context->faults |= FAULT_SAFETY;
        context->state = FLE_FAULT_LATCHED;
        break;
    }
}

const char *fle_state_name(fle_state_t state) {
    switch (state) {
        case FLE_SAFE_OFF: return "SAFE_OFF";
        case FLE_OBSERVING: return "OBSERVING";
        case FLE_ARMED_PENDING_PROOF: return "ARMED_PENDING_PROOF";
        case FLE_BENCH_READY_SIMULATED: return "BENCH_READY_SIMULATED";
        case FLE_FAULT_LATCHED: return "FAULT_LATCHED";
        default: return "UNKNOWN";
    }
}
