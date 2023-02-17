#pragma once
#include <Kamek/kamek.hpp>

class Rknetcontroller{
public:
    u8 unknown_0x0[0x28 - 0x0];
    int connectionState;
    u8 unknown_0x2c[0x29c8 - 0x2c];
};

extern Rknetcontroller *rkNetController;