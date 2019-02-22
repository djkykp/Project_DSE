#include "pwm_thread0.h"
#include "button_thread0.h"
  #define CLOCK_A         0
  #define CLOCK_B         1
/* Duty control entry function */
void pwm_thread0_entry(void) {
	/* TODO: add your own code here */
	g_external_irq10.p_api->open(g_external_irq10.p_ctrl,g_external_irq10.p_cfg);
	 g_timer0.p_api->open(g_timer0.p_ctrl, g_timer0.p_cfg);

	       //Change Duty cycle around 30% i.e. overriding properties
	       g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, 0, TIMER_PWM_UNIT_PERCENT, CLOCK_B);

	       //start the timer which will product PWM
	       g_timer0.p_api->start(g_timer0.p_ctrl);


	       //initialize timer_1.  1 second interrupt


	       g_timer1.p_api->open (g_timer1.p_ctrl, g_timer1.p_cfg);
	      		    g_timer1.p_api->start (g_timer1.p_ctrl);
	      	/* TODO: add your own code here */
	      	//.p_api->pinWrite(IOPORT_PORT_00_PIN_09, false);

	      		    g_timer1.p_api->periodSet (g_timer1.p_ctrl, 5, TIMER_UNIT_PERIOD_SEC);
	      //uint8_t dutycycle = 0;
	//while (1) {
		//tx_thread_sleep (150);
		            //dutycycle = (dutycycle  + 5) % 100; // Every iteration change Duty Cycle 5% more
		           // g_timer0.p_api->dutyCycleSet(g_timer0.p_ctrl, 0, TIMER_PWM_UNIT_PERCENT, CLOCK_B);
	//}
}
