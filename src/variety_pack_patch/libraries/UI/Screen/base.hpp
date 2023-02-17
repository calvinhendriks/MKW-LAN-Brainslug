/*
Credits:
kHacker35000vr and the Sanbo team (dolphin map, ScreenText)
stebler (names for some of the classes)
Melg
*/

#pragma once
#include <Kamek/kamek.hpp>
#include <nw4r/lyt/lyt.hpp>
#include <Race/racedata.hpp>
#include <Race/raceinfo.hpp>
#include <UI/menudata.hpp>
#include <UI/Ctrl/Ctrl.hpp>
#include <UI/Ctrl/Action.hpp>

class Screen;

struct UITimer{
    float value;
    bool isActive;
    u8 unknown_0x5[3];
    u32 seconds;
};//total size 0xC

class Screen {
public:
    Screen(); //8060197c, vtable 0x808ba5c0
    virtual ~Screen(); //8
    virtual int getPage(); //returns "(unknown page)" c
    virtual int getNextScreen(); //returns -1 10
    virtual int func_0x14(); //returns 0 14
    virtual int func_0x18(); //returns 18
    virtual void func_0x1C(); //1c
    virtual void func_0x20(); //20
    virtual void AddScreenLayer(ScreenType id, u32 r5); //806025b0 24
    virtual void OnInit(); //just a blr 28
    virtual void ClearInstance(); //just a blr 2C
    virtual void OnLoad(); //just a blr   30
    virtual void OnUnload(); //just a blr
    virtual void OnActivate(); //just a blr
    virtual void OnFocus(); //just a blr
    virtual void OnDefocus(); //just a blr 40
    virtual void func_0x44(); //just a blr
    virtual void BeforeChildUpdate(); //just a blr
    virtual void AfterChildUpdate(); //just a blr
    virtual void OnUpdate(); //just a blr 50
    virtual void OnResume(); //just a blr
    virtual void func_0x58(); //just a blr
    virtual void func_0x5C(); //just a blr
    virtual int GetStaticInstanceAddr(); //returns 809C1d10
    void InitControlGroup(u32 controlCount); //inits the sub class and sets the count to a specified value
    void AddControl(u32 arrayPosition, LayoutUIControl *control, u32 r6); //Adds a control to the screnChild control array at a specified position
    void Setup(ScreenType screenId);
    void SetActionController(ScreenActionController *controller); //0x80602474
    void EndStateAnimate(float animLength, u32 animId);
    void SetTransitionSound(u32 id, u32 id2); //0x80602d20
    u32 screenId;
    UnkType unknown_0x8[3];
    float unknown_0x14[2];
    UnkType unknown_0x1C[2];
    ControlGroup controlGroup;
    ScreenActionController *screenActionController;
    UnkType unknown_0x3C[2];
}; //Total Size 0x44

