#include "lib_state_machine.h"

/*!
  Initialize the state machine

  \param[in] ctx Pointer to the state machine context.
  \param[in] init_state Pointer to the state to start the state machine at.
  \param[in] checkTransitionsForNextState Pointer to the function which will check for state transitions.
  \return N/A
*/
void lib_sm_init(
    LibSmContext *ctx, const LibSmState *init_state,
    CheckTransitionsForNextState check_transitions_for_next_state) {
  // configASSERT(checkTransitionsForNextState != NULL);
  ctx->current_state = init_state;
  ctx->check_transitions_for_next_state = check_transitions_for_next_state;
}

/*!
  Run an iteration of the state machine

  \param[in] ctx Pointer to the state machine context.
  \return N/A
*/
void lib_sm_run(LibSmContext *ctx) {
  // configASSERT(ctx.current_state != NULL);
  // configASSERT(ctx.current_state->run);
  ctx->current_state->run();
  const LibSmState *next_state =
      ctx->check_transitions_for_next_state(ctx->current_state->state_enum);
  // configASSERT(next_state != NULL);
  if (ctx->current_state != next_state) {
    if (ctx->current_state->on_state_exit) {
      ctx->current_state->on_state_exit();
    }
    ctx->current_state = next_state;
    if (ctx->current_state->on_state_entry) {
      ctx->current_state->on_state_entry();
    }
  }
}

/*!
  Returns the current state's string name.

  \param[in] ctx Pointer to the state machine context.
  \return The name of the current state.
*/
const char *lib_sm_get_current_state_name(const LibSmContext *ctx) {
  // configASSERT(ctx.current_state->stateName != NULL);
  return ctx->current_state->state_name;
}

/*!
  Returns the current state's string name.

  \param[in] ctx Pointer to the state machine context.
  \return The name of the current state.
*/
uint8_t get_current_state_enum(const LibSmContext *ctx) {
  return ctx->current_state->state_enum;
}
