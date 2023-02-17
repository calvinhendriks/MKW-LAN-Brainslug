#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/SpecificScreens/SharedStructs.hpp>
#include <Misc/Mii.hpp>

typedef enum CountDownScreenStatus{
    STATUS_WAITING = 0x2,
    STATUS_VR_SCREEN,
    STATUS_CUP_SELECT,
    STATUS_VOTES_SCREEN,
    STATUS_DISCONNECTED,
    STATUS_DISCONNECT_MSG = 0x8
};

class CountDownTimerControl : public LayoutUIControl{
public:
    CountDownTimerControl(); //0x805C3CD4
    virtual ~CountDownTimerControl(); //805c3d18 808b7dc0
    virtual void OnUpdate(); //805c407c
    virtual void BeforeChildUpdate(); //80650218
    virtual void AfterChildUpdate(); //80650274
    virtual void func_vtable(); //vtable 0x808b7dc0

    UITimer *timer;
    bool unknown_0x178;
    u8 unknown_0x179[0x17C-0x179];
}; //total size 0x17C

class CountDownScreen : public Screen { //0x90
public:
    CountDownScreen(); //8064fbdc vtable 0x808c069c
    virtual ~CountDownScreen(); //8064fc70
    virtual void OnResume(); //806507a0

    ptmfHolder disconnectHandler;
    InputThing inputThing;
    CountDownScreenStatus status; //0x68
    UITimer timer; //0x6C
    CountDownTimerControl TimerElement; //0x78
    PlayerInfo infos[12]; //large loop at 0x80651980, one per player it seems
    u32 unknown_0x284;
    u32 engineClass;
    u32 battleType; //init at 2 8064fe14
    MiiGroup miiGroup; //0x290
}; //total size 0x328