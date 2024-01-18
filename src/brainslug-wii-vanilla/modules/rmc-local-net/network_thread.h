#ifndef NETWORK_THREAD_H_
#define NETWORK_THREAD_H_

#include <rvl/OSThread.h>
#include <rvl/so.h>
#include <stdbool.h>
#include <stdint.h>

#include "mkw.h"

#define NETWORK_THREAD_SIZE 0x4000
#define FAKE_PUBLIC_IP 0x08080808

struct peer_info {
	uint32_t ip;
	uint16_t communication_port;
	int8_t status;
};

void* network_thread_main(void *arg);
bool network_thread_get_fake_pid_status(uint32_t pid, uint8_t *status);
void network_thread_after_server_setup(struct dwc_gamedata *gamedata);
void network_thread_on_server_join(struct dwc_gamedata *gamedata);
void network_thread_after_server_join(struct dwc_gamedata *gamedata);
bool network_thread_send_status_record(int type, uint32_t pid, uint32_t ip, uint16_t port, const uint32_t *packet, uint32_t packet_len_in_words);
void network_thread_set_mii(const uint8_t mii[MII_SIZE], uint16_t longitude, uint16_t latitude, uint8_t country, uint8_t state);
void network_thread_set_friend(int index, struct menu_friend_list_friend *f);
struct peer_info network_get_peer_info(unsigned int index);

extern uint8_t network_thread_stack[NETWORK_THREAD_SIZE];
extern OSThread_t network_thread;
extern uint32_t my_fake_pid;
extern uint32_t local_ip;
extern bool network_thread_running;

#endif