#include "state_machine.h"
#include <stdio.h>

static void print_step(const char *step, fle_context_t ctx) {
    printf("%-25s state=%-26s TX=%d faults=%u\n", step, fle_state_name(ctx.state),
           ctx.tx_hardware_enabled ? 1 : 0, (unsigned)ctx.faults);
}

int main(void) {
    fle_context_t ctx;
    fle_inputs_t in = {0};
    fle_init(&ctx);
    print_step("startup", ctx);
    in.power_path_verified = true;
    in.enclosure_closed = true;
    in.temperature_ok = true;
    in.supply_ok = true;
    fle_step(&ctx, in);
    print_step("passive observation", ctx);
    in.physical_interlock_closed = true;
    in.protocol_proof_recorded = true; /* SYNTHETIC, not actual BMW proof. */
    in.request_arm = true;
    fle_step(&ctx, in);
    print_step("arm simulation", ctx);
    in.request_ready = true;
    fle_step(&ctx, in);
    print_step("simulated readiness", ctx);
    in.elapsed_since_heartbeat_ms = 501;
    fle_step(&ctx, in);
    print_step("watchdog timeout", ctx);
    /* No TX at any stage; this binary has no bus/hardware support. */
    return ctx.state == FLE_FAULT_LATCHED && !ctx.tx_hardware_enabled ? 0 : 1;
}
