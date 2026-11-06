#include "state_machine.h"
#include <assert.h>
#include <stdio.h>

int main(void) {
    fle_context_t c;
    fle_inputs_t in = {0};
    fle_init(&c);
    assert(c.state == FLE_SAFE_OFF && !c.tx_hardware_enabled);
    in.power_path_verified = true;
    in.enclosure_closed = true;
    in.temperature_ok = true;
    in.supply_ok = true;
    fle_step(&c, in);
    assert(c.state == FLE_OBSERVING && !c.tx_hardware_enabled);
    in.request_arm = true;
    in.physical_interlock_closed = true;
    fle_step(&c, in);
    assert(c.state == FLE_OBSERVING); /* cannot arm without proof */
    in.protocol_proof_recorded = true;
    fle_step(&c, in);
    assert(c.state == FLE_ARMED_PENDING_PROOF && !c.tx_hardware_enabled);
    in.request_ready = true;
    fle_step(&c, in);
    assert(c.state == FLE_BENCH_READY_SIMULATED && !c.tx_hardware_enabled);
    in.elapsed_since_heartbeat_ms = 501;
    fle_step(&c, in);
    assert(c.state == FLE_FAULT_LATCHED && !c.tx_hardware_enabled);
    in.elapsed_since_heartbeat_ms = 0;
    fle_step(&c, in);
    assert(c.state == FLE_FAULT_LATCHED); /* latched */
    in.request_arm = false;
    in.request_ready = false;
    in.physical_interlock_closed = false;
    in.explicit_reset = true;
    fle_step(&c, in);
    assert(c.state == FLE_SAFE_OFF && !c.tx_hardware_enabled);
    /* Interlock opening during a simulated armed state must latch a fault. */
    fle_init(&c);
    in.explicit_reset = false;
    in.request_arm = false;
    in.request_ready = false;
    in.physical_interlock_closed = false;
    fle_step(&c, in);
    assert(c.state == FLE_OBSERVING);
    in.physical_interlock_closed = true;
    in.request_arm = true;
    fle_step(&c, in);
    assert(c.state == FLE_ARMED_PENDING_PROOF);
    in.physical_interlock_closed = false;
    fle_step(&c, in);
    assert(c.state == FLE_FAULT_LATCHED && !c.tx_hardware_enabled);
    puts("STATE_MACHINE_TESTS_PASS");
    return 0;
}
