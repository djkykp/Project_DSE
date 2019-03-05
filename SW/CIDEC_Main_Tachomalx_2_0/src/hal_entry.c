/* HAL-only entry function */
#include "hal_data.h"
#include "gx_api.h"
bool isOn=true;
void hal_entry(void) {
	/* TODO: add your own code here */




}

void timer_end0(timer_callback_args_t *p_args){

	//send_hmi_message (GX_FIRST_SIGNAL);
		//g_ioport.p_api->pinWrite(IOPORT_PORT_00_PIN_09, isOn);
		//timer1_thread0_entry();
isOn=!isOn;
g_timer1.p_api->periodSet (g_timer1.p_ctrl, 1, TIMER_UNIT_PERIOD_SEC);
	}


