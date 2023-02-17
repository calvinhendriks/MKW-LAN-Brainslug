#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>

class GhostReplayPauseScreen : public PauseScreen{
public:
    GhostReplayPauseScreen(); //80624d7c 808bdb08
    virtual ~GhostReplayPauseScreen(); //80632f74
    u32 unknown_0x340;
}; //total size 0x344