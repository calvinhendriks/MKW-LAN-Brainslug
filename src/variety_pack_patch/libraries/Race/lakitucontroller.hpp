#pragma once

#include <Kamek/kamek.hpp>
#include <egg/egg.hpp>
#include <common.hpp>
#include <base/rvl_sdk.h>

class LakituControllerPlayer;
class UnkLakituClass2;
class Player;

class UnkLakituClass{ //likely inherited from another class 808cbc30
    UnkLakituClass(); //0x8074ae2c
    void *actionHolder; //instance +0x8 on ctor, then copy of the ptr at 4
    void *currentActionHolder; //only non-0 while lakitu is active, instance + a set amount depending on what lakitu is
    virtual void func_vtable(); //at 0x8
    
    u32 pointerToItself;
    ptmf unknown_0x10;
    ptmf unknown_0x1C;
    ptmf unknown_0x28;
    

    UnkType unknownClass_0x34; //0x808cbc18, just to get o the correct size, idk because it gets overwritten
}; //unknown total size 0x38

class LakituActionHolder{
    u32 vtable;
    void* subject; //always the controllerplayer itself
    ptmf ptmf1; //807255b0 to use this one
    ptmf ptmf2; //807255f8 to use this one
    ptmf ptmf3; //80725628 to use this one
}; //total size 0x2C

class EnableLakituAction{
    EnableLakituAction(); //inlined everywhere
    virtual ~EnableLakituAction(); 
    virtual void ResetState(); //always called on init
    virtual void EnableAction(); //if the conditions are met
    u8 playerId;
    bool isEnabled; 
    bool hasHappened; //held true forever except if certain conditions can reset the state
    u8 unknown_0x7[2];
};
class EnableCountdownAction : public EnableLakituAction{
    EnableCountdownAction(); //0x80725a78
    virtual ~EnableCountdownAction(); //80725a98 vtable 808c98a0
    virtual void ResetState(); //80725ad8
    virtual void EnableAction(); //if the conditions are met checks raceinfo state to set it 
}; //total size 0x8

class EnableDisplayLapAction : public EnableLakituAction{
    EnableDisplayLapAction(); //0x80725b48
    virtual ~EnableDisplayLapAction(); //80725b68 vtable 808c988c 
    virtual void ResetState(); //80725ba8  runs every frame the action is not enabled, enables by comparing with stored maxLap
    virtual void EnableAction(); //80725bd8 if the conditions are met checks raceinfo state to set it
    u8 maxLap; //0x7
}; //total size 0x8

class EnableRespawnAction : public EnableLakituAction{ //this one 
    EnableRespawnAction(); //0x80725dd8
    virtual ~EnableRespawnAction(); //80725df8 vtable 808c9864
    virtual void ResetState(); //80725e38 
    virtual void EnableAction(); //80725e48 conditions are always met so just a blr
}; //total size 0x8

class EnableBackwardsAction : public EnableLakituAction{ //this one 
    EnableBackwardsAction(); //0x80725c1c
    virtual ~EnableBackwardsAction(); //80725c3c vtable 808c9878
    virtual void ResetState(); //80725c7c 
    virtual void EnableAction(); //80725c98 checks raceinfoPlayer stateflags and also makes sure you are not currently hitting an item or obj
    float unknown_0x8; //unknown
}; //total size 0xC

class EnableEndingAction : public EnableLakituAction{ //this one 
    EnableEndingAction(); //0x80725e4c
    virtual ~EnableEndingAction(); //80725e6c vtable 808c9850
    virtual void ResetState(); //80725eac
    virtual void EnableAction(); //80725ebc checks stateFlags, only if didn't finish in last and past ending camera
}; //total size 0x8

class LakituModel{
public:
    void DisplayLap(float lap);
};

class LakituControllerPlayer { //very likely inherits from a class with vtable 808c9740
    LakituControllerPlayer(Player *player); //80721514
    virtual void func_vtable(); //808c96a0
    void Init(); //80722504 loads jugemu.brres, rod.brres, links anims
    LakituModel *lakituModel; //too lazy to document  //these are all inherited from modeldirector it appears 8055b50c ctor
    LakituModel *rodModel; //same
    LakituModel *signalModel;
    LakituModel *lapModel; 
    LakituModel *finallapModel;
    LakituModel *reverseModel;
    LakituModel *flagModel;
    UnkType *hair;
    LakituModel *lamp;
    UnkType *shadow; //ends at 2c
    Mat34 unknown_0x2C;
    u8 unknown_0x5C; //ctor'd at 1
    u8 unknown_0x5D;
    UnkLakituClass unknown_0x60; //ends at 0x98
    LakituActionHolder actionHandlers[7]; //each has a specific use all are virtual, vtable 808c9728
    /*
    1st one: onNoAction
    2nd one: countdown
    3rd one: display lap
    4th one: respawn
    5th one: backwards
    6th one: ending
    7th one: unknown, doesn't have an enable
    */
    Player *player; //0x1CC
    u32 unknown_0x1D0;
    Vec3 unknown_0x1D4;
    u8 unknown_0x1E0;
    u8 unknown_0x1E1[3]; //seems to be padding
    u32 state; //0x1 load, 0x2 active, 0x3 unload? idk, but forcing it to 0 prevents lakitu from appearing
    u32 frames; //frames each states lasts for //8072411c for unload on lap transition
    u32 animationState; //gets set to 2 when the animation for countdown (the arm moving) starts
    u32 frames2; //only increments for state 0x2 when looking backwards
    EnableCountdownAction *enableCountdownAction; //all of these actions are check by 807234a4, which only runs when the current actionHandler is "onNoAction"
    EnableDisplayLapAction *enableDisplayLapAction;
    EnableRespawnAction *enableThirdAction;
    EnableBackwardsAction *enableBackwardsAction;
    EnableEndingAction *enableEndingAction; //0x204
    u32 unknownclass_0x208; //will do later 80721820 ctor
    u32 unknown_list0x20C;
    u32 unknownclass_0x210; //8074bf28 ctor
    u32 soundclass_0x214; //8070ca8c seems to be for sound
};//total size 0x218

class LakituController {
public:
    EGG::Disposer disposer; //0x808c94bc, idk what this is used for, its dtor is inlined in the actual class dtor
    LakituController(); //8071e270 
    virtual ~LakituController(); //8071e1d8 vtable 808c94b0 at 0x10
    void Init(); //8071e638
    LakituControllerPlayer *lakituControllerPlayers[4]; //lakitu player, one per local player
    u32 localPlayerCount ; //8071e610


}; //total size 0x28


extern LakituController *lakituController; 