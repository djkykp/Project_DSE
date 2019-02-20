#include "button_thread0.h"
bool on=true;
/* New Thread entry function */
void button_thread0_entry(void) {
	/* TODO: add your own code here */
	g_external_irq10.p_api->open(g_external_irq10.p_ctrl,g_external_irq10.p_cfg);
	g_external_irq10.p_api->enable(g_external_irq10.p_ctrl);
	while (1) {
		tx_thread_sleep(1);
	}
}


void button_callback_SW5(external_irq_callback_args_t * p_args)
{
	//g_ioport.p_api->pinWrite(IOPORT_PORT_01_PIN_14, true);

    	g_ioport.p_api->pinWrite(IOPORT_PORT_01_PIN_14, on);
           on=!on;

}
