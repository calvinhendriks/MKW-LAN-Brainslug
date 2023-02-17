#pragma once
#include <lecode.hpp>
#include <common.hpp>
#include <base/c_stdlib.hpp>
#include <UI/menudata.hpp>
#include <UI/Screen/base.hpp>
#include <UI/Screen/parentscreenbases.hpp>
#include <Sound/musichandler.hpp>
#include <Race/kmp.hpp>
#include <Race/raceinfo.hpp>
#include <Race/racedata.hpp>
#include <Race/playerholder.hpp>
#include <Race/Item/itemslotdata.hpp>
#include <Race/Item/itemobjproperties.hpp>
#include <Race/Item/itemholder.hpp>
#include <Race/Item/itembehaviour.hpp>
#include <Race/Item/itembehaviour.hpp>
#include <Network/rknetcontroller.hpp>
#include <Model/model.hpp>
#include <Kamek/kamek.hpp>
#include <Input/inputdata.hpp>
#include <System/system.hpp>
#include <Sound/musichandler.hpp>
#include <UI/Ctrl/Action.hpp>
#include <UI/Ctrl/Ctrl.hpp>
#include <UI/HudElements/HudElements.hpp>

extern int *GreenShellSpeed;
extern int *RedShellSpeed;
extern int *BlueShellSpeed;
extern int *WaitForGhostLoadDone;
extern int *Player_getControllerHolder;
extern int *RKNetController_ConnectToAnybodyAsync_VsRegionSet;
extern int *RKNetController_ConnectToAnybodyAsync_BtRegionSet;
extern int *RKNetController_ConnectToGameServerFromGroupId_VsRegion;
extern int *RKNetController_ConnectToGameServerFromGroupId_BtRegion;
//extern int *UseMegaFunction;
extern "C"{
    void SetMatIcon(UnkType *r3, char *materialName, char *iconPaneName);
    int PlayBRSARSound(int r3, u32 soundId, u32 r5);
    void ChangeMusic(MusicHandler *musichandler, RaceState raceState);
    u32 LoadFromU8(UnkType *archive, u8 src, char *fileName, UnkType *r6);
    void ScreenCtr_loadCtr(UnkType *r3, char *folderName, char *ctrName, char *locName, char **animNames);
    void CopyItemOBJPropertiesFromRelToTable(int *itemTable, ItemOBJProperties *itemObjProperties);
    UnkType *ResFile_LoadFromU8(int *r3, UnkType U8Source, char *fileName);
    void GetBrakeSound(u8 characterId, PlayerSub1c *playerSub1c);
    void UseMegaFunction(ItemHolderPlayer *itemHolderPlayer);
    void LoadObjModelFromU8(UnkType *OBJCollidable, u8 src, char *fileName, UnkType *r6);
    void _OSLaunchTitle(UnkType r3, UnkType r4);
    void SubtractItem(PlayerInventory *playerInventory, int r4);
    UnkType *GenerateEvent(UnkType r3, u8 id);
    void MenuData_loadNextMenu(MenuData *menuData);
    u32 func_807907f8(UnkType *courseModel, Vec3 *v0, Vec3 *v1, UnkType kcl_flags, UnkType *the_answer, UnkType *r8, UnkType r9);
    void func_8058160c(PlayerSub10 *playerSub10);
}

class Quad2D{
public:
    bool IsInConvexQuad(Vec2 *point);
    Vec2 PointA;
    Vec2 PointB;
    Vec2 PointC;
    Vec2 PointD;
};

class CtrlRaceSpeedo : public CtrlRaceBase {
public:
    virtual void Init();
    virtual void OnUpdate();
    void Load(char* variant, u8 id);
};

class CtrlRaceDebug : public CtrlRaceBase {
public:
    virtual void Init();
    virtual void OnUpdate();
    void Load();
};

class RaceLoadHook {
private:
    typedef void (Func)();
    Func *mFunc;
    RaceLoadHook * mNext;

    static RaceLoadHook * sHooks;

public:
    RaceLoadHook(Func * f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (RaceLoadHook * p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};

class RaceFrameHook {
private:
    typedef void (Func)();
    Func *mFunc;
    RaceFrameHook * mNext;

    static RaceFrameHook * sHooks;

public:
    RaceFrameHook(Func * f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (RaceFrameHook * p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};

class BootHook {
private:
    typedef void (Func)();
    Func *mFunc;
    BootHook * mNext;

    static BootHook * sHooks;

public:
    BootHook(Func * f) {
        mNext = sHooks;
        sHooks = this;
        mFunc = f;
    }

    static void exec() {
        for (BootHook * p = sHooks; p; p = p->mNext)
            p->mFunc();
    }
};
extern "C"{
    void StoreFlapIntoSave(UnkType *saveDataManagerLicense, UnkType *timer, u32 r5, CourseId id);
}

bool CheckButtonPressed(RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, u32 button);
bool CheckButtonCombination(RealControllerHolder *controllerHolder, ControllerType controllerType, bool onlyCheckNewButtons, UniversalButtons buttonMask);