#include "button_thread0.h"
#include "gx_api.h"
#include "system_api.h"



#include "bsp_cfg.h"



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
	 /** Create message. */
	    //message_to_gx.gx_event.gx_event_type = event;
	   // message_to_gx.state = g_system_state;
	    //message_to_gx.gx_event.gx_event_target = GX_NULL;
	   // message_to_gx.gx_event.gx_event_payload.gx_event_ulongdata = (ULONG) &message_to_gx;
	   // gxe.gx_event_type = GX_EVENT_PEN_DOWN;
	    /** Post message. */
	   // gx_err = gx_system_event_send (&message_to_gx.gx_event);
	   //send_hmi_message (GX_FIRST_SIGNAL);
			//g_ioport.p_api->pinWrite(IOPORT_PORT_00_PIN_09, isOn);
    	g_ioport.p_api->pinWrite(IOPORT_PORT_01_PIN_14, on);
           on=!on;

}
