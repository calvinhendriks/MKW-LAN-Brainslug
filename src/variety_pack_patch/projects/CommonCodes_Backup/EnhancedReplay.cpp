#include <UI/menudata.hpp>
#include <Race/racedata.hpp>
#include <Race/kmp.hpp>
#include <Race/playerholder.hpp>
#include <Race/Item/itemholder.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <UI/Screen/SpecificScreens/GhostReplayPause.hpp>
#include <Model/model.hpp>
#include <common.hpp>

#ifdef ENHANCEDREPLAY

kmWrite32(0x80630450, 0x3880000d);  //To use the correct onInit
kmWrite32(0x80630474, 0x3880000d);
kmWrite32(0x80630498, 0x3880000d);  
kmWrite32(0x80631ce4, 0x2c030035);  //Music
kmWrite32(0x806320ac, 0x2c030035);
kmWrite32(0x80711444, 0x3803ffcb);
kmWrite32(0x8071e4a0, 0x38600000);  //Lakitu
kmWrite32(0x807f1590, 0x60000000);  //Player Name
kmWrite32(0x80856e64, 0x2c040035); //Removes fade at the end
kmWrite32(0x80857540, 0x2c000035); //Fixes instant FINISH flash at the end
kmWrite32(0x80859ed4, 0x48000048); //no immediate unload if ghost

void CreateTTInterface(Scene *scene, ScreenType id){
    scene->CreateScreen(TIME_TRIAL_INTERFACE);
    scene->CreateScreen(SPLITS_AFTER_TT);
}
kmCall(0x8062ccd4, &CreateTTInterface);
kmCall(0x8062cc5c, &CreateTTInterface);
kmCall(0x8062cc98, &CreateTTInterface);

ScreenType TTSplitsNextScreen(){
    MenuType menuId = menuData->curScene->menuId;
    if (menuId == TIME_TRIAL_GAMEPLAY || menuId == GHOST_RACE_GAMEPLAY_1 || menuId == GHOST_RACE_GAMEPLAY_2) return LEADERBOARD_AFTER_TT;
    else if (menuId == GRAND_PRIX_GAMEPLAY) return GPVS_SCORE_UPDATE_SCREEN;
    else if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) return GHOST_REPLAY_PAUSE_MENU;
    return SCREEN_NONE;
}
kmBranch(0x808561dc, &TTSplitsNextScreen);

int ChangePlayerType(RacedataPlayer *player, u8 id){

    PlayerType type = raceData->main.scenarios[0].players[id].playerType;
    if (type == PLAYER_GHOST && id == 0) return 0;
    return type;
}
kmCall(0x80594444, &ChangePlayerType);
kmWrite32(0x80594434, 0x889F0010);
kmWrite32(0x80594448, 0x2c030000);
kmWrite32(0x80594450, 0x2c030001);
kmWrite32(0x80594458, 0x2c030003);

bool PatchIsLocalCheck(Player *player){
    MenuType menuId = menuData->curScene->menuId;
    if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) return false;
    return player->IsLocal();
}
kmCall(0x80783770, &PatchIsLocalCheck);

ScreenType TTPauseNextScreen(PauseScreen *screen){
    MenuType menuId = menuData->curScene->menuId;
    if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) return GHOST_REPLAY_PAUSE_MENU;
    return screen->GetPauseScreenId();
}
kmCall(0x808569e0, &TTPauseNextScreen);

void OnContinueButtonTTPauseClick(GhostReplayPauseScreen *screen, ScreenType id){
    u32 stage = raceInfo->stage;
    if (stage == 0x4) id = SPLITS_AFTER_TT; //if race is finished, repurpose the continue button
    screen->onContinuePressNextScreen = id;
    return;
}
kmCall(0x8085a1e0, &OnContinueButtonTTPauseClick);

s32 GhostSavingPatch(u32 willGhostSave){
    MenuData *menu = menuData;
    MenuType menuId = menu->curScene->menuId;
    if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) willGhostSave = -1;
    menu->menudata98->willGhostSave = willGhostSave;
    return willGhostSave;
}
kmCall(0x80855c78, &GhostSavingPatch);
kmWrite32(0x80855c80, 0x2c03ffff);
kmWrite32(0x80855c84, 0x60000000);

void FlapSavingPatch(UnkType *saveDataManagerLicense,UnkType *timer, u32 r5, CourseId id){
    MenuData *menu = menuData;
    MenuType menuId = menu->curScene->menuId;
    if(menuId < WATCH_GHOST_FROM_CHANNEL || menuId > WATCH_GHOST_FROM_MENU) StoreFlapIntoSave(saveDataManagerLicense, timer, r5, id);
    return;
}
kmCall(0x8085606C, &FlapSavingPatch);

bool WillCharCheer(Racedata *racedata){
    MenuData *menu = menuData;
    MenuType menuId = menu->curScene->menuId;
    if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <=WATCH_GHOST_FROM_MENU){
        raceScreen->timer.minutes = 0xFFFF;
        return true;
    } 
    else if(racedata->main.scenarios[0].settings.gamemode == MODE_GHOST_RACE || menu->menudata98->ghostType != 0x1) return true;
    return false;
}
kmCall(0x808570a0, &WillCharCheer);
kmWrite32(0x80857088, 0x40820018);
kmWrite32(0x808570a4, 0x2C030001);
kmWrite32(0x808570c0, 0x807cd728);

void PatchFinishRaceBMGID(LayoutUIControl *control, u32 bmgId, ScreenText *text){
    MenuType menuId = menuData->curScene->menuId;
    if(menuId >= WATCH_GHOST_FROM_CHANNEL && menuId <= WATCH_GHOST_FROM_MENU) bmgId = 0x4B5;
    control->SetMsgId(bmgId, text);
}
kmCall(0x8085728c, &PatchFinishRaceBMGID);

bool PatchOpacity(ComboIDs *comboIDs, GFX44 *gfx44, bool isGhost, u8 playerId){
    if (playerId == 0) isGhost = false;
    return ApplyTransparency(comboIDs, gfx44, isGhost, playerId);
}
kmCall(0x8058e2b8, &PatchOpacity);
kmCall(0x807c7870, &PatchOpacity);

void *PatchMiiHeadsOpacity(MiiHeadsModel *model, Mii *mii, ModelDirector *driverModel, u32 r6, u32 r7, u32 r8, u32 id){
    if (id == 0) model->isTransparent = false;
    return model->InitModel(mii, driverModel, r6, r7, r8, id);
}
kmCall(0x807dc0e8, &PatchMiiHeadsOpacity);

bool EnableCPUDrivingAfterRace(PlayerPointers *pointers){
    u8 id = pointers->getPlayerIdx();
    PlayerType type = raceData->main.scenarios[0].players[id].playerType;
    if (type == PLAYER_GHOST && id != 0) return true;
    return false;
}
kmCall(0x80732634, &EnableCPUDrivingAfterRace);

asm void PatchSoundIssues(){
    ASM(
    nofralloc;
    lwz r5, 0 (r4); //Default
    cmpwi r5, 0x32;
    blt+ end;
    li r5, 0x1f;
    end:;
    blr;
    )
}
kmCall(0x80716064, &PatchSoundIssues);

#endif