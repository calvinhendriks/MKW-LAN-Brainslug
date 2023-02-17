#pragma once

#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>

class CtrlMenuCharacterSelect: public LayoutUIControl{
public:
    CtrlMenuCharacterSelect(); //vtable 808d3038
    virtual ~CtrlMenuCharacterSelect(); //80627008
    CharacterId selectedCharacter;
    u8 unknown_0x178[0x184-0x178];
    UITimer *timer; //807e25d4
    u32 playerCount;
    bool unknown_0x18C; //result of 8081d020, loop at 0x807e2610
    bool unknown_0x18D; //result of 8081d020
    bool unknown_0x18E; //result of 8081d020
    bool unknown_0x18F; //result of 8081d020
    bool unknown_0x190; //result of 8081d020
    bool unknown_0x191; //result of 8081d020
    bool unknown_0x192; //result of 8081d020
    bool unknown_0x193; //result of 8081d020
    bool unknown_0x194; //result of 8081d020
    bool unknown_0x195; //result of 8081d020
    bool unknown_0x196; //result of 8081d020
    bool unknown_0x197; //result of 8081d020
    bool unknown_0x198; //result of 8081d020
    bool unknown_0x199; //result of 8081d020
    bool unknown_0x19A; //result of 8081d020
    bool unknown_0x19B; //result of 8081d020
    bool unknown_0x19c; //result of 8081d020
    bool unknown_0x19D; //result of 8081d020
    bool unknown_0x19F; //result of 8081d020
    bool unknown_0x1A0; //result of 8081d020
    bool unknown_0x1a3; //result of 8081d020
    bool unknown_0x1A4; //same but outside of the loop
    bool unknown_0x1A5; //same but outside of the loop
    u8 unknown_0x1A6[2];
    u32 unknown_0x1a8; //init at 4
    u32 unlockedCharactersCount; // 0x1a if all unlocked 0x1AC
    UnkType *array_0x1B0; //seems to be a class inherited from PushButton ctor 807e2808 vtable 808D3074
    u32 unknown_0x1B4; 
    ptmfHolder ptmfHolder_0x1B8; //vtable = 0x808bd2c4 function = 807e35fc (onBtnClick)
    ptmfHolder ptmfHolder_0x1CC; //vtable = 0x808bd2c4 function = 807e36f4 (onSelect)
    ptmfHolder ptmfHolder_0x1E0; //vtable = 0x808bd2c4 function = 807e37d4 (onDeselect)
    ptmfHolder ptmfHolder_0x1F4; //vtable = 0x808bd2c4 function = 807e3880 (onMiiBtnClick)   
    ptmfHolder ptmfHolder_0x208; //vtable = 0x808bd2c4 function = 807e39cc (onMiiSelect)  
    ptmfHolder ptmfHolder_0x21C; //vtable = 0x808bd2c4 function = 807e3aac (onMiiDeSelect)
}; //total size 0x230

class CharacterSelectScreen: public InteractableScreen { //0x6B
public:
    CharacterSelectScreen(); //80626c10
    virtual ~CharacterSelectScreen(); //vtable 808d92c0 
    virtual void onInit(); //8083d55c
    virtual void Load(); //8083da78
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd1d4 function = 8083e740 on itself
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd1d4 offset = 0x64 call is virtual on itself
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd1d4 function = 8083E924 on itself
    ptmfHolder onBackPressHandler; //vtable = 0x808BD1C8 function = 8083E928 (onBackPress)
    ptmfHolder handler; //vtable = 0x808bd1c8 offset = 0x7c call is virtual on itself Handler
    u32 unknown_0x6BC[2]; //constructed at 1
    CtrlMenuCharacterSelect ctrlMenuCharSelect;
    Mii *localPlayerMii;
    u8 unknwon_0x8F8[0x904-0x8f8];
    u32 playerCount; //0x904
    u32 unknwon_0x908;
    UITimer *timer; //0x90c
    CharaName *names;
    DriverModelControl *names2;

}; //Total Size 0x918