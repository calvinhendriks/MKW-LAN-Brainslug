#include <Kamek/kamek.hpp>
#include <egg/egg.hpp>
#include <System/system.hpp>
#include <UI/menudata.hpp>
#include <UI/Screen/SpecificScreens/GhostManager.hpp>
#include <UI/Screen/SpecificScreens/GhostSelect.hpp>

#ifdef GHOSTLOADER

void* LoadRKG(char *path, void *buffer, EGG::Heap *heap, u32 allocDirection, u32 offset, u32 r8, u32 *r9){
    char *occurrence = strstr(path, "ghost");
    s32 fd = -1;
    if(occurrence != NULL){
        u32 ghostType;
        u32 trackId;
        sscanf(occurrence,"ghost%*d/ghost%d_comp_%d.rkg", &ghostType, &trackId);
        if(ghostType == 1) trackId += 0x20;
        char nandPath[0x30];
        snprintf(nandPath, 0x30, "/Ghosts/%02d.rkg", trackId);
        fd = ISFSOpen(nandPath, 1);
        if (fd >= 0){
            ISFSRead(fd, buffer, 0x2800);
            ISFSClose(fd);
        }
    }
    if (fd < 0 ) EGG::LoadToMainRam(path, buffer, heap, allocDirection, offset, r8, r9);
    return buffer;
}

void LoadCustomStaffGhost (SystemManager *systemManager, char *ghostPath, void *heap, u32 allocDirection, u32 r7, u32 *buffer){
    Scene *scene =  menuData->curScene;
    GhostSelectScreen *screen = (GhostSelectScreen*) scene->screens[SELECT_GHOST2];
    GhostList *list = screen->ghostList;
    u32 page = screen->page;
    GhostFile *ghostChosen = list->entries[page].file;

    GhostManagerScreen *ghostManager = (GhostManagerScreen*) scene->screens[GHOST_LIST_MANAGER];
    GhostFile *easyStaffGhostsFiles = ghostManager->easyStaffGhostsGroup->files[0];
    GhostFile *expertStaffGhostsFiles = ghostManager->expertStaffGhostsGroup->files[0];

    u32 arrayPosition = ghostChosen - easyStaffGhostsFiles;
    u32 ghostType = 0x1;
    if (arrayPosition > 31){
        arrayPosition = ghostChosen - expertStaffGhostsFiles;
        ghostType = 0x2;
    }
    char path[0x80];
    snprintf(path, 0x80, "/Race/TimeAttack/ghost%1d/ghost%1d_comp_%02d.rkg", ghostType, ghostType, arrayPosition);
    systemManager->RipFromDiscAsync(path, 0, 1, 0, buffer);
    return;
}
kmCall(0x8000b5ac, &LoadRKG);
kmCall(0x8054284c, &LoadCustomStaffGhost);
kmWrite32(0x805E237C, 0x38600002); //easy and experts are displayed no matter what
kmWrite32(0x805E2B0C, 0x38000000); //remove nintendo "flag"

#endif