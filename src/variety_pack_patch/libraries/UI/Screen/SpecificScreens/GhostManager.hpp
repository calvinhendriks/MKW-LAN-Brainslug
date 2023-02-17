#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <UI/Screen/SpecificScreens/SharedStructs.hpp>

typedef enum GhostManagerScreenState{
    IDLE,
    SAVED_GHOST_RACE_FROM_MENU = 0x3,
    SAVED_GHOST_REPLAY = 0x6,
    STAFF_GHOST_RACE_FROM_MENU = 0x9,
    STAFF_GHOST_REPLAY = 0xc
};

class GhostFile;
class GhostManagerScreen;
struct GhostListEntry{
    GhostFile *file;
    u32 licenseId;
    u32 index;
    bool isNew;
    u8 unknown_0xD[3];
}; //total size 0x10

struct GhostList{
    GhostListEntry entries[38];
    u32 count;
    GhostManagerScreen *ghostManagerScreen;
}; //total size 0x268

class GhostFile {
public:
    bool headerIsValid;
    u8 unknown_0x1;
    u16 userData[11]; //emulating wide chars
    u8 miiData[76];
    u8 lapCount;
    u8 unknown_0x65[3];
    Timer lapTimes[5];
    Timer finishTime;
    CharacterId characterId;
    VehicleId vehicleId;
    CourseId courseId;
    ControllerId controllerId;
    u8 year;
    u8 month;
    u8 day;
    u8 unknown_0xC3;
    GhostType type;
    bool isDriftAuto;
    u8 unknown_0xc9[3];
    u32 location;
    u32 inputSize;
    void *inputs;
}; //total size 0xd8

class GhostGroup{
public:
    GhostGroup(); //0x8051ce94 vtable 808b2d38
    virtual void func_vtable();
    u16 count;
    u8 unknown_0x6[2];
    u32 ghostType;  //saved 0, downloaded 1, easy 2, expert 3, ghost race 4, competition 5
    GhostFile *files[32];
    u32 unknown;
}; //total size 0x14

class GhostManagerScreen : public Screen {
public:
    GhostManagerScreen(); //805e0c38 vtable 0x808b9258
    virtual ~GhostManagerScreen(); //0x805e0cb
    InputThing inputThing;
    GhostGroup *savedGhostGroups[4];
    GhostGroup *downloadedGhostsGroup;
    GhostGroup *easyStaffGhostsGroup;
    GhostGroup *expertStaffGhostsGroup;
    GhostGroup *unknown_group;
    bool isNew[0x20]; //for each track
    GhostManagerScreenState state;
    u32 unknown_0x98;
    GhostList list;
    RKG *rkgBuffer;
    RKG rkg2;
};//total size 0x2b0c