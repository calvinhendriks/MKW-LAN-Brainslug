#pragma once

#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <UI/Screen/SpecificScreens/SharedStructs.hpp>
#include <UI/Screen/SpecificScreens/GhostManager.hpp>
#include <Misc/Mii.hpp>

class GhostInfoControl : public LayoutUIControl {
public:
    GhostInfoControl(); //0x805e274c
    virtual ~GhostInfoControl(); //0x805e27dc vtable 808b92c0
    MiiGroup miiGroup; //0x174
    //0x20c
    u8 unknown_0x20C[0x234-0x20c];
    u32 unknown_0x234; //set to 0
    u16 unknown_0x238; //set to 0
    u16 unknown_0x23A; //set to 0
    float unknown_0x23C;
    float unknown_0x240;
    u16 unknown_0x244;
    u16 unknown_0x246;
    u32 unknown_0x248; //gets set to 0x00080000 in the ctor
}; //total size 0x24C


class GhostSelectScreen : public Screen { //808bebd8
public:
    GhostSelectScreen(); //0x806395ec vtable 808bec2c
    virtual ~GhostSelectScreen(); //0x8063982c
    ScreenActionController screenactionController; //0x44
    CtrlMenuPageTitleText ctrlMenuPageTitleText; //0x268
    GhostInfoControl ghostInfo; //loads GhostInfo brctr
    GhostInfoControl ghostInfo2; //first for easy, 2nd for expert?
    ArrowPairControl arrowPairControl; //0x874
    LayoutUIControl pageNumber;
    PushButton challengeGhostButton;
    PushButton watchReplayButton;
    PushButton soloTTButton;
    CtrlMenuBackButton backButton; //ends at 1880
    GhostInfoControl *info;
    GhostInfoControl *info2;
    u32 unknown_0x1884;
    ptmfHolder ptmfHolder_0x188C; //vtable = 0x808BECC0 function = 8063a1a4 on itself
    ptmfHolder ptmfHolder_0x18A0; //vtable = 0x808BECC0 function = 8063a2a4 on itself
    ptmfHolder ptmfHolder_0x18B4; //vtable = 0x808BECa8 function = 8063a3a0 on itself
    ptmfHolder ptmfHolder_0x18C8; //vtable = 0x808BECa8 function = 8063a3c0 on itself
    ptmfHolder ptmfHolder_0x18DC; //vtable = 0x808BECa8 function = 8063a3e0 on itself
    ptmfHolder ptmfHolder_0x18F0; //vtable = 0x808BECa8 function = 8063a400 on itself    
    ptmfHolder ptmfHolder_0x1904; //vtable = 0x808BEC90 function = 8063a444 on itself
    GhostList *ghostList; //from screen 0xA7
    u32 page;
    u32 unknown_0x1920;
}; //total size 0x1924