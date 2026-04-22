#include "uink_thread.h"

#include "cmsis_os2.h"

#include "applications/inc/uink_button.h"
#include "applications/inc/uink_eink.h"
#include "applications/inc/uink_led.h"

static osThreadId_t led_thread_id;
static osThreadId_t eink_thread_id;
static osThreadId_t button_thread_id;

const osThreadAttr_t led_thread_attr = {
  .name       = "led",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 1024,
  .priority   = osPriorityLow,
  .tz_module  = 0,
  .reserved   = 0,
};

const osThreadAttr_t eink_thread_attr = {
  .name       = "eink",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 1024,
  .priority   = osPriorityLow,
  .tz_module  = 0,
  .reserved   = 0,
};

const osThreadAttr_t button_thread_attr = {
  .name       = "button",
  .attr_bits  = 0,
  .cb_mem     = 0,
  .cb_size    = 0,
  .stack_mem  = 0,
  .stack_size = 1024,
  .priority   = osPriorityLow,
  .tz_module  = 0,
  .reserved   = 0,
};

void thread_init(void)
{
	led_thread_id = osThreadNew(led_thread, NULL, &led_thread_attr);
	if (led_thread_id == NULL) {
		return;
	}

	eink_thread_id = osThreadNew(eink_thread, NULL, &eink_thread_attr);
	if (eink_thread_id == NULL) {
		return;
	}

	button_thread_id = osThreadNew(button_thread, NULL, &button_thread_attr);
	if (button_thread_id == NULL) {
		return;
	}
}
