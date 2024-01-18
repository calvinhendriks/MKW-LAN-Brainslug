#include "port_addresses.h"

/* E, J, P */
static const uint32_t portAddresses[][3] = {
	{ 0x8066B8D4, 0x806726A4, 0x80673038 }, /* login error branch */
	{ 0x8065acc0, 0x80662c84, 0x80663618 }, /* mkw_get_fc_for_current_license */
	{ 0x805c4f88, 0x805d1980, 0x805d20a4 }, /* mkw_load_friends_list_from_save */
	{ 0x805c5098, 0x805d1a90, 0x805d21b4 }, /* mkw_copy_friends_list_to_save */
	{ 0x80660f28, 0x80662678, 0x8066300c }, /* mkw_form_user_record */
	{ 0x809bd938, 0x809c1170, 0x809c2110 }, /* friend tracking structure */
	{ 0x80615148, 0x80646FC4, 0x80647958 }, /* where to go on connect success */
	{ 0x8061a300, 0x8064cc80, 0x8064D614 }, /* what to do when pressing B at friend roster (not a method start) */
	{ 0x8061a204, 0x8064cb84, 0x8064D518 }, /* what to do when pressing A on B at the friend roster (not a method start) */
	{ 0x809BD508, 0x809C0E98, 0x809C1E38 }, /* menu_data */
	{ 0x8066FCE0, 0x80676ab0, 0x80677444 }, /* stop ghosts sending */
	{ 0x8065307c, 0x80656b70, 0x80657504 }, /* mkw_net_main_thread */
	{ 0x805c97f0, 0x805d61e8, 0x805D690C }, /* Remove friend button pressed */
	{ 0x805ddcd0, 0x80601d24, 0x806025B0 }, /* Render Popup */
	{ 0x805c11e0, 0x805cd5dc, 0x805cdd00 }, /* BMG_Print */
	{ 0x80831bcc, 0x8085084c, 0x808511e0 }, /* On Mario Kart Channel pressed (not a method start) */
	{ 0x80839a2c, 0x8085ab28, 0x8085b4bc }, /* On Check Rankings pressed (not a method start) */
};

void *get_port_address(int index) {
	uint8_t game_id = *(uint8_t *)0x80000003;
	int index2 =
		game_id == 'E' ? 0 :
		game_id == 'J' ? 1 :
		game_id == 'P' ? 2 :
		/* deliberate crash! */
		*(volatile int *)0;
	return (void *)portAddresses[index][index2];
}