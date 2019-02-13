/* HMI Thread entry function */
#include "hmi_thread.h"

extern void hmi_thread_main(void);

void hmi_thread_entry(void)
{
    hmi_thread_main();
}
