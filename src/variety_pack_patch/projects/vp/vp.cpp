#include <project.hpp>
#include <settings.hpp>

s16 invincibilityTimer[12];
int fastFallTimer = 0x0;

// Login Region
kmWrite32(0x80384fd4, 0x30383535);

void GetCustomItemWindow(UnkType *r3, char *folderName, char *ctrName, char *locName, char **animNames){
    if (settings.mode == BSS){
        ctrName = "item_window_new_bss";
    }
    else if (settings.mode == BBB){
        ctrName = "item_window_new_bbb";
    }
    ScreenCtr_loadCtr(r3, folderName, ctrName, locName, animNames);
}

kmCall(0x807ef50c, &GetCustomItemWindow);

u32 GetCustomItemSlot(UnkType *archive, u8 src, char *fileName, UnkType *r6){
    if (settings.mode == NOMODE){
        fileName = "ItemSlot0.bin";
    }
    else if (settings.mode == BSS){
        fileName = "ItemSlot1.bin";
    }
    else if (settings.mode == BBB){
        fileName = "ItemSlot2.bin";
    }
    else if (settings.mode == CHAOTIC){
        fileName = "ItemSlot3.bin";
    }

    return LoadFromU8(archive, src, fileName, r6);
}

kmCall(0x807bb128, &GetCustomItemSlot);
kmCall(0x807bb030, &GetCustomItemSlot);
kmCall(0x807bb200, &GetCustomItemSlot);
kmCall(0x807bbb58, &GetCustomItemSlot);


void ChangeItemBehaviour(){
    ItemBehaviour *table = itemBehaviourTable;
    table[TRIPLE_BANANA].useType = ITEMUSE_CIRCLE;
    table[BLUE_SHELL].useType = ITEMUSE_FIRE;

    if (settings.mode == BBB){
        table[TRIPLE_GREEN_SHELL].objectId = OBJ_BOBOMB;
        table[TRIPLE_GREEN_SHELL].useType = ITEMUSE_CIRCLE;
        table[MUSHROOM].objectId = OBJ_BOBOMB;
        table[MUSHROOM].useType = ITEMUSE_FIRE;
        table[BULLET_BILL].objectId = OBJ_BOBOMB;
        table[BULLET_BILL].useType = ITEMUSE_CIRCLE;
        table[BULLET_BILL].numberOfItems = 0x3;
    }

    if (settings.mode == BSS){
        table[BULLET_BILL].objectId = OBJ_BLUE_SHELL;
        table[BULLET_BILL].useType = ITEMUSE_CIRCLE;
        table[BULLET_BILL].numberOfItems = 0x3;
        table[TRIPLE_GREEN_SHELL].objectId = OBJ_BLUE_SHELL;
    }
}

kmBranch(0x807bd1cc, &ChangeItemBehaviour);

void ChangeItemOBJProperties(int *billTable, ItemOBJProperties *billProperties){
    CopyItemOBJPropertiesFromRelToTable(billTable, billProperties);

    ItemOBJProperties *table = itemObjProperties;

    table[OBJ_BULLET_BILL].limit = 0x2;

    if(settings.mode == BSS){
        table[OBJ_BLUE_SHELL].limit = 0x14;
    }
    if(settings.mode == BBB){
        table[OBJ_BOBOMB].limit = 0x14;
    }
}

kmCall(0x80790c04, &ChangeItemOBJProperties);

// Don't Hide Position After Race
kmWrite32(0x807F4DB8, 0x38000001);

// Show Everyone's Times After Race
kmWrite32(0x8085C914, 0x38000000);
kmWrite32(0x8085D460, 0x4BF984FD);

// Don't Lose VR When Disconnecting
kmWrite32(0x80856560, 0x60000000);

// Coloured Minimap
kmWrite32(0x807DFC24, 0x60000000);

// Unlock Code
kmWrite32(0x80549974, 0x38600001);

// Motion Sensor Bombs
kmWrite16(0x807A5BF6, 0x0FFF);
kmWrite16(0x807A4ACA, 0x0FFF);

void UpdateTimers(){
    for (int i=0; i<12; i++){
        if (invincibilityTimer[i] > 0){
            invincibilityTimer[i]--;
        }
    }
}

static RaceFrameHook updateTimerHook(UpdateTimers);

void ResetTimers(){
    for (int i=0; i<12; i++){
            invincibilityTimer[i] = 0;
    }
}

static RaceLoadHook resetTimerHook(ResetTimers);

void InvincibilityFrames(PlayerSub14 *playerSub14, DamageType newDamage, UnkType r5, int r6, u32 r7){ // For Chaotic add random item damage
    u8 playerId = playerSub14->playerPointers->params->playerIdx;
    if (raceData->main.scenarios[0].settings.gamemode != MODE_BATTLE && 
    raceData->main.scenarios[0].settings.gamemode != MODE_PRIVATE_BATTLE && 
    raceData->main.scenarios[0].settings.gamemode != MODE_PUBLIC_BATTLE && settings.mode != CHAOTIC){
        if (invincibilityTimer[playerId] > 0){
            return;
        }
        invincibilityTimer[playerId] = 150;
    }
    if(settings.mode == CHAOTIC){
        if(Util_RandInt(0, 6) > 1){ // Items
            int rand = Util_RandInt(0, 7);
            int item = MUSHROOM;
            switch (rand){
                case 0:
                    if (newDamage != SPINOUT_SHOCK){
                        item = LIGHTNING;
                    }
                    break;
                case 1:
                    item = STAR;
                    break;
                case 2:
                    item = MEGA_MUSHROOM;
                    break;
                case 3:
                    item = BLOOPER;
                    break;
                case 4:
                    item = POW_BLOCK;
                    break;
                case 6:
                    item = BULLET_BILL;
                    break;
            }
            itemHolder->players[playerId].inventory.currentItemCount += 1;
            itemBehaviourTable[item].useFunction(&itemHolder->players[playerId]);
            return;
        }
        else{ // Damage
            if(Util_RandInt(0, 2) > 0){
                newDamage = (DamageType)Util_RandInt(0, 18);
            }
        }
    }
    playerSub14->Update(newDamage, r5, r6, r7);
}

kmCall(0x805721a4, &InvincibilityFrames);
kmCall(0x805727b4, &InvincibilityFrames);
kmBranch(0x80590d84, &InvincibilityFrames);

UnkType AllVehiclesInBattle(){
    return 0;
}

kmBranch(0x80860A8C, &AllVehiclesInBattle);
kmWrite32(0x8084FEE8, 0x38000000);
kmWrite32(0x80553FAC, 0x38A00000);

// No Team Invincibility
kmWrite32(0x807bd2bc, 0x38000000);
kmWrite32(0x80572618, 0x38000000);

// // VP 200cc

// Minimum Drift Speed Modifier
kmWrite32(0x808B5B1C, 0x3EBBBBBC);

// Engine Class Modifier
kmWrite32(0x808B5CD4, 0x3F666666); //50->100cc
kmWrite32(0x808B5CD8, 0x3F800000); //100->150cc
kmWrite32(0x808B5CDC, 0x3F99999A); //150->200cc

// Max Speed Modifier
kmWrite32(0x808B59F4, 0x43100000);

// Bullet Bill Speed Modifier
kmWrite32(0x808B59F8, 0x432E0000);

// Green Shell Speed Modifier
static PostLECodeHook greenShellSpeedModifier(&GreenShellSpeed, 0x3e6042fc, PostLECodeHook::WRITE32);

// Red Shell Speed Modifier
static PostLECodeHook redShellSpeedModifier(&RedShellSpeed, 0x3e6042b4, PostLECodeHook::WRITE32);

// Blue Shell Speed Modifier
static PostLECodeHook blueShellSpeedModifier(&BlueShellSpeed, 0x3e60431c, PostLECodeHook::WRITE32);

// //

void BrakeDrifting(){
    for (int i = 0; i < raceData->main.scenarios[0].localPlayerCount; i++)
    {
        bool brake = false;
        u8 hudPlayerId = raceData->main.scenarios[0].settings.hudPlayerIds[i];
        u32 controllerInfo = menuData->sub.controllerInfos[0].controllerSlotAndTypeActive;
        ControllerType controllerType = ControllerType(controllerInfo & 0xFF);
        RealControllerHolder *controllerHolder = &inputData->realControllerHolders[i];
        if(controllerType == CLASSIC || controllerType == GCN){
            if(CheckButtonCombination(controllerHolder, controllerType, false, (UniversalButtons)(BUTTON_A | BUTTON_B | BUTTON_R))){
                brake = true;
            }
        }
        else if(controllerType == NUNCHUCK){
            if(CheckButtonCombination(controllerHolder, controllerType, false, (UniversalButtons)(BUTTON_A | BUTTON_B | BUTTON_DPAD_DOWN))){
                brake = true;
            }
        }
        else if(controllerType == WHEEL){
            if(CheckButtonCombination(controllerHolder, controllerType, false, (UniversalButtons)(BUTTON_2 | BUTTON_1 | BUTTON_B))){
                brake = true;
            }
        }

        if (brake && playerHolder->players[hudPlayerId]->playerPointers->playerSub10->driftState != 0){
                float multiplier = 0.95;
                if (playerHolder->players[hudPlayerId]->playerPointers->playerSub10->vehicleSpeed > 0){
                    multiplier = 0.98;
                }
                playerHolder->players[hudPlayerId]->playerPointers->playerSub10->vehicleSpeed *= multiplier;
        }
    }
}

static RaceFrameHook brakeDriftingHook(BrakeDrifting);

void FastFalling(){
    for (int i = 0; i < raceData->main.scenarios[0].localPlayerCount; i++)
    {
        u8 hudPlayerId = raceData->main.scenarios[0].settings.hudPlayerIds[i];
        if(playerHolder->players[hudPlayerId]->playerPointers->playerSub18->preRespawnTimer > 0){
            fastFallTimer = 0x80;
        }
        else{
            if (fastFallTimer > 0){
            fastFallTimer--;
            }
            else if(playerHolder->players[hudPlayerId]->playerPointers->playerSub1c->airtime > 0x20 &&
            inputData->realControllerHolders[i].inputStates->stickY > 0){
                playerHolder->players[hudPlayerId]->playerPointers->playerGraphics->playerPhysicsHolder->playerPhysics->speed0.y -= inputData->realControllerHolders[i].inputStates->stickY;
            }
        }
    }
}

static RaceFrameHook fastFallingHook(FastFalling);

void MegaTC(PlayerSub10 *playerSub10){
    ItemHolderPlayer itemHolderPlayer = itemHolder->players[playerSub10->playerPointers->params->playerIdx];
    UseMegaFunction(&itemHolderPlayer);
}

kmCall(0x80580630, &MegaTC);

int AccurateItemRoulette(ItemSlotData *itemSlotData, int itemBoxSetting, int position, s32 r6, int r7){
    u8 playerId = raceInfo->playerIdInEachPosition[position-1];
    if (raceData->main.scenarios[0].settings.gamemode != MODE_BATTLE && 
    raceData->main.scenarios[0].settings.gamemode != MODE_PRIVATE_BATTLE && 
    raceData->main.scenarios[0].settings.gamemode != MODE_PUBLIC_BATTLE){
        ItemHolderPlayer *itemHolderPlayer = &itemHolder->players[playerId];
        return itemSlotData->decideItem(itemBoxSetting, position, itemHolderPlayer->isHuman, 0x1, itemHolderPlayer);
    }
    return itemSlotData->decideRandomItem(itemBoxSetting, position, r6, r7);
}

kmCall(0x807ba1e4, &AccurateItemRoulette);
kmCall(0x807ba428, &AccurateItemRoulette);
kmCall(0x807ba598, &AccurateItemRoulette);

void VSPointsSystem(){
    for (int i = 0; i < raceData->main.scenarios[1].playerCount; i++){
        u8 playerId = raceInfo->playerIdInEachPosition[i];
        u8 playerIdOf1st = raceInfo->playerIdInEachPosition[0];

        Timer *finishTimer = raceInfo->players[playerId]->raceFinishTime;
        Timer *finishTimerOf1st = raceInfo->players[playerIdOf1st]->raceFinishTime;

        s32 finishTime = finishTimer->milliseconds + finishTimer->seconds*1000 + finishTimer->minutes*60000;
        if (finishTime != 0){
            s32 finishTimeOf1st = finishTimerOf1st->milliseconds + finishTimerOf1st->seconds*1000 + finishTimerOf1st->minutes*60000;

            s32 timeDifference = (finishTime - finishTimeOf1st)/1000;

            if (timeDifference < 30){
                raceData->main.scenarios[1].players[playerId].score = raceData->main.scenarios[1].players[playerId].previousScore + (30-timeDifference);
                if (playerId == playerIdOf1st){
                    raceData->main.scenarios[1].players[playerId].score += 5;
                }
            }
            else{
                raceData->main.scenarios[1].players[playerId].score = raceData->main.scenarios[1].players[playerId].previousScore;
            }
        }
    }
}

kmBranch(0x8052ed14, &VSPointsSystem);

int UseItem(PlayerSub18 *playerSub18, ItemId id){
    u8 playerId = playerSub18->playerPointers->params->playerIdx;
    itemHolder->players[playerId].inventory.currentItemCount++;
    itemBehaviourTable[id].useFunction(&itemHolder->players[playerId]);
    return -1;
}

int AllShocksCanLand(PlayerSub18 *playerSub18){
    return UseItem(playerSub18, LIGHTNING);
}

int AllMegasCanLand(PlayerSub18 *playerSub18){
    return UseItem(playerSub18, MEGA_MUSHROOM);
}

int AllFeathersCanLand(PlayerSub18 *playerSub18){
    return UseItem(playerSub18, BLOOPER);
}

int AllPOWsCanLand(PlayerSub18 *playerSub18){
    return UseItem(playerSub18, POW_BLOCK);
}

int AllGoldensCanLand(PlayerSub18 *playerSub18){
    return UseItem(playerSub18, MUSHROOM);
}

int AllBulletsCanLand(PlayerSub18 *playerSub18){
    return UseItem(playerSub18, BULLET_BILL);
}

kmWritePointer(0x808b54b8, AllShocksCanLand);
kmWritePointer(0x808b54d0, AllMegasCanLand);
kmWritePointer(0x808b54e8, AllFeathersCanLand);
kmWritePointer(0x808b54f4, AllPOWsCanLand);
kmWritePointer(0x808b5500, AllGoldensCanLand);
kmWritePointer(0x808b550c, AllBulletsCanLand);
kmWrite32(0x807A66C4, 0x60000000);
kmWrite32(0x80796D30, 0x38600000);
kmWrite32(0x80790EF0, 0x39800001);
kmWrite32(0x80790EF4, 0x39600001);
kmWrite32(0x80790EF8, 0x39400001);
kmWrite32(0x80790EFC, 0x39200001);

// Faster Voting Roulette
kmWrite32(0x80643c2c, 0x60000000);

void LoadOriginalItemboxes(UnkType *OBJCollidable, u8 src, char *fileName, UnkType *r6){
    if (strcmp(fileName, "itembox.brres") == 0){
        src = 0x0;
    }
    LoadObjModelFromU8(OBJCollidable, src, fileName, r6);
}

kmCall(0x8081fdb4, &LoadOriginalItemboxes);

void LaunchRiivolutionButton(MenuData *menuData){
    if (menuData->nextMenuId == 0x7A){
        int result = ISFSOpen("/title/00010001/52494956/content/title.tmd\0", 1);
        if (result > -1){
            ISFSClose(result);
            _OSLaunchTitle(0x00010001, 0x52494956);
            return;
        }
        result = ISFSOpen("/title/00010001/4c554c5a/content/title.tmd\0", 1); // If Riivolution can't be found try HBC
        if (result > -1){
            ISFSClose(result);
            _OSLaunchTitle(0x00010001, 0x4c554c5a);
            return;
        }
        result = ISFSOpen("/title/00010001/48424330/content/title.tmd\0", 1); // If HBC can't be found try OHBC
        if (result > -1){
            ISFSClose(result);
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

void UseFeather(ItemHolderPlayer *itemHolderPlayer){
    itemHolderPlayer->playerPointers->playerSub10->specialFloor += 4;
    itemHolderPlayer->playerPointers->playerSub1c->jumpPadType = 7;
    if ((itemHolderPlayer->playerPointers->playerSub1c->bitfield1 & 1<<10) != 0){
        itemHolderPlayer->playerPointers->playerSub1c->jumpPadType = 2;
    }
    itemHolderPlayer->playerPointers->playerSub1c->trickableTimer = 4;
    SubtractItem(&itemHolderPlayer->inventory, 0x1);

    if(rkNetController->connectionState != 0 && itemHolderPlayer->player->IsLocal()){
        GenerateEvent(0xA, itemHolderPlayer->id);
    }
}

kmWritePointer(0x808A5894, UseFeather);

void FeatherOnlineFix(UnkType r3, u8 id){
    UseFeather(itemHolder->otherLocalOnlinePlayersplayer[id]);
}

kmCall(0x80796D8C, &FeatherOnlineFix);

kmWrite32(0x808b5c24, 0x42aa0000);
kmWrite32(0x808b5c28, 0x42aa0000);
kmWrite32(0x808b5c2c, 0x42960000);

u32 IgnoreInvisibleWalls(UnkType *courseModel, Vec3 *v0, Vec3 *v1, UnkType kcl_flags, UnkType *the_answer, UnkType *r8, UnkType r9, PlayerSub18 *playerSub18){
    if (((playerSub18->playerPointers->playerSub1c->bitfield0 & 1<<30) != 0) && (playerSub18->playerPointers->playerSub1c->jumpPadType == 0x7)){
        kcl_flags -= 0x2000;
        kcl_flags = kcl_flags & 0x4a109000;
    }
    return func_807907f8(courseModel, v0, v1, kcl_flags, the_answer, r8, r9);
}

asm void IgnoreInvisibleWallsWrapper(){
    ASM(
    nofralloc;

    mr r10, r15;

    b IgnoreInvisibleWalls;
    )
}

kmCall(0x805b68dc, &IgnoreInvisibleWallsWrapper);

// Remove staff ghost loading
kmWrite32(0x806211dc, 0x4e800020);

// 8064ba38 is address for WW Buttons

//// Transmission Select

void temp(){
    OSReport("Brakedrifting Location: %x", &BrakeDrifting);
}

static RaceLoadHook tempHook(temp);