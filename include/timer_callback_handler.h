#include <stdint.h>
#include <stdbool.h>

#ifndef TIMER_HANDLER_TASK_PRIORITY
#define TIMER_HANDLER_TASK_PRIORITY 5
#endif

typedef void (*timer_handler_cb)(void * arg);

void timer_callback_handler_init();
bool timer_callback_handler_send_cb(timer_handler_cb cb, void* arg, uint32_t timeoutMs);
