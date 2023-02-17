#include <project.hpp>
#include <settings.hpp>

int miiheads(Racedata *racedata, int r4, int r5, u8 id){
    u32 charId = (&racedata->main)->scenarios[0].players[id].characterId;
    if (settings.miiHeads){
        if (charId < 0x2a){
            if (id == 0){
                charId = 0x2a;
            }
            else if(rkNetController->connectionState != 0)
            {
                charId = 0x2a;
            }
        }
    }
    return charId;
}

kmCall(0x807eb154, &miiheads);
kmWrite32(0x807eb15c, 0x60000000);
kmWrite32(0x807eb160, 0x88de01b4);

void musicSpeedup(int r3, u32 jingle, u32 r5){
    RaceinfoPlayer *localPlayer = raceInfo->players[(&raceData->main)->scenarios[0].settings.hudPlayerIds[0]];
    PlayerSound *playerSound = *(&playerHolder->players[localPlayer->id]->pointers.playerSound);
	u8 maxLap = localPlayer->maxLap;
    if (maxLap == (&raceData->main)->scenarios[0].settings.lapCount && (&raceData->main)->scenarios[0].settings.lapCount != 1){
        if (settings.finalLapSpeedup){
            Timer *raceTimer = &raceInfo->timerManager->timers[0];
            Timer *playerTimer = &localPlayer->lapFinishTimes[maxLap-2];
            Timer difference = *raceTimer - playerTimer;
            if(difference.minutes < 1 && difference.seconds < 5){
                nw4r::snd::BasicSound *basicSound = NODE_TO_ITEM(playerSound->brstmData->soundPlayer->soundList.initialNode.next, nw4r::snd::BasicSound, soundList);
                basicSound->ambientPitch += 0.0002f;
            }
            if (maxLap != playerSound->currentLap){
                PlayBRSARSound(r3, 0x74, r5);
            }
        }
        else{
            if ((maxLap != playerSound->currentLap) && (*(&musicHandler->raceState) == 0x4 || *(&musicHandler->raceState) == 0x6)){
                ChangeMusic(musicHandler, (RaceState)0x5); //0x5 is racestate FAST
            }
        }
    }
    
    else{
        if (maxLap != playerSound->currentLap){
            PlayBRSARSound(r3, jingle, r5);
        }
    }
}

kmCall(0x8070b2f8, &musicSpeedup);

kmWrite32(0x8070b2c0, 0x60000000);
kmWrite32(0x8070b2d4, 0x60000000);

// Silent Controller Changing
kmCallDefAsm(0x8061AF94){
    ASM(
    nofralloc;
    
    lis r12, settings.silentController@ha;
    lbz r12, settings.silentController@l(r12);
    cmpwi r12, 0;
    bne+ end;
    cmpwi r0, 0;

    end:
    blr;
    )
}