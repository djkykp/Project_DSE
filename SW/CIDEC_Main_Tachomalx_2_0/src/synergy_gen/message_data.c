/* generated messaging source file - do not edit */
#include "sf_message.h"
#ifndef SF_MESSAGE_CFG_QUEUE_SIZE
#define SF_MESSAGE_CFG_QUEUE_SIZE (16)
#endif
TX_QUEUE hmi_thread_message_queue;
static uint8_t queue_memory_hmi_thread_message_queue[SF_MESSAGE_CFG_QUEUE_SIZE];
static sf_message_subscriber_t hmi_thread_message_queue_0_0 = { .p_queue =
		&hmi_thread_message_queue, .instance_range = { .start = 0, .end = 0 } };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_TOUCH[] = {
		&hmi_thread_message_queue_0_0, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_TOUCH = {
		.event_class = SF_MESSAGE_EVENT_CLASS_TOUCH, .number_of_nodes = 1,
		.pp_subscriber_group = gp_group_SF_MESSAGE_EVENT_CLASS_TOUCH };
static sf_message_subscriber_t *gp_group_SF_MESSAGE_EVENT_CLASS_RPM_READER[] = {
		&hmi_thread_message_queue_0_0, };
static sf_message_subscriber_list_t g_list_SF_MESSAGE_EVENT_CLASS_RPM_READER = {
		.event_class = SF_MESSAGE_EVENT_CLASS_RPM_READER, .number_of_nodes = 1,
		.pp_subscriber_group = gp_group_SF_MESSAGE_EVENT_CLASS_RPM_READER };
sf_message_subscriber_list_t *p_subscriber_lists[] = {
		&g_list_SF_MESSAGE_EVENT_CLASS_TOUCH,
		&g_list_SF_MESSAGE_EVENT_CLASS_RPM_READER, NULL };
void g_message_init(void);
void g_message_init(void) {
	tx_queue_create(&hmi_thread_message_queue,
			(CHAR *) "HMI Thread Message Queue", 1,
			&queue_memory_hmi_thread_message_queue,
			sizeof(queue_memory_hmi_thread_message_queue));
}
