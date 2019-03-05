/* generated thread header file - do not edit */
#ifndef BUTTON_THREAD0_H_
#define BUTTON_THREAD0_H_
#include "bsp_api.h"
#include "tx_api.h"
#include "hal_data.h"
#ifdef __cplusplus
extern "C" void button_thread0_entry(void);
#else
extern void button_thread0_entry(void);
#endif
#include "r_icu.h"
#include "r_external_irq_api.h"
#ifdef __cplusplus
extern "C" {
#endif
/* External IRQ on ICU Instance. */
extern const external_irq_instance_t g_external_irq10;
#ifndef button_callback_SW5
void button_callback_SW5(external_irq_callback_args_t *p_args);
#endif
#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* BUTTON_THREAD0_H_ */
