/*
Racedata is the class that holds the information to set up a race, such as the gamemode and the characters each player chose
Contributors:
    Seeky (main documentation)
    TheLordScruffy (main documentation)
    WhatIsLoaf (ghost player type)
    riidefi (ParameterFile)
    CLF78 (local player count)
References:
    http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
    https://github.com/riidefi/mkw/blob/master/source/game/host_system/ParameterFile.hpp
*/

#pragma once
#include <common.hpp>
#include <Kamek/kamek.hpp>
#include <Misc/Mii.hpp>

typedef enum PlayerType{
    PLAYER_REAL_LOCAL,
    PLAYER_CPU,
    PLAYER_UNKNOWN2,
    PLAYER_GHOST,
    PLAYER_REAL_ONLINE,
    PLAYER_NONE
};

typedef enum Team{
    TEAM_RED,
    TEAM_BLUE
};

typedef enum BattleType{
    BATTLE_BALLOON,
    BATTLE_COIN
};

typedef enum CpuMode{
    CPU_EASY,
    CPU_NORMAL,
    CPU_HARD,
    CPU_NONE
};

typedef enum GameMode{
    MODE_GRAND_PRIX,
    MODE_VS_RACE,
    MODE_TIME_TRIAL,
    MODE_BATTLE,
    MODE_MISSION_TOURNAMENT,
    MODE_GHOST_RACE,
    MODE_6,
    MODE_PRIVATE_VS,
    MODE_PUBLIC_VS,
    MODE_PUBLIC_BATTLE,
    MODE_PRIVATE_BATTLE,
    MODE_AWARD,
    MODE_CREDITS
};

typedef enum GameType{
    TIME_ATTACK = 0x0,
    CPU_RACE = 0x5,
    ONLINE_SPECTATOR = 0x6
};

typedef enum EngineClass{
    CC_50,
    CC_100,
    CC_150,
    CC_BATTLE // Note: Battle mode actually sets it to 50cc (which is ignored by code), but setting it to this in other modes results in Battle CC
};

typedef enum ItemMode{
    ITEMS_BALANCED,
    ITEMS_FRANTIC,
    ITEMS_STRATEGIC,
    ITEMS_NONE
};

typedef struct RacedataSettings{
public:
    CourseId courseId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Courses
    EngineClass engineClass;
    GameMode gamemode;
    GameType gametype;
    BattleType battleType;
    CpuMode cpuMode;
    ItemMode itemMode;
    u8 hudPlayerIds[4];
    u32 cupId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Cups
    u8 raceNumber; // resets at 100 for some reason
    u8 lapCount;
    u8 unknown_0x26;
    u8 unknown_0x27;
    u32 modeFlags; // bit flags:
    /*
        2 is teams enabled
        1 is mirror mode
        Others unknown
    */
    u32 unknown_0x2c;
    u32 unknown_0x30;
}; // Total size 0x34

class RacedataPlayer {
public:
    RacedataPlayer(); // 8052d96c
    u32 computeGpRank(); // 8052daf0
    
    // vtable 808b3294
    virtual ~RacedataPlayer(); // 8052DC68
    u8 unknown_0x4;
    s8 localPlayerNum;
    s8 realControllerId; // id of the controller at the console for this player, -1 if not controlled by one
    u8 unknown_0x7; // possibly padding
    VehicleId vehicleId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Vehicles
    CharacterId characterId; // http://wiki.tockdom.com/wiki/List_of_Identifiers#Characters
    PlayerType playerType; //0x10
    Mii mii; //0x14
    Team team;
    u8 unknown_0xd0[8];
    u16 previousScore;
    u16 score;
    u8 unknown_0xdc[2];
    s16 gpRankScore;
    u8 unknown_0xe0;
    u8 prevFinishPos;
    u8 unknown_0xe2[6];
    s16 rating; // vr or br, depending on mode
    u8 unknown_0xea[6];
}; // Total size 0xf0

class RacedataScenario {
public:
    RacedataScenario(void * ghost); // 8052dbc8, never used - racedata's constructor does it inline

    // vtable 808b3288
    virtual ~RacedataScenario();
    u8 playerCount;
    u8 unknown_0x5;
    u8 localPlayerCount;
    u8 unknown_0x7;
    RacedataPlayer players[12];
    RacedataSettings settings;
    u8 mission[0x70]; // 0x70 struct, see http://wiki.tockdom.com/wiki/Mission_Mode#mission_single.kmt
    void * ghost; // Scenario 0 points to the one you race, 1 points to one I'm not sure about, 2 points to null
}; // Total size 0xbf0

class RacedataMain {
public:
  // Always constructed inline, functions seem to always be members of Racedata rather than specifically RacedataMain

  //vtable 808b3260 (empty)  
  virtual void unknown_vtable();
  RacedataScenario scenarios[3]; // 0 is in race, 1 is in menu, not sure what 2 is
  u8 ghosts[2*0x2800]; // 0x2800 size each, 0 is the one you're racing, not sure what 1 is, see http://wiki.tockdom.com/wiki/RKG_(File_Format)
};  // Total size 0x73d4

// ParameterFile size is 0x1c, Racedata's is /boot/menuset.prm
class Racedata {
public: // vtable override 808b3268
    static Racedata * sInstance; // 0x809bd728
    static Racedata * getStaticInstance(); // 8052fe58
    static void destroyStaticInstance(); // 8052ffe8

    virtual ~Racedata(); // 80530038
    virtual int FUN_80009ddc();
    virtual int FUN_80532078(); // just a blr
    virtual int FUN_80532074(); // just a blr
    virtual int FUN_80532070(); // just a blr
    // Always constructed inline
    
    u8 unknown_0x4[0x1c - 0x4];
  
    RacedataMain main;
};  // Total size 0x73f0

extern Racedata *raceData;