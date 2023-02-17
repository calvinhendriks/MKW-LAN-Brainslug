#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <UI/Screen/SpecificScreens/SharedStructs.hpp>

class TTInterface: public RaceScreen { //just an example, ID 0xd
    TTInterface(){//806247cc
        u32 gamemode = *(&raceData->main.scenarios[0].settings.gamemode);
        nextScreenId = 0x21;
        if(gamemode == MODE_TIME_TRIAL || gamemode ==  MODE_GHOST_RACE){
            nextScreenId = 0x2D;
        }
    }; 
    virtual void func_vtable(); //0x808be478
};