#include <Kamek/kamek.hpp>
#include <UI/menudata.hpp>

/*
this class handles in race BRSAR sounds that are not:
-item based
-character based
-vehicle based

so stuff like the position tracker, the lap transition sound, the roulette spinning etc...
*/

class RaceRSARSoundHandler{ //inherited from something else
public:
    RaceRSARSoundHandler(); //inlined 80713f14
    virtual void func_vtable(); //vtable 808c9088 parent = 808c90e8
    bool PlayBRSARSound(u32 soundId, u32 r5);
    u8 unknown_0x4[4];
    u32 state; //01 before load, 02 after, 0x3 after pressing next race -> setting it to 3 midrace mutes most BRSAR sounds
    u8 unknown_0xC; //checks if it's 1 after pressing next race
    u8 unknown_0xD[3]; //likely padding
    MenuType menuId; //0x10
    bool isPaused;
    bool isRouletteSoundPlaying; //alternates 0/1 within the same frame, but only when the roulette sound is playing
    u8 unknown_0x16[0x1C-0x16]; //probably for other types of sounds
}; //total size 0x1C


extern RaceRSARSoundHandler *raceRSARSoundHandler; //809c2850

extern u32 currentlyPlayingSoundID[0x10]; //809c2840