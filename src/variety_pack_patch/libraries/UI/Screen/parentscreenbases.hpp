#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Screen/base.hpp>
#include <Misc/Mii.hpp>
#include <UI/Ctrl/Ctrl.hpp>

struct UnkArray {
    u8 unknown_0x0[0x104-0x0]; //each element is 0x34 bytes long
}; //Total Size 0x104

class UnkClass2 {
public:
    UnkClass2(); //805ef240
    ~UnkClass2(); //805ef2fc
    virtual void func_vtable(); //0x808b9a48
    u8 unknown_0x4[0x3C-0x4]; //has an array of something related to inputs
    UnkArray array;
}; //Total Size 0x144

class BalloonClass{
    BalloonClass(); //0x807f1c58
    ~BalloonClass(); //0x80858864
    u8 unknown_0x0[0xC4];
}; //total size 0xC4

class CtrlRaceNameBalloon : public LayoutUIControl {
    CtrlRaceNameBalloon(); //808588cc
    virtual ~CtrlRaceNameBalloon(); //807f4820
    u8 unknown_0x174[0x17C-0x174];
    BalloonClass *balloonClass;
    u8 unknown_0x180[0x188-0x180];
}; //total size 0x188

class PauseScreen : public Screen{
public:
    PauseScreen(); //80858ca4 vtable 0x808da928
    virtual ~PauseScreen(); //80624b38
    virtual ScreenType GetPauseScreenId();
    u32 unknown_0x44;
    PushButton **buttons; //number of buttons depends on the specific screen
    u8 unknown_0x4C[0x54-0x4C];
    u32 unknown_0x54;
    u8 unknown_0x58[0xF0-0x58];
    ScreenType onContinuePressNextScreen;
    ptmfHolder ptmfHolder_0xF4; //0xF4 vtable = 0x808da9b0 function = 8085a0f4 on itself onClick?
    ptmfHolder ptmfHolder_0x108; //0x104 vtable = 0x808da9a4 function = 8085a098 on itself onClick?
    ScreenActionController screenActionController;
}; //total size 0x340

class RaceScreen: public Screen { 
public:
    RaceScreen(); //ctor seems inlined, vtable 0x808da710
    virtual ~RaceScreen();
    virtual int getNextScreen();
    virtual void func_0x20();
    virtual void Init();
    virtual void ClearInstance(); //sets 0x809c4680 to 0
    virtual void func_0x34(); //sets 0x44 to 0
    virtual void func_0x48(); //extensively patched in advanced watch replay
    virtual void func_0x4C(); //also patched in advanced watch replay
    virtual int GetStaticInstanceAddr(); //returns 809C4640
    int getCtrlRaceBaseCount(); //returns how screen elements there should be
    void InitCtrlRaceBase(u32 bitField); //inits all of the screen elements 

    u32 nextScreenId;
    Timer timer; //0xC
    u8 countDown; //0 1 2 3 4, 4 at GO
    u32 unknown_0x54; //0x54
    CtrlRaceCount *ctrlRaceCountArray;  //0x58, 2 elements per hudSlot
    LayoutUIControl *ghostMessage; //GHOST CANNOT BE SAVED //0x5C
    bool hudHasPlayer[4]; //is true if there's a player 0x60
    u32 id; //unsure when there are multiple players
    u8 unknown_0x68;
    u8 unkknown_0x69[0x78-0x69];
    u32 framesAfterFinish; //0x78
    PauseScreen *pauseScreen; //0x7C, only set when in an actual pause
    UnkClass2 class2;
    u8 unknown_0x1C4[0x1D0-0x1C4]; //based on all of the new such as 806234f4
    CtrlRaceNameBalloon *ctrlRaceNameBalloonArray; //0x1d0 one per hudslot
    BalloonClass *balloonClassArray; //0x1D4 one per hudslot
    u8 unknown_0x1D8[4];
}; //Total Size 0x1DC
extern RaceScreen *raceScreen;

class InteractableScreen : public Screen {
public:
    InteractableScreen(){}; //seems to be inlined vtable 808d8d78
    virtual ~InteractableScreen();
    virtual int getNextScreen();
    virtual void AddScreenLayer(ScreenType id, u32 r5); //806025b0
    virtual void OnInit(); //just a blr
    virtual void OnLoad(); //just a blr   
    virtual void OnActivate(); //just a blr
    virtual void OnDefocus(); //just a blr
    virtual void OnResume(); //just a blr
    virtual int GetStaticInstanceAddr(); //returns 809C1d10
    virtual void OnSelectChange(PushButton *button, u32 r5);
    
    void LoadPrevMenu(PushButton *pushButton);
    
    void Init(); //80836b9c
    void LoadNextScreen(ScreenType id, PushButton *button); //80837720
    void LoadPrevScreen(PushButton *button);
    MiiGroup *playerMiis; //from MenuData98 //0x44
    PushButton **externObjects; //array to the PushButtons of all the buttons probably
    u32 externObjectsCount;
    PushButton *curSelect; //0x50
    CtrlMenuBackButton backButton; //0x54
    CtrlMenuPageTitleText *topText; //0x2B8
    CtrlMenuInstructionText *bottomText; //0x2bc
    u8 unknown_0x2C0[0x310-0x2C0];
    u32 videoCount;
    ScreenText text;
    u32 layoutCount; //3D8
    bool hasBackButton;
    u8 extraControlype; //affects controlCount
    u8 unknown_0x3DE[0x3E0-0x3dE];
    NoteModelControl **modelPosition; //array [extraControlNumber] elements
    u32 titleBmgId; //0x3e4
    ScreenType nextScreenId;//0x3e8
    ScreenType prevScreenId;//0x3ec
    MenuType prevMenu; //0x3f0
    MenuType nextMenu; //0x3f4
    u32 controlSources; //0x80836cc8 3f8
    PtmfHolder_1A<InteractableScreen, void, PushButton*> loadPrevMenuHandler; ////0x3fc
    PtmfHolder_0A<InteractableScreen, void> initThpPtmf; //0x410
    u32 videoStartFrame; //0x424
    u32 extraControlNumber; //depends on the amount of local players and the screen
    bool isLocked;
    u8 unknown_0x42D[0x430-0x42D];
}; //total size 0x430

/*
InteractableScreen::InteractableScreen(){
    videoCount = 0;
    layoutCount = 1;
    hasBackButton = true;
    extraControlype = 0;



};*/