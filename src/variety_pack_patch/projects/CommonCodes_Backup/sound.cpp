#include <Kamek/kamek.hpp>
#include <common.hpp>
#include <nw4r/ut/ut.hpp>
#include <nw4r/snd/snd.hpp>
#include <Sound/musichandler.hpp>
#include <Sound/RaceRSARSounds.hpp>
#include <Sound/AudioManager.hpp>
#include <Race/playerholder.hpp>
#include <UI/menudata.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <paramsholder.hpp>

#ifdef SOUND

bool LoadBRSTMVolume(nw4r::snd::DVDFileReader *fileReader, nw4r::snd::StrmSound *sound){
    u8 volume = fileReader->strmFileReader.header->volumeByte;
    if (volume != 0){
        u32 maxVolume = 0x7F;
        if (volume > maxVolume) volume = maxVolume;
        sound->volumeRatio = (float) volume / (float) maxVolume;
    }
    return fileReader->InitHeadData(&sound->strmPlayer.headData.base);
}
kmCall(0x800a66f4, &LoadBRSTMVolume);
kmWrite32(0x800a66f0, 0x389DFF00);

void BRSAREntrySizePatch(nw4r::snd::DVDSoundArchive::DVDFileStream *stream, u32 begin, u32 r5){
    stream->size = 0x7FFFFFFF;
    stream->Seek(begin, r5);
    return;
}
kmCall(0x80091354, &BRSAREntrySizePatch);

void MusicSpeedup(RaceRSARSoundHandler *soundHandler, u32 jingle, u32 r5){
    ParamsHolder *params = ParamsHolder::sInstance;

    RaceinfoPlayer *localPlayer = raceInfo->players[(&raceData->main)->scenarios[0].settings.hudPlayerIds[0]];
    PlayerSound *playerSound = *(&playerHolder->players[localPlayer->id]->pointers.playerSound);
	u8 maxLap = localPlayer->maxLap;
    if (maxLap == (&raceData->main)->scenarios[0].settings.lapCount && (&raceData->main)->scenarios[0].settings.lapCount != 1){
        if (params->settings.radioSetting[2] == 1){
            Timer *raceTimer = &raceInfo->timerManager->timers[0];
            Timer *playerTimer = &localPlayer->lapFinishTimes[maxLap-2];
            Timer difference = *raceTimer - playerTimer;
            if(difference.minutes < 1 && difference.seconds < 5){
                nw4r::snd::BasicSound *basicSound = NODE_TO_ITEM(playerSound->brstmData->soundPlayer->soundList.initialNode.next, nw4r::snd::BasicSound, soundList);
                basicSound->ambientPitch += 0.0002f;
            }
            if (maxLap != playerSound->currentLap) soundHandler->PlayBRSARSound(0x74, r5);
        }
        else{
            if ((maxLap != playerSound->currentLap) && (*(&musicHandler->raceState) == 0x4 || *(&musicHandler->raceState) == 0x6)){
                musicHandler->ChangeMusic((RaceState)0x5);
            }
        }
    }
    else{
        if (maxLap != playerSound->currentLap){
            soundHandler->PlayBRSARSound(jingle, r5);
        }
    }
    return;
}
kmCall(0x8070b2f8, &MusicSpeedup);
kmWrite32(0x8070b2c0, 0x60000000);
kmWrite32(0x8070b2d4, 0x60000000);

int CheckChannelCount(UnkType *r3, u32 channel, nw4r::snd::StrmSound *strmSound){
    u32 id = strmSound->soundId;
    u32 need = strmSound->strmPlayer.channelsNeeded;
    u32 channelCount = strmSound->strmPlayer.headData.base.channelCount;
    return (channelCount < need) ? -1 : id;
}

asm int ConditionalChannelSwitch(){
    ASM(
    nofralloc;
    mr r27, r3;
    mr r28, r4;
    mflr r29;
    bl CheckChannelCount;
    mr r0, r3;
    mr r3, r27;
    mr r4, r28;
    mtlr r29;
    blr;
    );
}
kmCall(0x806fab78, &ConditionalChannelSwitch);

#endif