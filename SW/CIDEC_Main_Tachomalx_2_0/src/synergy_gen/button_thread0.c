/* generated thread source file - do not edit */
#include "button_thread0.h"

TX_THREAD button_thread0;
void button_thread0_create(void);
static void button_thread0_func(ULONG thread_input);
static uint8_t button_thread0_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.button_thread0") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
#if (8) != BSP_IRQ_DISABLED
#if !defined(SSP_SUPPRESS_ISR_g_external_irq10) && !defined(SSP_SUPPRESS_ISR_ICU10)
SSP_VECTOR_DEFINE( icu_irq_isr, ICU, IRQ10);
#endif
#endif
static icu_instance_ctrl_t g_external_irq10_ctrl;
static const external_irq_cfg_t g_external_irq10_cfg = { .channel = 10,
		.trigger = EXTERNAL_IRQ_TRIG_FALLING, .filter_enable = true, .pclk_div =
				EXTERNAL_IRQ_PCLK_DIV_BY_64, .autostart = true, .p_callback =
				button_callback_SW5, .p_context = &g_external_irq10, .p_extend =
				NULL, .irq_ipl = (8), };
/* Instance structure to use this module. */
const external_irq_instance_t g_external_irq10 = { .p_ctrl =
		&g_external_irq10_ctrl, .p_cfg = &g_external_irq10_cfg, .p_api =
		&g_external_irq_on_icu };
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void button_thread0_create(void) {
	/* Increment count so we will know the number of ISDE created threads. */
	g_ssp_common_thread_count++;

	/* Initialize each kernel object. */

	UINT err;
	err = tx_thread_create(&button_thread0, (CHAR *) "New Thread",
			button_thread0_func, (ULONG) NULL, &button_thread0_stack, 1024, 1,
			1, 1, TX_AUTO_START);
	if (TX_SUCCESS != err) {
		tx_startup_err_callback(&button_thread0, 0);
	}
}

static void button_thread0_func(ULONG thread_input) {
	/* Not currently using thread_input. */
	SSP_PARAMETER_NOT_USED(thread_input);

	/* Initialize common components */
	tx_startup_common_init();

	/* Initialize each module instance. */

	/* Enter user code for this thread. */
	button_thread0_entry();
}
