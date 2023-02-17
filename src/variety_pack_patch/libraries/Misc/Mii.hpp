#pragma once

#include <Kamek/kamek.hpp>

class Mii{ //has stuff like sex, type etc.. most likely
    Mii(u32 r4); //80525f88
    virtual void func_vtable(); //808b3148
    u32 r4;
    u8 unknown_0x8[0x12-0x8];
    wchar_t name[10]; //0x12 only used for other miis?
    u8 unknown_0x26[0x46-0x26];
    wchar_t name2[10]; //0x46
    u8 unknown_0x5A[0x68-0x5A];
    wchar_t name3[10]; //0x68
    u8 unknown_0x7C[0xB8-0x7C];
}; //total size 0xB8

class MiiGroup{ 
    MiiGroup();//805f9e78 vtable 808b9f68
    virtual void func_vtable();
    Mii **mii; //pointer to the array of the miis loader
    u8 unknown_0x8[0x98-0x8];
}; //Total Size 0x98