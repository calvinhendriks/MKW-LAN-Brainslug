#include <Kamek/kamek.hpp>
#include <UI/menudata.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/SpecificScreens/CharacterSelect.hpp>
#include <UI/Screen/SpecificScreens/VehicleSelect.hpp>
#include <UI/Screen/SpecificScreens/DriftSelect.hpp>
#include <UI/Screen/SpecificScreens/Voting.hpp>
#include <UI/Screen/SpecificScreens/Timer.hpp>

#ifdef CHANGECOMBO

ptmfHolder votingSTARThandler;
bool hasStartbeenPressed = false;

void OnStartPress(PushButton *pushButton){
    hasStartbeenPressed = true;
    pushButton->HandleClick(0, -1);
}

void AddChangeComboScreens(Scene *scene, ScreenType id){
    scene->CreateScreen(id);
    scene->CreateScreen(CHARACTER_SELECT);
    switch(scene->menuId){
        case(P1_WIFI_VS_VOTING):
        case(P1_WIFI_FRIEND_ROOM_VS_VOTING):
        case(P1_WIFI_FRIEND_ROOM_TEAM_VS_VOTING):
            scene->CreateScreen(VEHICLE_SELECT);
            break;
        case(P1_WIFI_BATTLE_VOTING):
        case(P1_WIFI_FRIEND_ROOM_BALLOON_VOTING):
        case(P1_WIFI_FRIEND_ROOM_COIN_VOTING):
            scene->CreateScreen(SELECT_VEHICLE_BATTLE);
            break;
    }
        scene->CreateScreen(DRIFT_SELECT);        
}

void PatchPtmfVotingScreen(Scene *scene, ScreenType id){
    scene->CreateScreen(id);
    VotingScreen *votingScreen = (VotingScreen*) scene->screens[PLAYER_LIST_VR_SCREEN];
    votingSTARThandler.vtable = (u32) &ptmfVtable;
    votingSTARThandler.subject = &votingScreen->pushButton;
    votingSTARThandler.ptmf.this_delta = 0x0;
    votingSTARThandler.ptmf.vtableOffset = -1;
    votingSTARThandler.ptmf.functionPointer = &OnStartPress;
    votingScreen->pushButton.actionHolder.actionHandlers[START_PRESS] = &votingSTARThandler;

    CountDownScreen *timerScreen = (CountDownScreen*) scene->screens[TIMER];
    UITimer *timer = &timerScreen->timer;

    CharacterSelectScreen *charScreen = (CharacterSelectScreen*) scene->screens[CHARACTER_SELECT];
    charScreen->timer = timer;
    charScreen->ctrlMenuCharSelect.timer = timer;
    VehicleSelectScreen *vehicleScreen = (VehicleSelectScreen*) scene->screens[VEHICLE_SELECT];
    if (vehicleScreen != NULL){
        vehicleScreen->timer = timer;
    }
    
    VehicleSelectBattleScreen *vehicleBattleScreen = (VehicleSelectBattleScreen*) scene->screens[SELECT_VEHICLE_BATTLE];
    if (vehicleBattleScreen != NULL){
        vehicleBattleScreen->timer = timer;
    }

    DriftSelectScreen *driftScreen = (DriftSelectScreen*) scene->screens[DRIFT_SELECT];
    driftScreen->timer = timer;

}
kmCall(0x8062e0cc, &PatchPtmfVotingScreen); //0x58
kmCall(0x8062e858, &PatchPtmfVotingScreen); //0x60
kmCall(0x8062e8e8, &PatchPtmfVotingScreen); //0x61
kmCall(0x8062e15c, &PatchPtmfVotingScreen); //0x59
kmCall(0x8062e978, &PatchPtmfVotingScreen); //0x62
kmCall(0x8062ea08, &PatchPtmfVotingScreen); //0x63

kmCall(0x8062e09c, &AddChangeComboScreens); //0x58 84 before a8 breaks
kmCall(0x8062e7e0, &AddChangeComboScreens); //0x60
kmCall(0x8062e870, &AddChangeComboScreens); //0x61
kmCall(0x8062e0e4, &AddChangeComboScreens); //0x59
kmCall(0x8062e900, &AddChangeComboScreens); //0x62
kmCall(0x8062e990, &AddChangeComboScreens); //0x63


void AddCharSelectLayer(CountDownScreen *screen, ScreenType id, u32 r5){
    if (hasStartbeenPressed){
        id = CHARACTER_SELECT;
        hasStartbeenPressed = false;
    } 
    return screen->AddScreenLayer(id, r5);
}

void PatchScreenAfterDrift(InteractableScreen *screen, ScreenType id, PushButton *button){
    GameMode gamemode = raceData->main.scenarios[1].settings.gamemode;
    if (gamemode == MODE_PUBLIC_BATTLE || gamemode == MODE_PRIVATE_BATTLE) id = SELECT_BATTLE_CUP;
    return screen->LoadNextScreen(id, button);
}
kmCall(0x806509d0, &AddCharSelectLayer);
kmCall(0x8084e698, &PatchScreenAfterDrift);
kmWrite32(0x8065086c, 0x38800058);

#endif