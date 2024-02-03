/* main.c
 *   by Alex Chadwick
 * 
 * Copyright (C) 2014, Alex Chadwick
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <bslug.h>

#include <gamespy/sb.h>
#include <stdint.h>
#include <rvl/dwc.h>
#include <rvl/OSLink.h>
#include <rvl/OSTime.h>
#include <rvl/OSThread.h>

#include "mkw.h"
#include "network_thread.h"
#include "port_addresses.h"
#include "ui.h"

/* Which game to support. ? is a wild card (e.g. RMC? is any version of Mario
 * Kart Wii) */
BSLUG_MODULE_GAME("RMC?");
BSLUG_MODULE_NAME("MKW LAN multiplayer");
BSLUG_MODULE_VERSION("v0.9");
BSLUG_MODULE_AUTHOR("Chadderz and MrBean35000vr");
BSLUG_MODULE_LICENSE("BSD");

extern void _start(void);

extern uint32_t DWC_ConnectToGameServerAsync2[];
static void on_populate_friend(struct menu_friend_list_friend *friend, void *save_file_license, int index);
static void sleep_a_frame(void);
uint32_t BMG_Print[2];

static struct /* size 0x24 */ {
  uint8_t _unk00[0x1c - 0x00];
  uint32_t pid; /* +0x1c */
  uint8_t _unk20[0x24 - 0x20];
  uint32_t game_id; /* +0x24 RMCJ */
} pid_struct;

#define POKE_B(addr, dest) do { *(uint32_t*)(addr) = 0x48000000 + (((uint32_t)(dest) - (uint32_t)(addr)) & 0x3ffffff); } while (0)
#define POKE_BL(addr, dest) do { *(uint32_t*)(addr) = 0x48000001 + (((uint32_t)(dest) - (uint32_t)(addr)) & 0x3ffffff); } while (0)
#define RELOC_HA(dest) ((((uint32_t)dest) + 0x8000) >> 16)
#define RELOC_LO(dest) (((uint32_t)dest) & 0xffff)

#if 0
// beans endless thing
uint32_t array_yay_woo[] = {
0x3C60809C ,0x80631E38,
0x8083000C ,0x2C040060,
0x40A2000C ,0x38800058,
0x9083000C ,0x7FC3F378,
0x4e800020
};
	POKE_BL(0x80009918, array_yay_woo);
#endif

static void _start_patches(void) {

	// fix for le-code distributions
	if(*(uint32_t *)_start == 0x7ea802a6){
		*(uint32_t *)0x80000034 = *(uint32_t *)0x80000034 + 8;
		*(uint32_t *)0x80000038 = *(uint32_t *)0x80000038 + 8;
	}
	
	// force us to know ourselves
	DWC_ConnectToGameServerAsync2[0x3B] = 0x48000100;
	DWC_ConnectToGameServerAsync2[0x7E] = 0x38000001;
	
	// work out where dwc_gamedata is
	dwc_gamedata_offset = ((int16_t *)&dwc_process_status_record)[0xb];
	
	// stop the error condition preventing all online processing.
	// TODO: this is actually patching the method starting 800ccc68 so this may not port.
	((uint32_t *)&dwc_unknown_800ccc38)[0xF] = 0x60000000;
	
	// prevent error 5 when sending packets
	dwc_unknown_800d577c[0x203] = 0x48000014;
	
	// disconnect gracefully on state machine lockup in joins
	void *menu_data = get_port_address(9);
	((uint32_t *)&dwc_think)[0x44] = 0x3c600000 + RELOC_HA(menu_data);
	((uint32_t *)&dwc_think)[0x45] = 0x80630000 + RELOC_LO(menu_data);
	((uint32_t *)&dwc_think)[0x46] = 0x80630000;
	((uint32_t *)&dwc_think)[0x47] = 0x80630274;
	((uint32_t *)&dwc_think)[0x48] = 0x80a3035c;
	((uint32_t *)&dwc_think)[0x49] = 0x2c050001;
	((uint32_t *)&dwc_think)[0x4a] = 0x40821a80;
	((uint32_t *)&dwc_think)[0x4b] = 0x38a00002;
	((uint32_t *)&dwc_think)[0x4c] = 0x90a3035c;
	((uint32_t *)&dwc_think)[0x4d] = 0x48001a74;
	_start();
}

static int OSLink_patches(void* location1, void* location2) {
	int ret = OSLink(location1, location2);

	/* force no network error */
	*(uint32_t *)get_port_address(0) = 0x48000060;

	/* forces our fc load method to use the fake pid (rather than save file). */
	uint32_t *mkw_get_fc_for_current_license  = get_port_address(1);
	mkw_get_fc_for_current_license[8] = 0x3c600000 + RELOC_HA(&pid_struct);
	mkw_get_fc_for_current_license[9] = 0x38630000 + RELOC_LO(&pid_struct);

	/* make friend list populate by us. */
	uint32_t *mkw_load_friends_list_from_save = get_port_address(2);
	mkw_load_friends_list_from_save[0x1a] = 0x60000000;
	mkw_load_friends_list_from_save[0x1b] = 0x7fa5eb78;
	mkw_load_friends_list_from_save[0x1f] = 0x60000000;
	/* prevent it saving */
	POKE_BL(&mkw_load_friends_list_from_save[0x1c], on_populate_friend);
	uint32_t *mkw_copy_friends_list_to_save = get_port_address(3);
	mkw_copy_friends_list_to_save[0] = 0x4e800020;

	/* Limit functionality of WFC to just friends section */
	*(uint32_t *)get_port_address(6) = 0x3860008D;
	*(uint32_t *)get_port_address(7) = 0x41820028;
	*(uint32_t *)get_port_address(8) = 0x41820030;

	/* Stop ghosts from attempting to send to WFC. There's no point. */
	uint32_t *stop_ghost_send = get_port_address(10);
	stop_ghost_send[0x0] = 0x38600000;
	stop_ghost_send[0x1] = 0x4e800020;

	/* High data rate. */
	uint32_t *mkw_net_main_thread = get_port_address(11);
	POKE_BL(&mkw_net_main_thread[0x12B], sleep_a_frame);
	/* strictly speaking these are the next method over. */
	mkw_net_main_thread[0x269] = 0x28040007;
	mkw_net_main_thread[0x296] = 0x3b400000;

	/* Custom behaviour for Remove Friend */
	POKE_B(get_port_address(12), &OnRemoveFriendPressed);

	/* Wrap BMG_Print to allow interception. */
	uint32_t *BMG_Print_loc = get_port_address(14);
	if (BMG_Print[0] == 0)
		BMG_Print[0] = BMG_Print_loc[0];
	POKE_B(&BMG_Print[1], (uint32_t)BMG_Print_loc + 4);
	POKE_B(&BMG_Print_loc[0], MyBMG_Print);

	/* Disable Mario Kart Channel */
	uint32_t *mk_channel_pressed = get_port_address(15);
	POKE_BL(&mk_channel_pressed[0], &OnMarioKartChannelPressed);
	mk_channel_pressed[1] = 0x480002F8;

	/* Disable check rankings */
	*(uint32_t *)get_port_address(16) = 0x48000724;

	return ret;
}

#define SLEEP_TARGET microsecs_to_ticks(16666)

static void sleep_a_frame(void) {
	static uint32_t last_time;
	uint32_t this_time;
	asm volatile ("mftbl %0" : "=r"(this_time));

	uint32_t difference = this_time - last_time;
	if (difference < SLEEP_TARGET) {
		OSSleepTicks(SLEEP_TARGET - difference);
		this_time += SLEEP_TARGET - difference;
	}
	last_time = this_time;
}

static void setup_pid(struct dwc_gamedata *gamedata) {
	while (my_fake_pid <= 30) {
		asm volatile ("mftbl %0" : "=r"(my_fake_pid));
	}
	gamedata->my_pid = my_fake_pid;
	gamedata->gamedata2->my_pid = my_fake_pid;
	pid_struct.pid = my_fake_pid;
	pid_struct.game_id = 0x524D434A; // RMCJ
}

static void on_populate_friend(struct menu_friend_list_friend *friend, void *save_file_license, int index) {
	network_thread_set_friend(index, friend);
}

static uint8_t mii[MII_SIZE];

static void get_mii(void) {
	uint8_t user_record[0xc8];
	((void (*)(uint8_t *))get_port_address(4))(user_record);
	for (int i = 0; i < MII_SIZE; i++)
		mii[i] = user_record[i + 16];
	network_thread_set_mii(mii, ((uint16_t *)user_record)[0xbc / 2], ((uint16_t *)user_record)[0xbe / 2], user_record[0xb8], user_record[0xb9]);
}

static void setup_friends(void) {
	uint32_t *friend_struct = *(uint32_t **)get_port_address(5);
	friend_struct += 0x9c / 4;
	for (int i = 0; i < 30; i++) {
		friend_struct[i * 3 + 0] = 0x3800;
		friend_struct[i * 3 + 1] = i + 1;
	}
}

static int MyDWC_LoginAsync(void *r3, int r4, void (*r5)(int, int, void *), void *r6) {
	setup_pid(get_dwc_gamedata());
	get_mii();
	setup_friends();
	mkw_net_state = r6;
	OSCreateThread(&network_thread, network_thread_main, 0, network_thread_stack + NETWORK_THREAD_SIZE, NETWORK_THREAD_SIZE, 0x18, false);
	OSResumeThread(&network_thread);
	return 0;
}


static uint8_t Mydwc_get_friend_status(const struct dwc_buddy *buddy, uint8_t *loc, int *loc_length) {
	if (network_thread_get_fake_pid_status(buddy->pid, loc)) {
		*loc_length = 8;
		return 1;
	} else {
		*loc_length = -1;
		return 0;
	}
}

static bool MyDWC_SetupGameServer(int player_count, void (*r4)(void *), void *r5, int r6, int r7, void (*r8)(void *), uint8_t *r9, void *r10) {
	struct dwc_gamedata *gamedata = get_dwc_gamedata();
	setup_pid(gamedata);
	bool result = DWC_SetupGameServer(player_count, r4, r5, r6, r7, r8, r9, r10);
	network_thread_after_server_setup(gamedata);
	return result;
}

static bool MyDWC_ConnectToGameServerAsync(int player_count, void (*r4)(void *), void *r5, int r6, int r7, void (*r8)(void *), uint8_t *r9, void *r10) {
	struct dwc_gamedata *gamedata = get_dwc_gamedata();
	setup_pid(gamedata);
	network_thread_on_server_join(gamedata);
	bool result = DWC_ConnectToGameServerAsync(player_count, r4, r5, r6, r7, r8, r9, r10);
	network_thread_after_server_join(gamedata);
	return result;
}

static int Mydwc_qr2_init(uint32_t pid) {
	// let's not and say we did
	return 0;
}

static int MyDWCi_SBUpdateAsync(uint32_t pid) {
	// let's not and say we did
	return 0;
}

static int Mydwc_send_status_record(int type, uint32_t pid, uint32_t ip, uint16_t port, const uint32_t *packet, size_t packet_len_in_words) {
	return network_thread_send_status_record(type, pid, ip, port, packet, packet_len_in_words) ? 0 : 1;
}

static uint32_t MyServerBrowserGetMyPublicIPAddr(void *sb) {
	return FAKE_PUBLIC_IP;
}

BSLUG_MUST_REPLACE(_start, _start_patches);
BSLUG_MUST_REPLACE(OSLink, OSLink_patches);
BSLUG_MUST_REPLACE(DWC_LoginAsync, MyDWC_LoginAsync);
BSLUG_MUST_REPLACE(dwc_get_friend_status, Mydwc_get_friend_status);
BSLUG_MUST_REPLACE(DWC_SetupGameServer, MyDWC_SetupGameServer);
BSLUG_MUST_REPLACE(DWC_ConnectToGameServerAsync, MyDWC_ConnectToGameServerAsync);
BSLUG_MUST_REPLACE(dwc_qr2_init, Mydwc_qr2_init);
BSLUG_MUST_REPLACE(DWCi_SBUpdateAsync, MyDWCi_SBUpdateAsync);
BSLUG_MUST_REPLACE(dwc_send_status_record, Mydwc_send_status_record);
BSLUG_MUST_REPLACE(ServerBrowserGetMyPublicIPAddr, MyServerBrowserGetMyPublicIPAddr);
