#include <Kamek/kamek.hpp>
#include <System/system.hpp>
#include <Input/inputdata.hpp>
#include <UI/menudata.hpp>
#include <Race/racedata.hpp>
#include <paramsholder.hpp>

#ifdef BOOTINTOMENUS

u16 controllerOnStrap = 0x112;
asm int ControllerOnStrapPress(){
    ASM(
    mr r3, r31;
    cmpwi r3, 0;
    beq+ end;

    li r6, 0x3;
    addi r5, sp, 0x10;
    loop:;
    mulli r4, r6, 0xC;
    lhzx r4, r5, r4;
    cmpwi r4, 0x0;
    addi r4, r6, 0x1;
    slwi r4, r4, 0x8;
    addi r4, r4, 0x24;
    bne- store;

    subic. r6, r6, 1;
    bge+ loop;

    slwi r5, r29, 0x8;
    lbz r6, 0x9F (sp);
    addi r4, r5, 0x11;
    cmpwi r6, 0x2;     //wheel
    beq- store;
    addi r4, r5, 0x12;
    cmpwi r6, 0x5;     //nunchuck
    beq+ store;
    addi r4, r5, 0x13;

    store:;
    lis r5, controllerOnStrap@ha;
    sth r4, controllerOnStrap@l (r5);
    end:;
    )
}
kmCall(0x800079b0, &ControllerOnStrapPress);

char bootParams[16] = "-s132 -l0 -p274";
MenuType BootIntoMenu(){
    ParamsHolder *params = ParamsHolder::sInstance;
    RacedataScenario *scenario =  &raceData->main.scenarios[1];
    MenuData98 *menuData98 = menuData->menudata98;
    MenuType menu = MENU_NONE;
    switch (params->settings.scrollSetting[0]){
        case 1:
            scenario->settings.gamemode = MODE_TIME_TRIAL;
            scenario->settings.engineClass = CC_150;
            for (u8 i = 1; i<0xC; i++){
                scenario->players[i].playerType = PLAYER_NONE;
            }
            scenario->players[0].characterId = FUNKY_KONG;
            scenario->players[0].vehicleId = BOWSER_BIKE;

            menuData98->characters[0] = FUNKY_KONG;
            menuData98->vehicles[0] = BOWSER_BIKE;
            menu = SINGLE_PLAYER_TT_CHANGE_COURSE;
            break;

        case 2:
            menu = SINGLE_PLAYER_FROM_MENU;
    }

    snprintf(bootParams, 16, "-s132 -l0 -p%d", controllerOnStrap);
    systemManager->ndevArg = bootParams;
    SetupMenuLoad();

    return menu;
}
kmCall(0x80634f20, &BootIntoMenu);

void SetUpCorrectController(RealControllerHolder *realControllerHolder, void* inputDataSub, u32 r5){  //r4 usually uses inputdata3 which is slot and controller independant
    u32 controllerInfo = menuData->sub.controllerInfos[0].controllerSlotAndType;  //technically hooking into a loop 
    ControllerType controllerType = ControllerType(controllerInfo & 0xFF);
    u32 slot =((controllerInfo & 0xFF00) >>0x8) - 1; //to make it 0-indexed
    InputData *input = inputData;
    if (controllerType == GCN) inputDataSub = (void*) &input->gcnControllers[slot];
    else inputDataSub = (void*) &input->wiiControllers[slot];
    StoreCorrectInputDataSub(realControllerHolder, inputDataSub, r5);
    return;
}
kmCall(0x805243f4, &SetUpCorrectController);

#endif