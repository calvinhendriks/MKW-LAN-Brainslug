#pragma once
#include <egg/egg.hpp>
#include <Kamek/kamek.hpp>
#include <common.hpp>
#include <nw4r/ut/ut.hpp>
//#include <Misc/Mii.hpp>

class PlayerModelBones;
class MiiHeadsModel;
class PlayerPointers;
class ModelDirector;

class PlayerModel {
public:

  PlayerModel(); //807c7364
  PlayerPointers *PlayerPointers; //as part of a struct
  nw4r::ut::Link link; //presumably to all the model parts?
  UnkType *modelSubstruct; //0x808dbbf0 related to sound
  u8 unknown_0x10;
  u8 unknown_0x11[3];
  u32 unknown_0x14;
  u32 unknown_0x18;
  virtual int unknown_vtable(); //vtable 0x808d2ad8 //0x20
  u8 unknown_0x24[0x38-0x24];
  u32 trickType;
  u32 trickDirection;
  u8 unknown_0x40[0x68-0x40];
  void *driverModelBRRES; //0x68
  ModelDirector *driverModel; //linked to mdl0 of the brres above
  ModelDirector *driverModel_lod; //linked to mdl0_lod of the brres above
  UnkType *unknown_0x74;
  float unknown_0x78[0xA8-0x78]; //related to the character, direction they are looking at, angle, scale, etc...
  bool isCpu;
  u8 unknown_0xa9[0xB8-0xA9];
  UnkType *unknown_0xB8;
  Vec3 unknown_0xBC;
  bool isHq;
  u8 unknown_0xC9[0xCC-0xC9];
  UnkType *unknown_0xCC[2];
  u8 unknown_0xD4[2];
  bool isNotFocusedInLiveView;
  u8 unknown_0xD7[2];
  UnkType unknown_0xD8[2];
  u8 unknown_0xE0[0xfa-0xe0];
  u16 currentAnimation;
  u16 lastAnimation;
  u8 unknown_0xF8[0x100-0xf8];
  MiiHeadsModel *miiHeads; //0x807c795c
  PlayerModelBones *bones;
  u8 unknown_0x108[0x10c-0x108];
  char* characterName;
  u8 unknown_0x110[0x6e4-0x110];
};//total size 0x6e4

class ModelDirector{
public:
  ModelDirector(); //0x8055b298 vtable 808b47f0
  virtual ~ModelDirector(); //0x8055b5bc
  u32 unk_bitfield;
  u32 unknown_0x8;
  void *rawData; //MDL0 magic? seems to be wrong
  UnkType *g3dHolder;
  UnkType g3dHolderList[2];
  u32 unknown_0x1c[2];
  u32 isTransparent;
  UnkType *modelTransformator;
  UnkType unknown_0x2c[0x44-0x2c];
  UnkType objRenderer;
}; //total size 0x4c

class MiiHeadsModel : public ModelDirector {
public:
  MiiHeadsModel(); //807dbe0c 808d2e10
  virtual ~MiiHeadsModel(); //807d6860
  void *InitModel(Mii *mii, ModelDirector *driverModel, u32 r6, u32 r7, u32 r8, u32 id);
  Mii *mii;
  ModelDirector *driverModel;
  u8 unknown_0x54[0x70-0x54];
}; //total size 0x70
