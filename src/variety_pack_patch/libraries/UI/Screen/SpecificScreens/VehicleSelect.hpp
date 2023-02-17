#pragma once

#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>


class CtrlMenuMachineGraph : public LayoutUIControl {
public:
    CtrlMenuMachineGraph();//805f39bc vtable 808d3420
    virtual ~CtrlMenuMachineGraph(); //80627374
    UnkType **unk_array_0x174; //pointer to an array of an unknown class inherited from layoutUIControl, of size 0x17C 807e7d88 ctor
    UnkType **unk_array_0x178; //pointer to an array of pointers related to machinePara.bin getting dumped
    UnkType **unk_array_0x17c; //same but probably for vehicles and the other for characters?
    u32 unknown_0x180; //init at 0x7
}; //total size 0x184

class VehicleSelectScreen: public InteractableScreen { //0x6C
public:
    VehicleSelectScreen(); //80627060
    virtual ~VehicleSelectScreen(); //vtable 808d9880
    virtual void onInit(); //80844d68
    virtual void Load(); //80845510
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder onClick; //vtable = 0x808bd1dc function = 80846c1c on itself (onClick)
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd1dc offset = 0x64 call is virtual on itself (onSelect)
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd1dc function = 80846fbc on itself (onDeSelect, just a blr)
    ptmfHolder onBackPressHandler; //vtable = 0x808BD1b0 function = 80846fc0 (onBackPress)
    ptmfHolder handler; //vtable = 0x808bd1b0 offset = 0x7c call is virtual on itself Handler (onStartPress?)
    u32 unknown_0x6BC[2]; //constructed at 1
    u32 unknwown_0x6C4; //init at -1
    bool unknown_0x6C8[0x6EC-0x6C8]; //result of 8081cfb4, always 1 on construct
    u32 unknwon_0x6EC; //init at 2
    UITimer *timer;
    u32 buttonId;
    VehicleModelControl vehicleModel;
    CtrlMenuMachineGraph _0x87c; //808d3420 inherited from LayoutUIControl, 
    float unknown_0xA00;
    float unknown_0xA04;
    u32 unlockedVehiclesCount; //if 3, will display only 3 vehicles, the rest will be ?
   
}; //Total Size 0xA0C

class VehicleSelectBattleScreen : public InteractableScreen { //0x78
public:
    VehicleSelectBattleScreen(); //80628e3c vtable 0x808D8F40
    virtual ~VehicleSelectBattleScreen(); //8083b014
    ScreenActionController screenActionController;
    UnkType unknown_0x654;
    ptmfHolder ptmfHolder_0x658; //vtable = 0x808bd114 function = 8083A918 on itself (onClick)
    ptmfHolder ptmfHolder_0x66C; //vtable = 0x808bd114 offset = 0x64 call is virtual on itself (onSelect)
    ptmfHolder ptmfHolder_0x680; //vtable = 0x808bd114 function = 8083AB78 on itself (onDeSelect, just a blr)
    ptmfHolder onBackPressHandler; //vtable = 0x808BD108 function = 8083AB80 (onBackPress)
    ptmfHolder handler; //vtable = 0x808BD108 offset = 0x7c call is virtual on itself Handler (onStartPress?)
    u32 unknown_0x6BC[2]; //constructed at 1
    u32 unknwown_0x6C4; //init at -1
    UITimer *timer;
    u32 unknown_0x6CC;
    VehicleModelControl vehicleModel; //0x6D0
    CharaName name; //0x854
    CtrlMenuMachineGraph  ctrlMenuMachineGraph;
}; // Total Size 0xb50