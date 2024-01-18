#ifndef UI_H_
#define UI_H_

struct bmg_struct
{
	const void *bmg;
	const void *bmg_inf1_plus8;
	const void *bmg_dat1_plus8;
	int zero;
	const void *bmg_mid1_plus8;
};

void MyBMG_Print(void *r3, struct bmg_struct *bmg1, struct bmg_struct *bmg2, int messageId, void *parameters);
void OnRemoveFriendPressed(void *myPanel, void *thisButton);
void OnMarioKartChannelPressed(void);

#endif