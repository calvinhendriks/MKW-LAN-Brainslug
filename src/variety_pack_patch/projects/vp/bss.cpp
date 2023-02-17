#include <project.hpp>
#include <settings.hpp>

bool BlueShellSwapping(bool hasItem){
    if (settings.mode == BSS){
        for(int i=0; i<4; i++){
            u8 hudPlayerId = (&raceData->main)->scenarios[0].settings.hudPlayerIds[i];
            u32 controllerInfo = menuData->sub.controllerInfos[0].controllerSlotAndTypeActive;
            ControllerType controllerType = ControllerType(controllerInfo & 0xFF);
            RealControllerHolder *controllerHolder = &inputData->realControllerHolders[hudPlayerId];
            if (hudPlayerId != 0xFF){
                ItemId currentItem = itemHolder->players[hudPlayerId].inventory.currentItemId;
                if (currentItem == BLUE_SHELL){
                    bool switchItem = false;
                    if(CheckButtonPressed(controllerHolder, controllerType, false, BUTTON_MINUS)){
                        switchItem = true;
                    }
                    else if ((menuData->sub.controllerInfos[0].controllerSlotAndTypeActive & 0xFF) == GCN){
                        if (CheckButtonPressed(controllerHolder, controllerType, false, C_STICK_LEFT_EIGHT) || 
                            CheckButtonPressed(controllerHolder, controllerType, false, C_STICK_RIGHT_EIGHT) ||
                            CheckButtonPressed(controllerHolder, controllerType, false, C_STICK_UP_EIGHT) ||
                            CheckButtonPressed(controllerHolder, controllerType, false, C_STICK_DOWN_EIGHT)){
                            switchItem = true;
                        }
                    }
                    if (switchItem){
                        itemHolder->players[hudPlayerId].inventory.currentItemId = TRIPLE_MUSHROOM;
                        u8 mushroomCount = 3;
                        u8 playerCount = itemHolder->playerCount;
                        u8 position = raceInfo->players[hudPlayerId]->position;
                        float third = (float)position/(float)playerCount;
                        if (third <= 1.0f/3.0f){
                            mushroomCount = 1;
                        }
                        else if (third <= 2.0f/3.0f){
                            mushroomCount = 2;
                        }

                        itemHolder->players[hudPlayerId].inventory.currentItemCount = mushroomCount;
                    }
                }
            }
        }
    }

    return hasItem;
}

kmBranch(0x807eeed0, &BlueShellSwapping);