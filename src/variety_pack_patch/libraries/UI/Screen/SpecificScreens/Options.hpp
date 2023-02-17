#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>

class OptionsScreen : public Screen{
public:
    OptionsScreen(); //805fd518
    virtual ~OptionsScreen(); //805fd638 vtable 808ba3ec
    virtual int getNextScreen(); //80601060
    virtual void OnInit(); //805fd6e4
    virtual void ClearInstance(); //805fd8e4
    virtual void OnLoad(); //805fd8e8
    virtual int GetStaticInstanceAddr(); //80601068 returns809c1ce8

    void HandleClick(PushButton *pushButton, u32 r5); //

    PtmfHolder_2A<OptionsScreen, void, PushButton*, u32> onClick; //0x44 vtable 808ba45c 805fd90c
    ptmfHolder onBackPress; //0x58 vtable 808ba450 805fda80
    ScreenActionController screenActionController; //0x6C
    CtrlMenuPageTitleText ctrlMenuPageTitleText; //0x290
    PushButton gcnRumble; //0x404
    PushButton nintendoWiFi; //0x658
    PushButton AddMarioKartChannel; //0x8ac
    CtrlMenuBackButton backButton; //0xb00 ends at d64
    ScreenType nextScreenId; //when you press a button


}; //total size 0xd68
