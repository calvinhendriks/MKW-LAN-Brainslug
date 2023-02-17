#include <common.hpp>
#include <mkw2/settings.hpp>

RaceFrameHook *RaceFrameHook::sHooks = NULL;
int bombTimer = 0x4b0;

//Login Region
kmWrite32(0x80384fd4, 0x30303837);

void ReduceBombTimer(){
    if (settings.bombTimer == 0x1 && bombTimer > 0){
        bombTimer--;
    }
}

int CheckBombTimer(int chosenItem){
    if (settings.bombTimer == 0x1 && chosenItem == BOBOMB && bombTimer != 0){
        return MUSHROOM;
    }
    return chosenItem;
}

static RaceFrameHook reduceBombTimerHook(ReduceBombTimer);
kmBranch(0x8053369c, RaceFrameHook::exec);
kmBranch(0x807bb8cc, &CheckBombTimer);

void ChangeItemOBJProperties(int *billTable, ItemOBJProperties *billProperties){
    CopyItemOBJPropertiesFromRelToTable(billTable, billProperties);

    if (settings.shockLimit == 0x1){
    ItemOBJProperties *table = itemObjProperties;

    table[OBJ_LIGHTNING].limit = 0x2;
    }
}

kmCall(0x80790c04, &ChangeItemOBJProperties);

void LaunchRiivolutionButton(MenuData *menuData){
    if (menuData->nextMenuId == 0x7A){
        int result = ISFS_Open("/title/00010001/52494956/content/title.tmd\0", 1);
        if (result > -1){
            ISFS_Close(result);
            _OSLaunchTitle(0x00010001, 0x52494956);
            return;
        }
        result = ISFS_Open("/title/00010001/4c554c5a/content/title.tmd\0", 1); // If Riivolution can't be found try HBC
        if (result > -1){
            ISFS_Close(result);
            _OSLaunchTitle(0x00010001, 0x4c554c5a);
            return;
        }
        result = ISFS_Open("/title/00010001/48424330/content/title.tmd\0", 1); // If HBC can't be found try OHBC
        if (result > -1){
            ISFS_Close(result);
            _OSLaunchTitle(0x00010001, 0x48424330);
            return;
        }
        _OSLaunchTitle(0x1, 0x2); // Launch Wii Menu if channel isn't found
    }
    else{
        MenuData_loadNextMenu(menuData);
    }
}

kmCall(0x80553a60, &LaunchRiivolutionButton);

// No Team Invincibility
kmWrite32(0x807bd2bc, 0x38000000);
kmWrite32(0x80572618, 0x38000000);

// Faster Voting Roulette
kmWrite32(0x80643c2c, 0x60000000);

/* Host Always Wins
kmCallDefAsm(0x80661E20){
    nofralloc

    li r4, 0
    stb r4, 0x3E(r31)

    blr
}*/

// Faster Menu Navigation
kmWrite32(0x8038900C, 0x00000000);
kmWrite32(0x80635670, 0x38000000);
kmWrite32(0x80896830, 0x00000000);