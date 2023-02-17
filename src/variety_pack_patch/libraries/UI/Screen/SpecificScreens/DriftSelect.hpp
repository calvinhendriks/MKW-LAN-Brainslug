#pragma once

#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>

class DriftSelectScreen: public InteractableScreen { //0x6D
public:
    DriftSelectScreen(); //806273cc
    virtual ~DriftSelectScreen(); //vtable 808d9db0
    virtual void onInit(); //8084ddfc might be for 6c
    virtual void Load(); //8084e13c
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd15c function = 8084e388 on itself (onClick)
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd15c offset = 0x64 call is virtual on itself (onSelect)
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd15c function = 8084e6f4 on itself (onDeSelect, just a blr)
    ptmfHolder onBackPressHandler; //vtable = 0x808BD1150 function = 8084e6f8 (onBackPress)
    ptmfHolder handler; //vtable = 0x808bd150 offset = 0x7c call is virtual on itself Handler
    u32 playerCount; //0x6BC
    u32 unknown_0x6C0;
    UITimer *timer; //0x6C4
    MenuType menuId;
}; //Total Size 0x6CC