#pragma once
#include <Kamek/kamek.hpp>
#include <nw4r/lyt/lyt.hpp>

class Screen;
class MainLayout;
class LayoutUIControl;

struct PositionAndScale{
    Vec3 position;
    Vec2 scale;
    u8 opacity;
    u8 unknown_0x15[0x18-0x15];
}; //Total Size 0x18


class GroupAnims{
public:
    GroupAnims(); //8063c53c 
    nw4r::lyt::AnimTransformBasic *transform;
    u32 unknown_0x4;
    float speed; //0x8
    u8 unknown_0xC;
    u8 unknown_0xD[3];
};

class PaneGroup{
public:
    PaneGroup(); //0x8063c844
    void DisplayAnimation(u32 id, float value);
    GroupAnims *groupAnims;
    u32 animationsCount;
    nw4r::lyt::Group group;
    bool isRecursive;
    bool isActive;
    u8 unknown_0x36[2];
    u32 currentAnimation;
    float unknown_0x3C[2];
};

class UIAnimator{
public:
    UIAnimator(); //0x8063c3ec
    void CreatePaneGroups(u32 groupCount); //0x8063c470
    PaneGroup *PaneGroupById(u32 id);
    PaneGroup *paneGroups; //array of pane groups
    u32 animationCount; //Unsure
    nw4r::lyt::Pane *rootPane;
    MainLayout *layout;
    
}; //Total Size 0x10

class BMGThing{
public:
    BMGThing(); //0x805f8b34
    u32 GetMsgId(s32 id);
    u32 *pointer_0x0;
    u32 *pointer_0x4;
    u32 *pointer_0x8; //points to UTF-16 strings of all bmg messages
    u32 unknown_0xC;
    u32 *pointer_0x10;
}; //Total Size 0x14

class ParentScreenLayout{
public:
    virtual ~ParentScreenLayout(); //vtable 808b950c
    nw4r::lyt::Layout layout; //from 0x0 to 0x0
    UnkType *pointer1_0x24;    //0x24
}; //Total size 0x28

class MainLayout : ParentScreenLayout {
public:
    MainLayout(); //vtable 808b94c4
    virtual ~MainLayout();
    nw4r::lyt::Pane *GetPaneByName(char *paneName);
    char string[0x44]; //from 0x28 to 0x6
    u8 unknown_0x6C[0x9C-0x6C];
}; //Total Size 0x9C

class ControlGroup {
public:
    ControlGroup(); //0x805C23E4
    ~ControlGroup(); //0x805c2400
    void Update(); //0x805c28d8
    void InitControls(); //0x805c2868
    void Init(Screen *parentScreen, u32 controlCount); //0x805c2620
    void SetControl(u8 index, LayoutUIControl *control, bool r6); //0x805c27dc
    LayoutUIControl **controlArray; //pointer to the array of controls
    LayoutUIControl **controlArray2; //pointer to the array of controls, of length controlCount, idk what is the difference look the same in game
    LayoutUIControl *parentControl;
    Screen *parentScreen;
    u32 controlCount;
};//Total Size 0x14

class ScreenText {
public:
    ScreenText();
    u32 intToPass[9];
    u32 bmgId[9];
    u32 miis[9];
    u8 licenseId[9];
    u8 unknown_0x75[3];
    u32 playerId[9];
    wchar_t *strings[9];
    bool useColoredBorder;
    char unknown_0xC1[3];
}; //total size 0xC4

class UIControl { 
public:
    UIControl(); 
    virtual ~UIControl();  //vtable 808bf008
    virtual void Init();
    virtual void Update();
    virtual void Draw(); //inferred from the name of the child overriden function
    virtual void InitSelf(); //just a blr
    virtual void OnUpdate(); //just a blr
    virtual void setPosition(); 
    virtual void func_805BD2DC(); //just a blr
    virtual int GetStaticInstanceAddr(); //returns 809c1e80 0x28
    virtual char* getClassName(); //how the class name was found
    virtual void func_0x30();
    virtual void func_805bd2d8(); //just a blr
    PositionAndScale positionAndscale[4]; //same structs repeats itself 4 times, but only the last one seems to do anything?
    ControlGroup *parentCtrl; //0x64 points to the parent class holding all screens 
    ControlGroup childrenCtrlGroup; 
    u32 drawPriority; //setting this to anything but 0 removes the element
    bool isHidden;
    u8 unknown_0x81[0x84-0x81];
    bool unknown_0x84;
    u8 unknown_0x85[0x8C-0x85];
    float unknown_0x8C;
    u32 unknown_0x90[2];
}; //Total Size 0x98

class LayoutUIControl : public UIControl {
public:
    LayoutUIControl(); //0x8063d798
    virtual ~LayoutUIControl(); //vtable 808befb4 0x8
    virtual void Init(); //0xc
    virtual void Update(); //0x10
    virtual void Draw(); //0x14
    //InitSelf 0x18
    //OnUpdate 0x1c
    //SetPosition 0x20
    //func_805bd2dc 0x24
    virtual int GetStaticInstanceAddr(); //returns 809c1e84 //0x28
    virtual char* getClassName(); //how the class name was found 0x2c
    virtual void func_0x30(); //called screen_buttonHolder 0x30
    //func_805bd2d8 0x34
    virtual void func_0x38(); //called screen_buttonHolder too
    void SetText(u32 bmgId, ScreenText *text);
    void SetMsgId(u32 bmgId, ScreenText *text);
    UIAnimator animator;
    MainLayout layout;
    BMGThing bmgThing1;
    BMGThing bmgThing2;
    UnkType *pointer_0x16C;
    u32 unknown_0x170;
};//Total Size 0x174

class ControlLoader{
public:
    LayoutUIControl *layoutUIControl;
    ControlLoader(LayoutUIControl *control);
    void Load(char *folderName, char *ctrName, char *variant, const char **animNames);
    ~ControlLoader();
    u8 unknown_0x4[0x28-0x4];

};//Total Size 0x28

class CtrlRaceBase : public LayoutUIControl { //one element is one CtrlRaceBase
public:
    //CtrlRaceBase(); //literally cannot find it
    virtual ~CtrlRaceBase(); //vtable 808d3a98
    //init 0xc
    //update 0x10
    //draw 0x14
    virtual void InitSelf(); //called setup pause position on sanbo
    //OnUpdate 0x1c
    //SetPosition 0x20
    //func_805bd2dc 0x24
    virtual int GetStaticInstanceAddr(); //returns 809c4010
    virtual char* getClassName(); //0x2c
    //func_0x30 
    //func 0x34
    //func 0x38
    virtual void UpdatePausePosition(); //0x3c
    virtual void func_0x40(); 
    virtual nw4r::lyt::Pane* GetPane(); //children use it if they have a pane
    virtual bool isPaused(); //returns MenuData -> curScene -> isPaused //0x48
    virtual bool hasRaceStarted(); //checks raceinfo->timer //0x4c
    void HudSlotColorEnabled(char *pane, bool enable); //pane name from the brlyt
    int getControlCount();
    u8 getPlayerId();
    u8 unknown_0x174[0x18C-0x174]; //couldn't find the ctor so based on 807f7c18 (ctor for timer element)
    nw4r::lyt::Pane *pane; //seems to be null pane for most children
    u8 hudSlotId;
    u8 unknown_0x191[0x198-0x191];
};//Total Size 0x198

class CtrlRaceCount : public LayoutUIControl {
    CtrlRaceCount(); //0x80858828
    virtual ~CtrlRaceCount(); //807ee40c vtable 0x808d3c18
    u8 unknown_0x174[0x198-0x174];
};

class CtrlRaceWifiStartMessage : public CtrlRaceBase {
public:
    //no ctor
    virtual ~CtrlRaceWifiStartMessage(); //vtable 808d4110 807f91f0
    virtual void OnUpdate();
    virtual int GetStaticInstanceAddr();
    virtual char *getClassName();
    virtual void func_0x40(); 
    virtual nw4r::lyt::Pane* GetPane();
    virtual bool isPaused(); //returns MenuData -> curScene -> isPaused //0x48
    virtual bool hasRaceStarted(); //checks raceinfo->timer //0x4c


    void Load(u32 variant, u32 hudSlotId); //807f8994 variant = localPlayerCount except 3 where it's 4 gamemodeType determines the displayed message
    nw4r::lyt::Pane *textBox_00;

};
//80858728
// 808d4110 custom func_0x40
//update pause position calls 807f8bd8 to make the state disappear

class CtrlMenuPageTitleText : public LayoutUIControl{
public:
    CtrlMenuPageTitleText(); //inlined 80836de4 for example
    virtual ~CtrlMenuPageTitleText(); //805baf10 vtable 808d36d4
    void SetText(u32 bmgId, ScreenText *text); //can just call with no screentext    
};

class CtrlMenuInstructionText : public LayoutUIControl{
public:
    virtual ~CtrlMenuInstructionText(); //805c00c0 vtable
    void SetText(u32 bmgId, ScreenText *text); //can just call with no screentext
}; //total size 0x174

class CharaName :public LayoutUIControl{
public:
    CharaName(); //8083d440
    virtual ~CharaName(); //0x8062912c vtable 808d9358
    u32 unknown_0x178;
}; //total size 0x178

class NoteModelControl : public LayoutUIControl {
public:
    NoteModelControl(); //805f42b4 vtable 808b9ad0
    virtual ~NoteModelControl(); //805f42f0
    void onInit(); //80837134
    bool unknown_0x174;
    u8 unknown_0x175[3]; //might be padding
    u32 unknown_0x178; //result of 805f5a98, which seems to be the init func
    bool unknown_0x17C;
    u8 unknown_0x17D[3]; //might be padding
};

class VehicleModelControl : public NoteModelControl{ //this c
public:
    VehicleModelControl(); //805f39bc vtable 808B9B0C
    virtual ~VehicleModelControl(); //805f39f8
    float unknown_0x180;
}; //Total size 0x184

class DriverModelControl : public LayoutUIControl{
public:
    DriverModelControl(); //805f3248
    virtual ~DriverModelControl(); //0x805f3284 vtable 808b9b48
    u8 layoutId;
    u8 unknown_0x175[3]; //might be padding
    u32 mode; //value based on menuId 805f5a98
    u8 translatesOnScreenTransition;
    float unknown_0x184; //some sort of scale factor for the transition
};//total size 0x188

