#pragma once
#include <Kamek/kamek.hpp>

typedef struct ItemOBJProperties{
    UnkType* unknown_0x0;
    u32 limit;
    u32 competitionLimit;
    u32 capacity;
    u32 capacity2;
    u8 unknown_0x14[0x30-0x14];
    float unknown_0x30[9];
    u8 unknown_0x54[0x59-0x54];
    bool unknown_0x59[2];
    u8 unknown_0x5b[0x6c-0x5b];
    float unknown_0x6c;
    bool unknown_0x70;
    u8 unknown_0x71[0x74-0x71];
}; // Total size 0x74

void CopyItemOBJPropertiesFromRelToTable();
extern ItemOBJProperties itemObjProperties[15];

extern float greenShellSpeed;
extern float redShellInitialSpeed;
extern float redShellSpeed;
extern float blueShellSpeed;
extern float blueShellMinimumDiveDistance; //big because it's squared
extern float blueShellHomingSpeed;