/* HAL-only entry function */
#include "hal_data.h"
bool isOn=true;
void hal_entry(void) {
	/* TODO: add your own code here */
	g_timer1.p_api->open (g_timer1.p_ctrl, g_timer1.p_cfg);
			    g_timer1.p_api->start (g_timer1.p_ctrl);
		/* TODO: add your own code here */
		//.p_api->pinWrite(IOPORT_PORT_00_PIN_09, false);

			    g_timer1.p_api->periodSet (g_timer1.p_ctrl, 5, TIMER_UNIT_PERIOD_SEC);

}

void timer_end0(timer_callback_args_t *p_args){


		g_ioport.p_api->pinWrite(IOPORT_PORT_00_PIN_09, isOn);
		//timer1_thread0_entry();
isOn=!isOn;
g_timer1.p_api->periodSet (g_timer1.p_ctrl, 5, TIMER_UNIT_PERIOD_SEC);
	}


