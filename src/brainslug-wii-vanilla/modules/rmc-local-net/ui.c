#include "ui.h"

#include "build/lan.bmg.h"
#include "network_thread.h"
#include "port_addresses.h"

// declared again in main but with different type!!
void BMG_Print(void *r3, struct bmg_struct *bmg1, struct bmg_struct *bmg2, int messageId, void *parameters);

static struct bmg_struct *get_lan_bmg()
{
	static struct bmg_struct lan_bmg_struct;

	if (!lan_bmg_struct.bmg)
	{
		lan_bmg_struct = (struct bmg_struct) 
		{
			.bmg = lan_bmg,
			.bmg_inf1_plus8 = lan_bmg + 0x20 + 8,
		};

		lan_bmg_struct.bmg_dat1_plus8 =
			(const uint8_t *)lan_bmg_struct.bmg_inf1_plus8 + 
			((const uint32_t *)lan_bmg_struct.bmg_inf1_plus8)[-1];
		lan_bmg_struct.bmg_mid1_plus8 =
			(const uint8_t *)lan_bmg_struct.bmg_dat1_plus8 + 
			((const uint32_t *)lan_bmg_struct.bmg_dat1_plus8)[-1];
	}
	return &lan_bmg_struct;
}

void MyBMG_Print(void *r3, struct bmg_struct *bmg1, struct bmg_struct *bmg2, int messageId, void *parameters)
{
	int ipParams[4];
	switch (messageId)
	{
		case 0x07dd: messageId = 11000; break;
		case 0x0fa2: messageId = 11000; break;
		case 0x13ba: messageId = 11000; break;
		case 0x07e8: messageId = 11001; break;
		case 0x07e9: messageId = 11002; break;
		case 0x07f1: messageId = 11004; break;
		case 0x07f2: messageId = 11005; break;
		case 0x10dc: messageId = 11006; break;
		case 0x1389: messageId = 11007; break;
		case 0x10dd: messageId = 11008; break;
		case 0x138e: messageId = 11009; break;
		case 0x1a36: messageId = 11009; break;
		case 0x10de: messageId = 11010; break;
		case 0x13f7: messageId = 11011; break;
		case 0x083e:
		{
			// 11012, IP and 11013, not connected
			int *intParams = parameters;
			if (intParams && intParams[0] == 0 && intParams[1] == 0 && intParams[2] < 31 && intParams[2] > 0)
			{
				// peer
				int peer = intParams[2] - 1;
				struct peer_info peer_info = network_get_peer_info(peer);
				if (peer_info.ip == 0)
				{
					messageId = 11013;
				}
				else
				{
					ipParams[0] = (peer_info.ip >> 24) & 0xff;
					ipParams[1] = (peer_info.ip >> 16) & 0xff;
					ipParams[2] = (peer_info.ip >>  8) & 0xff;
					ipParams[3] = (peer_info.ip >>  0) & 0xff;
					parameters = ipParams;
					messageId = 11012;
				}
			}
			else if (network_thread_running)
			{
				// assume local
				ipParams[0] = (local_ip >> 24) & 0xff;
				ipParams[1] = (local_ip >> 16) & 0xff;
				ipParams[2] = (local_ip >>  8) & 0xff;
				ipParams[3] = (local_ip >>  0) & 0xff;
				parameters = ipParams;
				messageId = 11012;
			}
			break;
		}
		case 0x1393: messageId = 11014; break;
		case 0x1453: messageId = 11015; break;
		case 0x1450: messageId = 11016; break;
		case 0x100c: messageId = 11019; break;
		case 0x1006: messageId = 11020; break;
		case 0x0fb5: messageId = 11021; break;
		case 0x0fb6: messageId = 11022; break;
		case 0x1451: messageId = 11023; break;
		case 0x14b9: messageId = 11024; break;
		case 0x14ba: messageId = 11024; break;
		case 0x14bf: messageId = 11024; break;
		case 0x14c0: messageId = 11024; break;
		case 0x14c1: messageId = 11024; break;
		case 0x14c2: messageId = 11024; break;
		case 0x14c3: messageId = 11024; break;
		case 0x14c4: messageId = 11024; break;
		case 0x14c5: messageId = 11024; break;
		case 0x14c6: messageId = 11024; break;
		case 0x14c7: messageId = 11024; break;
		case 0x14c8: messageId = 11024; break;
		case 0x14c9: messageId = 11024; break;
		case 0x14ca: messageId = 11024; break;
		case 0x14cb: messageId = 11024; break;
		case 0x14cc: messageId = 11024; break;
		case 0x14cd: messageId = 11024; break;
		case 0x14ce: messageId = 11024; break;
		case 0x14b4: messageId = 11025; break;
		case 0x14b5: messageId = 11026; break;
		case 0x0818: messageId = 11027; break;
		case 0x0841: messageId = 11028; break;
		case 0x0faa: messageId = 11029; break;
		case 0x0fab: messageId = 11030; break;
		case 0x1cea: messageId = 11031; break;
		case 0x1cee: messageId = 11032; break;
		case 0x26af: messageId = 11033; break;
	}

	if (messageId >= 11000 && messageId < 11050)
	{
		bmg1 = get_lan_bmg();
	}

	BMG_Print(r3, bmg1, bmg2, messageId, parameters);
}

void OnRemoveFriendPressed(void *myPanel, void *thisButton)
{
	int peer = ((int *)myPanel)[0x1108 / 4];
	struct peer_info peer_info = network_get_peer_info(peer);
	void *menu_data = *(void **)get_port_address(9);
	menu_data = menu_data ? *(void **)menu_data : 0;
	void *panel4d = menu_data ? ((void **)menu_data)[2 + 0x4d] : 0;

	if (panel4d != 0)
	{
		void *vtbl = *(void **)panel4d;
		void (*setText)(void *this, int message, void *parameters) = ((void **)vtbl)[0x1a];
		if (peer_info.ip == 0)
		{
			setText(panel4d,  11018, 0);
		}
		else
		{
			int params[6] =
			{ 
				(peer_info.ip >> 24) & 0xff,
				(peer_info.ip >> 16) & 0xff,
				(peer_info.ip >>  8) & 0xff,
				(peer_info.ip >>  0) & 0xff,
				peer_info.communication_port,
				peer_info.status
			};
			setText(panel4d, 11017, params);
		}

		void (*renderPopup)(void *thisPanel, int nextPanel, int r5) = get_port_address(13);
		renderPopup(myPanel, 0x4D, 0);
	}
}

void OnMarioKartChannelPressed(void)
{
	void *menu_data = *(void **)get_port_address(9);
	menu_data = menu_data ? *(void **)menu_data : 0;
	void *panel4d = menu_data ? ((void **)menu_data)[2 + 0x4d] : 0;
	void *panel5a = menu_data ? ((void **)menu_data)[2 + 0x5a] : 0;

	if (panel4d != 0 && panel5a != 0)
	{
		void *vtbl = *(void **)panel4d;
		void (*setText)(void *this, int message, void *parameters) = ((void **)vtbl)[0x1a];
		setText(panel4d, 11003, 0);

		void (*renderPopup)(void *thisPanel, int nextPanel, int r5) = get_port_address(13);
		renderPopup(panel5a, 0x4D, 0);
	}
}