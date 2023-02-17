#pragma once
#include <Kamek/kamek.hpp>

enum VPGamemode{
    NOMODE = 0x0,
    BSS = 0x1,
    BBB = 0x2,
    CHAOTIC = 0x3
};

struct Settings{
public:
    u8 mode;
    bool finalLapSpeedup;
    bool silentController;
    bool miiHeads;
};

extern Settings settings;