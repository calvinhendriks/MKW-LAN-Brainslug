#ifndef MKW_H_
#define MKW_H_

#include <gamespy/gt2.h>
#include <stdint.h>

struct mkw_net_state {
	uint8_t _unk0[0x28 - 0x0];
	int connection_state;
	uint8_t _unk2c[0x29c8 - 0x2c];
};

extern struct mkw_net_state *mkw_net_state;
extern int16_t dwc_gamedata_offset;

struct dwc_gamedata2;

enum dwc_match_state {
	DWC_MATCH_STATE_INIT = 0x0,
	DWC_MATCH_STATE_CL_WAITING = 0x1,
	DWC_MATCH_STATE_CL_SEARCH_HOST = 0x2,
	DWC_MATCH_STATE_CL_WAIT_RESV = 0x3,
	DWC_MATCH_STATE_CL_NN = 0x4,
	DWC_MATCH_STATE_CL_GT2 = 0x5,
	DWC_MATCH_STATE_CL_CANCEL_SYN = 0x6,
	DWC_MATCH_STATE_CL_SYN = 0x7,
	DWC_MATCH_STATE_CL_SVDOWN_1 = 0x8,
	DWC_MATCH_STATE_CL_SVDOWN_2 = 0x9,
	DWC_MATCH_STATE_CL_SVDOWN_3 = 0xa,
	DWC_MATCH_STATE_CL_SEARCH_GROUPID_HOST = 0xb,
	DWC_MATCH_STATE_SV_WAITING = 0xc,
	DWC_MATCH_STATE_SV_OWN_NN = 0xd,
	DWC_MATCH_STATE_SV_OWN_GT2 = 0xe,
	DWC_MATCH_STATE_SV_CANCEL_SYN = 0xf,
	DWC_MATCH_STATE_SV_CANCEL_SYN_WAIT = 0x10,
	DWC_MATCH_STATE_SV_SYN = 0x11,
	DWC_MATCH_STATE_SV_SYN_WAIT = 0x12,
	DWC_MATCH_STATE_WAIT_CLOSE = 0x13,
	DWC_MATCH_STATE_SEARCH_OWN = 0x14
};

struct dwc_gamedata /* size 0x10f8 */ {
	uint8_t _unk00[0x04 - 0x00];
	struct dwc_gamedata2 *gamedata2; /* +0x04 */
	uint8_t _unk08[0x16 - 0x08];
	uint8_t dwc_host_state; /* +0x16 */
	uint8_t _unk17[0x1c - 0x17];
	uint32_t suspend_votes; /* +0x1c */
	uint8_t _unk20[0x28 - 0x20];
	uint32_t dwc_suspend; /* +0x28 */
	uint8_t _unk2c[0x30 - 0x2c];
	uint32_t player_count; /* +0x30 */
	uint8_t _unk34[0x38 - 0x34];
	struct  /* size 0x30 */ {
		uint32_t player_id; /* +0x00 as in Wiimmfi pid */
		uint32_t public_ip; /* +0x04 */
		uint32_t local_ip; /* +0x08 */
		uint16_t public_port; /* +0x0c guess */
		uint16_t private_port; /* +0x0e guess */
		uint32_t communication_ip; /* +0x10 guess */
		uint16_t communication_port; /* +0x14 guess */
		uint8_t peer_index; /* +0x16 maybe or soemthing. */
		uint8_t _unk17[0x28 - 0x17];
		uint32_t players_at_console_little_endian; /* +0x28 */
		uint8_t _unk2c[0x30 - 0x2c];
	} peers[12]; /* +0x38 */
	uint8_t _unk278[0x6d0 - 0x278];
	uint16_t public_port; /* +0x6d0 probably? */
	uint8_t _unk6d2[0x6d4 - 0x6d2];
	uint32_t public_ip; /* +0x6d4 probably? */
	uint8_t _unk6d8[0x6dc - 0x6d8];
	void *sb; /* +0x6dc (it's a pointer to a gamespy thing) */
	uint8_t _unk6e0[0x71c - 0x6e0];
	enum dwc_match_state dwc_match_state; /* +0x71c (0xc means joinable, goes 0xd -> 0x12 during joining see {{CodeRef|RMCP|80279694}}) */
	uint8_t _unk720[0x730 - 0x720];
	uint32_t resv_check_value; /* +0x730 used for room entry message */
	uint8_t _unk734[0x778 - 0x734];
	uint32_t my_pid; /* +0x778 */
	uint32_t host_pid; /* +0x77c */
	uint8_t _unk780[0x7d8 - 0x780];
	uint8_t last_enter_type; /* +0x7d8 type of last 6 or 2 message sent */
	uint8_t _unk7d9[0x7da - 0x7d9];
	uint16_t last_enter_port; /* +0x7da port of last 6 or 2 message sent */
	uint32_t last_enter_ip; /* +0x7dc ip of last 6 or 2 message sent */
	uint8_t _unk7e0[0x860 - 0x7e0];
	uint32_t last_enter_pid; /* +0x860 pid of last 6 or 2 message sent */
	uint32_t last_enter_length; /* +0x864 length of last 6 or 2 message sent */
	uint64_t last_enter_timestamp; /* +0x868 OSGetTick of last 6 or 2 message sent */
	uint8_t _unk870[0x895 - 0x870];
	uint8_t sb_self_lookup_complete; /* +0x895 maybe */
	uint8_t _unk896[0x8a8 - 0x896];
	uint32_t players_at_console_little_endian; /* +0x8a8 */
	uint8_t _unk8ac[0x10f8 - 0x8ac];
};

struct dwc_gamedata2 /* size 0x1458 */ {
	struct gt2_socket *socket;
	uint8_t _unk04[0x14 - 0x04];
	uint32_t buffer_size_send; /* +0x14 0x2000*/
	uint32_t buffer_size_recv; /* +0x18 0x2000 */
	uint8_t _unk1c[0x24 - 0x1c];
	uint32_t online_status; /* +0x24 3 on menus, 5 in frooms */
	uint8_t _unk28[0x64 - 0x28];
	uint32_t my_pid; /* +0x64 */
	uint8_t _unk68[0x360 - 0x68];
	struct dwc_gamedata gamedata; /* +0x360 */
};

static inline struct dwc_gamedata *get_dwc_gamedata(void) {
	struct dwc_gamedata *result;
	asm ("lwzx %0,13,%1" : "=r"(result) : "r"((int)dwc_gamedata_offset));
	return result;
}

#define MII_SIZE 0x4c

struct menu_friend_list_friend /* size 0x1d0 */ {
	uint8_t _unk00[0x08 - 0x00];
	uint64_t friend_code; /* +0x08 */
	uint8_t _unk10[0x18 - 0x10];
	uint16_t flags; /* +0x18 0x1388 normally */
	uint16_t my_wins; /* +0x1a */
	uint16_t friend_wins; /* +0x1c */
	uint8_t _unk1e[0x22 - 0x1e];
	uint8_t mii[MII_SIZE]; /* +0x22 */
	uint8_t _unk6e[0x70 - (0x22 + MII_SIZE)];
	uint8_t country; /* +0x70 */
	uint8_t state; /* +0x71 complete guess */
	uint8_t _unk72[0x74 - 0x72];
	uint16_t longitude; /* +0x74 */
	uint16_t latitude; /* +0x76 */
	uint8_t _unk78[0x1c8 - 0x78];
	uint32_t mii_known; /* +0x1c8 */
	uint8_t _unk1cc[0x1d0 - 0x1cc];
};

struct menu_friend_list_friend_full /* size 0x1d8 */ {
	uint64_t friend_code; /* +0x00 */
	struct menu_friend_list_friend f; /* +0x08 */
};

#endif