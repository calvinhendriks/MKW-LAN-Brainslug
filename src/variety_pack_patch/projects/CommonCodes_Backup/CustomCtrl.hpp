#pragma once
#include <Kamek/kamek.hpp>
#include <UI/Ctrl/Ctrl.hpp>
#include <UI/Screen/ParentScreenBases.hpp>

class CtrlRaceSpeedo : public CtrlRaceBase {
public:
    virtual void Init();
    virtual void OnUpdate();
    void Load(char* variant, u8 id);
};
u32 CountSOM();
void CreateSOM(Screen *screen, u32 index);

class CtrlRaceDebug : public CtrlRaceBase {
public:
    virtual void Init();
    virtual void OnUpdate();
    void Load();
};
u32 CountDEBUG();
void CreateDEBUG(Screen *screen, u32 index);

class CtrlRaceOffroad : public CtrlRaceBase {
public:
    virtual void Init();
    virtual void OnUpdate();
    void Load();
    u32 offroadFrames;
    float minOffSpeed;
};
u32 CountOFFROAD();
void CreateOFFROAD(Screen *screen, u32 index);

class CtrlRaceTrackInfoDisplay : public CtrlRaceWifiStartMessage {
public:
    void Load();
};
u32 CountINFODISPLAY();
void CreateINFODISPLAY(Screen *screen, u32 index);

class CustomCtrlBuilder {
public:
    typedef u32 (Func)();
    typedef void (Funcv)(Screen *screen, u32 index);
    Func *countCtrls;
    u32 ctrlCount;
    Funcv *createCtrls;
    CustomCtrlBuilder *next;
    static CustomCtrlBuilder * sHooks;
    CustomCtrlBuilder(Func *count, Funcv *create) {
        next = sHooks;
        sHooks = this;
        countCtrls = count;
        createCtrls = create;
    }

    static u32 Count(){
        u32 count = 0;
        for (CustomCtrlBuilder * p = sHooks; p; p = p->next){
            p->ctrlCount = p->countCtrls();
            count += p->countCtrls();  
        }
        return count;
    }
    static void CreateCustomCtrls(Screen *screen, u32 firstIndex){
        u32 index = firstIndex;
        for (CustomCtrlBuilder * p = sHooks; p; p = p->next){
            if (p->ctrlCount != 0){
                p->createCtrls(screen, index);
                index += p->ctrlCount;
            }
        }
    }
};


