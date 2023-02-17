#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>

struct PlayerInfo{
    u8 aid; //shared by players on the same console
    u8 hudSlotid; //0 for P1, 1 for P2 on the same console etc....
    u8 unknown_0x2[2]; //never stored likely padding
    u32 team; //0x2 if no team (depending on the menu), 0x0 blue, 0x1 red 0x1F8
    u16 randomThing; //806519c4, no idea, gets the current license then does a bunch of operations 0x1FC
    u16 randomThing2; //80651a20, very similar, but uses a different address to start the operations
};//total size0xC

class InputThing{
public:
    InputThing(); //805eeb68 0x808b9a98 vtable is full of functions that perfom slw/and, likely to check an input
    virtual void func_vtable();
    virtual void OnInit(); //8064fcfc
    u32 playerFlags;
    u8 unknown_0x8[0xC-0x8];
    bool unknown_0xC;
    bool isMultiplayer;
    u8 unknown_0xE[0x10-0xE];
};//total size 0x10

struct RKG{
    u8 unknown[0x2800];
};//total size 0x2800