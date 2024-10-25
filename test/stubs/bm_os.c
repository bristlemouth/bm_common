#include "mock_bm_os.h"
#include <stdlib.h>

void *bm_malloc(size_t size) { return malloc(size); }
void bm_free(void *p) { return free(p); }
DEFINE_FAKE_VALUE_FUNC(BmSemaphore, bm_semaphore_create);
DEFINE_FAKE_VOID_FUNC(bm_semaphore_delete, BmSemaphore);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_semaphore_give, BmSemaphore);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_semaphore_take, BmSemaphore, uint32_t);
DEFINE_FAKE_VOID_FUNC(bm_delay, uint32_t);
DEFINE_FAKE_VALUE_FUNC(uint32_t, bm_get_tick_count);
DEFINE_FAKE_VALUE_FUNC(uint32_t, bm_ms_to_ticks, uint32_t);
DEFINE_FAKE_VALUE_FUNC(uint32_t, bm_ticks_to_ms, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmTimer, bm_timer_create, const char *, uint32_t, bool,
                        void *, BmTimerCb);
DEFINE_FAKE_VOID_FUNC(bm_timer_delete, BmTimer, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_timer_start, BmTimer, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_timer_stop, BmTimer, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_timer_change_period, BmTimer, uint32_t, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmQueue, bm_queue_create, uint32_t, uint32_t);
DEFINE_FAKE_VOID_FUNC(bm_queue_delete, BmQueue);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_queue_receive, BmQueue, void *, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_queue_send, BmQueue, const void *, uint32_t);
DEFINE_FAKE_VALUE_FUNC(BmErr, bm_task_create, BmTaskCb, const char *, uint32_t,
                       void *, uint32_t, void *);
DEFINE_FAKE_VOID_FUNC(bm_task_delete, void *);
