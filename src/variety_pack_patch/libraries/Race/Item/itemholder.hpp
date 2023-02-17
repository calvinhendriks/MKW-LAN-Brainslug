/* 
Stebler, CLF (main documentation)
*/
#pragma once
#include <Kamek/kamek.hpp>
#include <egg/egg.hpp>
#include <common.hpp>
#include <Race/playerholder.hpp>

class ItemHolderPlayer;
class PlayerModel;

class Item_KouraTogezo { //yoinked that from sanbo, idk where it's used but I'm keeping it
public:
    virtual int unknown_vtable_0x0();
    u8 unknown_0x4[0x290-0x4];
    float distance[3];
    u8 unknown_0x29c[0x2c4-0x29c];
    u8 currentState;
    u8 unknown_0x2c8[0x2d0-0x2c8];
    u16 * stateIds;
    UnkType stateTable;
    UnkType *self_pointer;
    u8 unknown_0x2dc[0x2ec-0x2dc];
    u8 targetPlayer;
    u8 unknown_0x2ed[0x338-0x2ed];
}; // Total size 0x338

class ParentItemObject{ //Called ItemControllerSub by Ssanbo seems to be the parent class of item type specific ones
public:
    ParentItemObject(); //8079d8bc
    virtual int unknown_vtable(); //0x808d19f0
    ItemObjectId objectId;
    u8 unknown_0x8[0x14-0x8];
    Vec3 unknown_0x20[3];
    Vec3 position;
    Vec3 velocity;
    Vec3 unknown_0x50;
    float unknown_0x5c;
    u8 unknown_0x60[0x174-0x60];
};//Total Size 0x174

class ItemObject : ParentItemObject {
public:
    ItemObject(); //807a6928
    virtual int unknown_vtable(); //808d1c50 each item actually has its own class with as specific vtable, but lazy
    u8 unknown_0x174[0x1A0-0x174];

}; //total size 0x1A0


class PlayerRoulette{
public:
    ItemHolderPlayer *itemHolderPlayer;
    u32 isTheRouletteSpinning;
    u32 frames; //how many frames have the roulette been spinning for
    u32 totalSpinDuration;
    float unknown_0x10[2];
    u32 currentItem;
    u32 nextItem;
    ItemId nextItemId;
    u32 unknown_0x24;
    u16 setting;
    u8 position;
    u8 unknown_0x2B[0x30-0x2b];
    u32 itemNum; //how many items have you pulled so far, useful for mushroom bug
}; //Total Size 0x34

class PlayerInventory{
public:
    void Update();
    ItemHolderPlayer *itemHolderPlayer;
    ItemId currentItemId;
    u32 currentItemCount;
    u8 unknown_0xC[0x1C-0xC];
    bool hasGolden;
    u8 unknown_0x1D[0x22-0x1D];
    u16 goldenTimer;
    u8 unknown_0x24[0x2C-0x24];
}; //Total Size 0x2C

class ItemHolderPlayerSub {
public:
    void Update();
    PlayerPointers *playerPointers;
    ItemHolderPlayer *itemHolderPlayer;
    u8 unknown_0x8[4];
    ItemHolderPlayer *itemHolderPlayer2;
    u8 id;
    u8 unknown0x11[0x14-0x11];
    ItemObjectId itemObjId; //seems to only change for items you can hold "behind" (including triple shells)
    ItemId itemId; //same
    u32 useType; //0x1 if trailing behind 0x2 if trailing behind triples, 0x3 if spinning, 0x4 if no item
    u8 unknown_0x20[0x50-0x20]; //this whole part only changes when trailing/using bananas/shells
    u32 activeItemCount; // eg 0x2 if 2 remaining spinning shells
    u32 unknown_0x54;
    Vec3 playerLeft;
    Vec3 playerUp;
    Vec3 playerFront;
    Vec3 pos;
    Vec3 unknown_0x88;
    u8 unknown_0x94[0xb0-0x94];
    Vec3 itemScale;
    u8 unknown_0xbc[0xc0-0xbc];
    Vec3 unknown_0xc0;
    u8 unknown_0xcc[0xd0-0xcc];
    Vec2 rotatingRadius;
    float unknown_0xd8[2];
    float itemScaleFactor;
    Vec3 itemPos; //relative to the player 0xE4
    u8 unknown_0xf0[0x174-0xF0];
    u16 spawnedObjs[3];
    u8 unknown_0x17a[0x180-0x17a];
}; //Total Size 0x180

class ItemHolderPlayer {
public:
    void Update();
    PlayerPointers *playerPointers;
    PlayerModel *model;
    u8 unknown_0x8[0x18-0x8];
    u8 id;
    bool isHuman;
    bool isRemote;
    bool isBike;
    Player *player;
    PlayerModel *model2;
    Vec3 unknown_0x24;
    u8 unknown_0x30[0x44-0x30];
    PlayerItemPoint itemPoint;  //currently in playerholder.h but will end up in KMP.h
    PlayerRoulette roulette;
    PlayerInventory inventory;
    ItemHolderPlayerSub itemHolderPlayerSub;
    u32 localPlayerNum;
    u8 unknown_0x238[0x248-0x238];
}; //Total Size 0x248

class ItemHolderItem { // one instance per object ID
public:
    ItemObjectId itemObjectId;
    ParentItemObject **itemObject;
    u32 capacity; //unsure what the diff is with limit
    u32 capacity2;
    u32 objCount; //count on the track, including trailing/spinning
    u8 unknown_0x14[0x1c-0x14];
    u32 limit;
    u8 unknown_0x20[0x24-0x20];
};//Total Size 0x24

class ItemHolder : public EGG::Disposer {
public:
    u8 playerCount;
    u8 unknown_0x11[3];
    ItemHolderPlayer *players; //0x14
    ItemHolderPlayer *otherLocalOnlinePlayersplayer[12];
    ItemHolderItem itemHolderItem[0xF]; //One per objectId 0x48
    ItemObject *itemObj[16]; //0x264
    ParentItemObject parentItemObj; //base one? dummy?
    u8 unknown_0x418[0x430-0x418];
};//Total Size 0x430

extern ItemHolder *itemHolder;