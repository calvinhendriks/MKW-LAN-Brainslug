#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>

class VSSettingScreen : public InteractableScreen{
public:
    VSSettingScreen(); //0x806284c8
    virtual ~VSSettingScreen(); //80853b10 vtable 0x808da3c8
    ScreenActionController screenActionController; //0x430
    u32 controlCount; //0x654
    PtmfHolder_1A<VSSettingScreen, void, PushButton*> onNextScreenButtonPress; //0x658 vtable 808bd18c 80853654
    PtmfHolder_1A<VSSettingScreen, void, PushButton*> onNextScreenButtonSelect; //0x66C vtable 808bd18c virtual off 0x64
    PtmfHolder_0A<VSSettingScreen, void> onNextScreenButtonDeselect; //0x680 vtable 808bd18c 808536b0
    PtmfHolder_0A<VSSettingScreen, void> onBackPress; //0x694 vtable 808bd18c 808536b4
    PtmfHolder_0A<VSSettingScreen, void> onStartPress; //0x6A8 vtable 808bd18c virtual off 0x7C
    u32 localPlayerCount;
    u32 unknown_0x6C0;
    RadioButtonControl radioButtonControls[5]; //0x6c4
    UpDownControl upDownControl[1]; //0x13BC
    TextUpDownValueControl textUpDownValueControl[1]; //0x1984
    RadioButtonChangeHandler *onRadioButtonChangeHandler; //0x1DF8
    RadioButtonSelectHandler *onRadioButtonSelectHandler; 
    UpDownChangeHandler *upDownChangeHandler; //0x1E00 //when you scroll
    UpDownClickHandler *upDownClickHandler; //0x1E04
    UpDownElementSelectHandler *upDownElementSelectHandler; //0x1E08
    UpDownDisplayedText *unkTextClassSelectHandler; //when you scroll
}; //0x1E10