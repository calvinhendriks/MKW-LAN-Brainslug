#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>

class VotingScreen : public Screen { //0x91
public:
    VotingScreen(); //8064a3f4 vtable 0x808bfd0c
    virtual ~VotingScreen(); //0x8064a4e0
    ptmfHolder disconnectHandler; //purely based on the previous screen 808bfd70 8064ae6c
    ScreenActionController screenActionController; 
    CtrlMenuPageTitleText ctrlMenuBackButton;
    CtrlMenuInstructionText ctrlMenuBottomMessage;
    PushButton pushButton; //0x564
    LayoutUIControl vrScreenElements[12];
    u32 unknown_0x1928;
}; //total size 0x192c