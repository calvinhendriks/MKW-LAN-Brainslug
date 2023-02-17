/*
PlayerHolder contains most player-specific data during a race
Contributors:
  stebler (main documentation)
  SwareJonge (extra methods and attributes)
  1superchip (extra timer attributes, correcting some signing of types)
  CLF78 (helped with jump pads)
References:
  http://wiki.tockdom.com/wiki/BSP_(File_Format)
  http://wiki.tockdom.com/wiki/KartParam.bin
  http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
  http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
*/

#pragma once
#include <common.hpp>
#include <Kamek/kamek.hpp>
#include <nw4r/snd/snd.hpp>

class PlayerModel;

enum VehicleType{
    KART=0x0,
    OUTSIDE_BIKE=0x1,
    INSIDE_BIKE=0x2
};

struct ComboIDs{
  VehicleId vehicleId;
  CharacterId characterId;
};

typedef enum DamageType {
    SPINOUT_BANANA=0x0,
    SPINOUT_GOOMBA=0x1,
    KNOCKBACK_SHELL_FIB=0x2,
    KNOCKBACK_STAR=0x3,
    KNOCKBACK_CHOMP=0x4,
    KNOCKBACK_CAR=0x5,
    KNOCKBACK_BULLET=0x6,
    LAUNCH_EXPLOSION=0x7,
    LAUNCH_CATAQUACK=0x8,
    SPINOUT_FIRE=0x9,
    SPINOUT_SHOCK=0xa,
    POW=0xb,
    SQUISH_THWOMP=0xc,
    SQUISH_MEGA=0xd,
    SQUISH_CAR=0xe,
    SPINOUT_ZAPPER=0xf,
    SQUISH_RESPAWN=0x10,
    SPINOUT_THUNDERCLOUD=0x11,
    NO_DAMAGE=0xffffffff
};

class PlayerPointers;
class PlayerSub10;
class CollisionData;
class Hitbox;
class PlayerPhysics;
class PlayerParams;
class StatsAndBsp;





class PlayerBoost {
public:
  PlayerBoost(); // 80588d28
  void reset(); // 80588d74
  bool activate(u32 type, s16 frames); // 80588db0
  void cancelAll(); // 80588e18
  bool update(bool *unk0); // 80588e24
  // vtable 808b5fd8
  virtual ~PlayerBoost(); // 8057811c
  s16 frames[6];
  u16 types; // bit flags:
    /*
      0 mt, ssmt, start boost
      1 unused (intended for star)
      2 mushroom, boost panel
      3 unused (intended for bullet)
      4 trick, zipper
      5 unused (intended for mega and tc)
    */
  u8 unknown_0x11[2];
  float multiplier;
  float acceleration;
  float unknown_0x1c;
  float speedLimit;
}; // total size 0x24

typedef struct JumpPadProperties{
  float minSpeed;
  float maxSpeed;
  float velY;
}; // total size 0xc

typedef enum TrickType {
  STUNT_TRICK_BASIC = 0,
  BIKE_FLIP_TRICK_X_NOSE = 1,
  BIKE_FLIP_TRICK_X_TAIL = 2,
  FLIP_TRICK_Y_LEFT = 3,
  FLIP_TRICK_Y_RIGHT = 4,
  KART_FLIP_TRICK_Z = 5,
  BIKE_SIDE_STUNT_TRICK = 6,
};

typedef enum TrickCategory {
  STUNT = 0,
  SINGLE_FLIP = 1,
  DOUBLE_FLIP = 2,
};

typedef struct TrickProperties{
  float initialAngleDiff;
  float minAngleDiff;
  float minAngleDiffMul;
  float angleDiffMulDec;
}; // total size 0x10

class PlayerTrick {
public:
  PlayerTrick(); // 80575a44
  void updateNext(); // 80575b38
  void tryStart(Vec3 *left); // 80575d7c
  void update(); // 805763e4
  void end(); // 805766b8
  PlayerPointers *pointers;
  u8 unknown_0x4[0xc-0x4];
  // vtable 808b58b0
  virtual ~PlayerTrick(); // 80575aa8
  virtual void start(Vec3 *left); // 80575ee8
  virtual void startInner(TrickCategory category); // 8057616c
  virtual void unknown_1();
  virtual void unknown_2();
  virtual void updateRot(); // 805764fc
  TrickType type;
  TrickCategory category;
  u8 nextDirection;
  u8 unknown_0x19;
  s16 nextTimer;
  float rotDir;
  TrickProperties *properties;
  float angle;
  float angleDiff;
  float angleDiffMul;
  float angleDiffMulDec;
  float maxAngle;
  s16 cooldown;
  bool boostRampEnabled;
  u8 unknown_0x3b;
  Quat rot;
  PlayerSub10 *playerSub10;
}; // total size 0x50

class PlayerTrickBike : public PlayerTrick {
public:
  virtual ~PlayerTrickBike(); // 80576afc
  virtual void start(Vec3 *left); // 80576758
  virtual void startInner(TrickCategory category); // 8057689c
  virtual void updateRot(); // 80576994
  // vtable 808b5890
}; // total size 0x50

class PlayerZipper {
public:
  PlayerZipper(); // 80574114
  void update(); // 80574340
  void end(int unk0); // 805758e4
  PlayerPointers *pointers;
  u8 unknown_0x4[0xc-0x4];
  // vtable 808b5798
  virtual ~PlayerZipper(); // 80574170
  u8 unknown_0x10[0x90-0x10];
}; // total size 0x90

class PlayerSub10 {
public:
  PlayerSub10(); // 80577fc4
  UnkType init(bool unk0, bool unk1); // 805784d4
  UnkType update(); // 805788dc
  UnkType updateHopPhysics(); // 80579968
  UnkType updateDir(); // 8057a140
  UnkType updateAcceleration(); // 8057b9bc
  UnkType updateOffroad(); // 8057c3d4
  UnkType updateRotation(); // 8057c69c
  UnkType updateStandstillBoostRot(); // 8057d1d4
  UnkType updateUps(); // 8057d398
  UnkType updateManualDrift(); // 8057dc44
  UnkType updateAutoDrift(); // 8057e0dc
  UnkType updateHopAndSlipdrift(); // 8057e804
  UnkType activateMushroom(); // 8057f3d8
  UnkType endTrick(); // 8057f7a8
  UnkType activateZipperBoost(); // 8057f96c
  UnkType tryStartJumpPad(); // 8057fd18
  UnkType applyLightning(); // 80580438
  UnkType applyLightningEffect(int frames, int unk0, int unk1); // 80580778
  UnkType activateTc(); // 80581a28
  UnkType deactivateTc(); // 80581a40
  UnkType updateInk(); // 80581b1c
  UnkType applyStartBoost(int frames); // 8058212c
  UnkType tryEndJumpPad(); // 80582530
  UnkType updateBoost(); // 80582694, always inlined
  UnkType releaseMt(int unk0, int unk1); // 80582f9c
  UnkType updateStickyRoad(); // 80583b88
  UnkType setInitialPhysicsValues(Vec3 *position, Vec3 *angles); // 80584044
  UnkType doRespawn(); // 80584334
  UnkType enterCannon(); // 8058498c
  UnkType updateCannon(); // 80584d58
  UnkType activateBullet(int unk); // 805858ac
  UnkType updateDiving(); // 805869dc
  UnkType updateSlipstream(); // 80586fa8
  UnkType updateSpecialFloor(); // 80587590, always inlined
  PlayerPointers *playerPointers;
  int *unknown_0x4;
  int *unknown_0x8;
  // vtable 808b5f60
  virtual ~PlayerSub10(); // 80587b78
  virtual void unknown_1();
  virtual int setTurnParams(); // 8057829c
  virtual void unknown_3();
  virtual int activateStar(); // 80580268
  virtual int activateMega(); // 80580b14
  virtual int applyInk(int unk); // 80581a58
  virtual void unknown_7();
  virtual void unknown_8();
  virtual void unknown_9();
  virtual void unknown_10();
  virtual void unknown_11();
  virtual void cancelWheelie(); // 8057dc40
  virtual bool checkWheelie(); // 80589744
  virtual int updateTurn(); // 8057a8b4
  virtual int updateVehicleSpeed(); // 8057ab68
  virtual int updateUpsWhileAirborne(); // 8057d888
  virtual int updateVehicleRotationVector(float turn); // 8057cf0c
  virtual float getWheelieSoftSpeedLimitBonus(); // 8057c3c8
  virtual int updateWheelie(); // 8058758c
  virtual void unknown_19();
  virtual bool canHop(); // 8057da18
  virtual int hop(); // 8057da5c
  virtual int updateMtCharge(); // 8057ee50
  virtual void unknown_23();
  float speedMultiplier; // 50cc: public 0.8, 100cc: public 0.9, 150cc: public 1.0
  float baseSpeed;
  float softSpeedLimit;
  float unknown_0x1c;
  float vehicleSpeed;
  float lastSpeed;
  float unknown_0x28;
  float hardSpeedLimit;
  float acceleration;
  float speedDragMultiplier;
  Vec3 smoothedUp;
  Vec3 up;
  Vec3 landingDir;
  Vec3 dir;
  Vec3 lastDir;
  Vec3 vel1Dir;
  Vec3 unknown_0x80;
  Vec3 dirDiff;
  bool hasLandingDir;
  u8 unknown_0x99[0x9c-0x99];
  float outsideDriftAngle;
  float landingAngle;
  Vec3 outsideDriftLastDir;
  float speedRatioCapped; // to 1
  float speedRatio;
  float kclSpeedFactor;
  float kclRotFactor;
  float kclWheelSpeedFactor;
  float kclWheelRotFactor;
  s16 flooorCollisionCount;
  u8 unknown_0xa[2];
  int hopStickX;
  int hopFrame;
  Vec3 hopUp;
  Vec3 hopDir;
  int slipstreamCharge;
  float unknown_0xf0;
  float divingRot;
  float boostRot;
  s16 driftState; // 1: public charging mt, 2: public mt charged, 3: public smt charged
  s16 mtCharge;
  s16 smtCharge;
  s16 mtBoost;
  float outsideDriftBonus;
  PlayerBoost boost;
  s16 zipperBoost;
  s16 zipperBoostMax;
  u8 unknown_0x130[0x148-0x130];
  s16 offroadInvincibilityFrames;
  u16 unknown_0x14a;
  u16 ssmtCharge;
  u8 unknown_0x14e[0x158-0x14e];
  float effectiveTurn;
  float conservedTurn;
  float unknown_0x164;
  Vec3 scale;
  float unknown_0x170;
  float someScale;
  float shockSpeedMultiplier;
  float megaScale;
  u8 unknown_0x180[0x188-0x180];
  s16 mushroomBoost2; // 0x188, another mushroom boost timer
  s16 starTimer; // 0x18A, timer for Star
  s16 shockTimer; // 0x18C, used when shocked by KC Zappers, TC, or Shock
  s16 blooperCharacterInk; // 0x18E, timer for ink on player
  u8 field_0x190; // set to 1 when the blooper state is applied
  u8 unknown_0x191;
  s16 crushTimer; // 0x192, timer for being crushed by Thwomp & Mega
  s16 megaTimer; // 0x194, timer for Mega mushroom
  u8 unknown_0x196[0x1b0-0x196];
  float jumpPadMinSpeed;
  float jumpPadMaxSpeed;
  JumpPadProperties jumpPadProperties;
  s16 rampBoost;
  u8 unknown_0x1c6[0x228-0x1c6];
  float hopVelY;
  float hopPosY;
  float hopGravity;
  u8 unknown_0x234[0x248-0x234];
  u32 drivingDirection; // 0: public forwards, 1: public braking, 2: public waiting on the backwards counter, 3: public backwards
  u16 backwardsAllowCounter;
  u8 unknown_0x24e[2];
  u32 specialFloor; // bit flags:
    /*
      0 boost panel
      1 boost ramp
      2 jump pad
    */
  u8 unknown_0x254[0x258-0x254];
  PlayerTrick *trick;
  PlayerZipper *zipper;
  u8 unknown_0x260[0x288-0x260];
  float rawTurn;
  float unknown_0x28c;
  s16 ghostVanishTimer;
  u8 unknown_0x292[2];
}; // Total size 0x294

extern float hardSpeedLimit;
extern float bulletBillSpeed;
extern float starSpeed;
extern float megaMushroomTCSpeed;

class PlayerSub10Remote : public PlayerSub10 {
public:
  // vtable 808b5d90
}; // Total size 0x294

class PlayerSub10RealLocal : public PlayerSub10 {
public:
  // vtable 808b5e78
}; // Total size 0x294

class PlayerSub10Bike : public PlayerSub10 {
public:
  PlayerSub10Bike(); // 80587b30
  // vtable 808b5ee8
  virtual ~PlayerSub10Bike(); // 80589704
  virtual int setTurnParams(); // 80587c54
  virtual void cancelWheelie(); // 80588b30
  virtual bool checkWheelie(); // 80588fe0
  virtual int updateVehicleRotationVector(float turn); // 80587d68
  virtual float getWheelieSoftSpeedLimitBonus(); // 80588324
  virtual int updateWheelie(); // 80587d64
  virtual int updateMtCharge(); // 80588888
  virtual int startWheelie(); // 80588350
  virtual void cancelWheelie2(); // 805883c4
  virtual void unknown_0x26();
  float leanRot;
  float leanRotCap;
  float leanRotInc;
  float wheelieRot;
  float maxWheelieRot;
  u32 wheelieTimer;
  u8 field_0x2AC; // could be a wheelie flag (0 = not in wheelie, 1 = in wheelie), set to 1 when starting wheelie and 0 when ending wheelie?
  u8 unknown_0x2ad[0x2b4-0x2ad];
  u16 wheelietimer2; // from what i know the same as wheelieTimer, but stored as a ushort
  u16 wheelieCooldown;
  u8 unknown_0x254[0x2c0-0x2b8];
  void *turnParams;
}; // Total size 0x2c4

class PlayerSub10BikeRemote : public PlayerSub10Bike {
public:
  // vtable 808b5d18
}; // Total size 0x2c4

class PlayerSub10BikeRealLocal : public PlayerSub10Bike {
public:
  // vtable 808b5e00
}; // Total size 0x2c4

class PlayerSub14 {
public:
  PlayerSub14(); // 805672cc
  PlayerPointers *playerPointers;
  u8 unknown_0x4[0xc-0x4];
  virtual void func_vtable1();
  virtual void Update(DamageType newDamage, UnkType r5, int r6, u32 r7);
  virtual void unknown_vtable(); // 0x808B5008
  float unknown_0x10[3];
  DamageType currentDamage;
  u8 unknown_0x20[0x100-0x20];
}; // Total size 0x100

class PlayerSub18 {
public:
  PlayerSub18(); // 8056e56c
  void processMovingRoad(CollisionData *collisionData, UnkType *kclFlags); // 8056e930
  UnkType processFloor(CollisionData *collisionData, Hitbox *hitbox, void *unk, UnkType *kclFlags, bool allowBoostPanels); // 8056ea04
  UnkType checkPlayerCollision(PlayerPointers **otherPlayer); // 8056f7f0
  UnkType checkItemCollision(); // 8057257c
  UnkType updateCollisions(); // 80572c20
  int handleNoopCollision(); // 80573170
  int handleBananaCollision(); // 80573178
  int handleShellCollision(); // 80573190
  int handleBlueShellCollision(); // 805731b0
  int handleBombCollision(); // 805731c8
  int handleMushroomCollision(); // 805731e0
  int handleStarCollision(); // 80573224
  int handleFibCollision(); // 8057325c
  UnkType activeOob(int unk0, int unk1, int unk2, int unk3); // 80573b00
  UnkType updateRespawn(); // 80573ed4
  UnkType updateCollisionsInner(float unk0, float unk1, u32 playerIdx, PlayerPhysics *playerPhysics, UnkType *collisionGroup, Quat *rotation, Vec3 *scale, bool enableHwg, Vec3 *unk2); // 805b6724
  // vtable 808b56a8
  virtual void processVehicleBodyCollision(CollisionData *collisionData, Hitbox *hitbox, void *unk, UnkType *kclFlags); // 8056e764
  virtual void processWheelCollision(CollisionData *collisionData, Hitbox *hitbox, void *unk, UnkType *kclFlags); // 8056e8d4
  virtual ~PlayerSub18(); // 80573ff0
  PlayerPointers *playerPointers;
  u8 unknown_0x8[0x2c-0x8];
  u32 surfaceProperties; // bit flags:
    /*
       0: public wall
       1: public solid oob
       4: public boost ramp
       6: public offroad
       8: public boost panel or ramp
      11: public trickable
    */
  u8 unknown_0x30[0x48-0x30];
  s16 preRespawnTimer;
  s16 solidOobTimer;
  u8 unknown_0x4c[0x74-0x4c];
}; // Total size 0x74

class PlayerSub1c {
public:
  PlayerSub1c(PlayerParams *playerParams); // 805943b4
  UnkType updateFromInput(); // 8059487c
  UnkType computeStartBoost(); // 805959d4
  UnkType applyStartBoost(int startBoostIdx); // 80595af8
  UnkType updateCollisions(); // 80594bd4
  // vtable 808b6534
  virtual void unknown_vtable();
  u32 bitfield0; // bit flags:
    /*
       0 accelerate
       1 brake
       2 drift input
       3 drift (manual)
       4 oob, before being respawned
       5 wall 3 collision
       6 wall collision
       7 first frame of hop
       8 first frame of acceleration
       9 first frame of groundtime
      10 floor collision with the vehicle body
      11 floor collision with any wheel
      12 floor collision with all wheels
      13 stick left
      15 airtime > 20
      16 sticky road
      18 ground
      19 hop
      20 boost
      24 stick right
      26 mushroom boost
      27 charging a slipstream
      28 drift (auto)
      29 wheelie
      30 jump pad enabled
      31 ramp boost
    */
  u32 bitfield1; // bit flags:
    /*
       0 hit by an item or an object
       1 first frame of respawn
       3 first frame of cannon
       4 in cannon
       5 first frame of trick
       6 in a trick
       7 offroad invincibility
      10 over a zipper
      13 zipper boost
      15 zipper trick
      20 mt boost
      22 in a trick
      30 on a trickable surface
      31 in a star
    */
  u32 bitfield2; // bit flags:
    /*
       0 charging a slipstream
       1 in a slipstream
       4 wheelie rotation
       7 shocked
      15 in a mega
      16 crushed
      18 stopped
      19 vanished
      27 in a bullet
      28 ink applied
      29 has a tc
    */
  u32 bitfield3; // bit flags:
    /*
       5 hwg (horizontal wall glitch)
       8 start boost charge
    */
  u32 bitfield4; // bit flags:
    /*
       0 cpu-controlled
       1 real local
       2 local
       3 remote
       4 automatic drift
       6 ghost
    */
  int *unknown_0x18;
  u32 airtime;
  u8 unknown_0x20[0x28-0x20];
  Vec3 floorNor;
  Vec3 unknown_0x34;
  u8 unknown_0x40[0x6b-0x40];
  s32 hwgTimer;
  u8 unknown_0x70[0x74-0x70];
  u32 boostRampType;
  u32 jumpPadType;
  u8 unknown_0x7c[0x7f-0x7c];
  u32 cnptId;
  u8 unknown_0x84[0x88-0x84];
  float stickX;
  float stickY;
  u8 unknown_0x90[0x9c-0x90];
  float startBoostCharge;
  s32 startBoostIdx; // -1 when burning out
  u8 unknown_0xa4[2];
  s16 trickableTimer;
  u8 unknown_0xa8[0xc0-0xa8];
}; // Total size 0xc0

class PlayerSub {
public:
  PlayerSub(PlayerParams *playerParams); // 80595d48
  PlayerPointers *playerPointers;
  int *unknown_0x4;
  int *unknown_0x8;
  // vtable 808b659c
  virtual void unknown_vtable();
  PlayerSub10 *playerSub10;
  PlayerSub14 *playerSub14;
  PlayerSub18 *playerSub18; // contains vehicle body collision data
  PlayerSub1c *playerSub1c; // contains input-related state
  u8 unknown_0x20[0x9c-0x20];
}; // Total size 0x9c

class PlayerPhysics {
private:
  PlayerPhysics(); // 805b4b54
public:
  //PlayerPhysics(); // 805b4af8
  UnkType initInertia0(); // 805b4dc4
  UnkType initInertia1(); // 805b4e84
  UnkType reset(); // 805b4d24
  UnkType update(float one, float maxSpeed, bool unknown); // 805b5170
  UnkType applyWheelSuspension(Vec3 *unk0, Vec3 *normalAcceleration, Vec3 *unk1, bool unk2); // 805b6150
  // vtable 808b7314
  virtual ~PlayerPhysics(); // 8059f678
  virtual UnkType stabilize(); // 805b5b68
  virtual int unknown_0x2();
  Mat34 inertiaTensor;
  Mat34 invInertiaTensor;
  float rotationSpeed;
  Vec3 position;
  Vec3 speed0; // speed caused by gravity and normal force
  Vec3 unknown_0x80;
  Vec3 unknown_0x8c;
  Vec3 unknown_0x98;
  Vec3 rotVec0; // contains drift, diving and wheel rotation
  Vec3 speed2;
  Vec3 rotVec1;
  Vec3 speed3;
  Vec3 speed; // sum of vel0, vel1, vel2 and vel3
  float speedNorm;
  Vec3 rotVec2;
  Quat mainRot;
  Quat fullRot; // also includes specialRot
  Vec3 normalAcceleration;
  Vec3 normalRotVec;
  Quat specialRot; // e.g. trick
  Quat unknown_0x138;
  float gravity; // 1.3f most of the time
  Vec3 engineSpeed; // speed caused by the vehicle engine
  u8 unknown_0x158[0x178-0x158];
  float stabilizationFactor;
  Vec3 speed1Adj;
  u8 unknown_0x180[0x1b4-0x188];
}; // Total size 0x1b4

class PlayerPhysicsBike : public PlayerPhysics {
public:
  virtual ~PlayerPhysicsBike(); // 805b66e4
  virtual UnkType stabilize(); // 805b6448
  // vtable 808b7300
}; // Total size 0x1b4

class CollisionData {
public:
  CollisionData(); // 805b821c
  u32 types; // bit flags:
    /*
      0 floor
      1 wall
      2 invisible wall
      3 trickable
      6 wall 3
    */
  Vec3 nor;
  Vec3 floorNor;
  Vec3 unknown_0x1c;
  Vec3 unknown_0x28;
  Vec3 vel;
  Vec3 relPos;
  Vec3 movement;
  Vec3 unknown_0x58;
  float speedFactor;
  float rotFactor;
  u32 closestFloorFlags;
  u32 closestFloorSettings;
  u8 unknown_0x74[0x7c-0x74];
  u32 intensity;
  u8 unknown_0x80[0x84-0x80];
}; // Total size 0x84

class Hitbox {
public:
  Hitbox(); // 805b7f48
  UnkType reset(); // 808b7f84
  UnkType update(float scale0, float scale1, Vec3 *scale, Quat *rotation, Vec3 *centerPosition); // 805b7fbc
  void *bspHitbox; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  float radius;
  s32 unknown_0x8;
  Vec3 position;
  Vec3 lastPosition;
  Vec3 unknown_0x24;
}; // Total size 0x30

class HitboxGroup {
public:
  HitboxGroup(); // 805b82bc
  HitboxGroup(UnkType *hitboxes); // 805b84c0
  HitboxGroup(float radius, Vec3 *position); // 805b875c
  UnkType updateBoundingRadius(); // 805b883c
  UnkType reset(); // 805b8330
  u16 hitboxCount;
  // padding 0x2 - 0x3
  float boundingRadius;
  CollisionData collisionData;
  Hitbox *hitboxes;
  u32 unknown_0x90;
  float unknown_0x94;
  float unknown_0x98;
}; // Total size 0x9c

class PlayerPhysicsHolder {
public:
  PlayerPhysicsHolder(bool isBike, StatsAndBsp *statsAndBsp, void *arg_r5, u32 wheelCount); // 805a04a0
  UnkType init(bool isBike); // 8059f5bc
  UnkType resetQuaternions(); // 805a0410
  // vtable 808b69e8
  virtual void unknown_vtable();
  PlayerPhysics *playerPhysics;
  HitboxGroup *hitboxGroup;
  u8 unknown_0xc[0x18-0xc];
  Vec3 position;
  Quat unknown_0x24[6];
  u8 unknown_0x84[0x9c-0x84];
  Mat34 unknown_0x9c;
  Vec3 unknown_0xcc[3];
  Vec3 speed;
  float unknown_0xfc;
}; // Total size 0x100

class Object3D {
public:
  Object3D(PlayerParams *playerParams, u32 unknown); // 80592848
  u8 unknown_0x0[0xc-0x0];
  // vtable 808b6450
  virtual void unknown_vtable();
  Vec3 unknown_0x10;
  Mat34 unknown_0x1c;
  Mat34 unknown_0x4c;
  u8 unknown_0x7c[0x8c-0x7c];
}; // Total size 0x8c

class PlayerGraphics : public Object3D { // tentative name
public:
  UnkType getWheelMatrixBike(Mat34 *wheelMatrix, u32 wheelIdx); // 8056dd54
  u8 unknown_0x8c[0x90-0x8c];
  PlayerPhysicsHolder *playerPhysicsHolder;
  float unknown_0x94;
  Vec3 unknown_0x98;
  u8 unknown_0xa4[0xa8-0xa4];
  Mat34 unknown_0xa8;
  Mat34 unknown_0xd8;
  u8 unknown_0x108[0x168-0x108];
  Mat34 unknown_0x168;
  Mat34 unknown_0x198;
  u8 unknown_0x1c8[0x230-0x1c8];
  float wheelForwardRotationSpeed; // from KartPartsDispParam/BikePartsDispParam
  float wheelBackwardRotationSpeed; // same
  u8 unknown_0x238[0x360-0x238];
}; // Total size 0x360

class DriverParams{
public:
  u32 wheelCount;
  VehicleType type;
  u32 weightClass;
  float unknown_0xC;
  float weight;
  float bumpDeviationLevel;
  float baseSpeed;
  float handlingSpeedMultiplier;
  float tilt;
  float standard_acceleration_as[4];
  float standard_acceleration_ts[3];
  float drift_acceleration_as[2];
  float drift_acceleration_ts[1];
  float manualHandling;
  float autoHandling;
  float handlingReactivity;
  float manualDrift;
  float automaticDrift;
  float driftReactivity;
  float targetAngle;
  float unknown_0x68;
  u32 mt;
  float speedFactors[32];
  float handlingFactors[32];
  float rotatingItemObjParams[4];
  float vertical_tilt;
  float megaScale;
  float unknown_0x188;

}; //total size 0x18c

class KartParams{
public:
  u32 wheelCount;
  VehicleType type;
  u32 weightClass;
  float unknown_0xC;
  float weight;
  float bumpDeviationLevel;
  float baseSpeed;
  float handlingSpeedMultiplier;
  float tilt;
  float standard_acceleration_as[4];
  float standard_acceleration_ts[3];
  float drift_acceleration_as[2];
  float drift_acceleration_ts[1];
  float manualHandling;
  float autoHandling;
  float handlingReactivity;
  float manualDrift;
  float automaticDrift;
  float driftReactivity;
  float targetAngle;
  float unknown_0x68;
  u32 mt;
  float speedFactors[32];
  float handlingFactors[32];
  float rotatingItemObjParams[4];
  float vertical_tilt;
  float megaScale;
  float unknown_0x188;

}; //total size 0x18c

extern DriverParams *driverParams;
extern KartParams *kartParams;


class PlayerStats{
public:
  u32 wheelCount;
  VehicleType type;
  u32 weightClass;
  float unknown_0xC;
  float weight;
  float bumpDeviationLevel;
  float baseSpeed;
  float handlingSpeedMultiplier;
  float tilt;
  float standard_acceleration_as[4];
  float standard_acceleration_ts[3];
  float drift_acceleration_as[2];
  float drift_acceleration_ts[1];
  float manualHandling;
  float autoHandling;
  float handlingReactivity;
  float manualDrift;
  float automaticDrift;
  float driftReactivity;
  float targetAngle;
  float unknown_0x68;
  u32 mt;
  float speedFactors[32];
  float handlingFactors[32];
  float rotatingItemObjParams[4];
  float vertical_tilt;
  float megaScale;
  float unknown_0x188;

}; //total size 0x18c

PlayerStats *Compute(VehicleId vehicleId, CharacterId characterId);

class StatsAndBsp {
public:
  PlayerStats *stats; // http://wiki.tockdom.com/wiki/KartParam.bin
  UnkType *bsp; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
}; // Total size 0x8

class GpStats {
public:
  bool startBoostSuccessful;
  u8 unknown_0x1[0x4-0x1];
  u32 mtCount;
  u32 offroadFrames;
  u32 unknown_0xC;
  u32 objectCollisionCount;
  u32 oobCount;
  u16 unknown_0x18;
  u8 unknown_0x1a[2];
}; // Total size 0x1c

class PlayerParams {
public:
  PlayerParams(u32 playerIdx, VehicleId vehicle, CharacterId character, bool isBike, StatsAndBsp *statsAndBsp,
               void *unknown, UnkType *kartDriverDispParams, UnkType *kartPartsDispParams,
               UnkType *bikePartsDispParams, UnkType *driverDispParams); // 80592fc0
  u32 isBike;
  VehicleId vehicle;
  CharacterId character;
  u16 wheelCount0;
  u16 wheelCount1;
  u8 playerIdx;
  u8 unknown_0x11[2];
  StatsAndBsp *statsAndBsp;
  int *unknown_0x18;
  UnkType *kartDriverDispParams;
  UnkType *kartPartsDispParams; // http://wiki.tockdom.com/wiki/KartPartsDispParam.bin
  UnkType *bikePartsDispParams; // http://wiki.tockdom.com/wiki/BikePartsDispParam.bin
  UnkType *driverDispParams;
  float wheelCountRecip;
  float wheelCountPlusOneRecip; // 1.0f / (wheelCount + 1.0f)
  GpStats *gpStats;
  u8 unknown_0x38[0x3C-0x38];
}; // Total size 0x3c

class WheelPhysics {
public:
  WheelPhysics(u32 wheelIdx, u32 bspWheelIdx); // 8059940c
  UnkType initHitboxGroup(); // 80599470
  UnkType realign(Vec3 *bottomDirection, Vec3 *unknown); // 80599ad0
  PlayerPointers *playerPointers;
  int *unknown_0x4;
  int *unknown_0x8;
  // vtable 808b66a4
  virtual void unknown_vtable();
  u32 wheelIdx;
  u32 bspWheelIdx;
  void *bspWheel; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  HitboxGroup *hitboxGroup;
  Vec3 position;
  Vec3 unknown_0x2c;
  Vec3 lastSpeed;
  float posY;
  Vec3 unknown_0x48[4];
  Vec3 topmostPosition;
}; // Total size 0x84

class WheelPhysicsHolder {
public:
  WheelPhysicsHolder(u32 wheelIdx, bool xMirroredKart, u32 bspWheelIdx); // 80599ed4
  UnkType update(float unknown, Vec3 *gravity, Mat34 *wheelMat); // 8059a278
  UnkType applySuspensions(Vec3 *forwardDirection, Vec3 *unknown); // 8059a574
  PlayerPointers *playerPointers;
  u8 unknown_0x4[0xc-0x4];
  // vtable 808b66b0
  void *bspWheel; // http://wiki.tockdom.com/wiki/BSP_(File_Format)
  WheelPhysics *wheelPhysics;
  u32 xMirroredKart;
  u32 bspWheelIdx;
  u32 wheelIdx;
  Vec3 topmostPosition;
  float slackY;
  u8 unknown_0x34[0x40-0x34];
  Vec3 bottomDirection;
}; // Total size 0x48

class Suspensions : public Object3D {
public:
  Suspensions(PlayerParams *playerParams); // 80598b08
  UnkType init(); // 80598bd4
  // vtable 808b6640
  u8 unknown_0x8c[0x90-0x8c];
  WheelPhysicsHolder *wheelPhysicsHolder;
}; // Total size 0x94

class Wheels : public Object3D {
public:
  Wheels(PlayerParams *playerParams, bool xMirroredKart, u32 bspWheelIdx); // 8059aa44
  // vtable 808b67e0
  u8 unknown_0x8c[0x90-0x8c];
  u32 xMirroredKart;
  u32 bspWheelIdx;
  WheelPhysics *wheelPhysics;
  float unknown_0x9c;
}; // Total size 0xa0

class WheelsFront : public Wheels {
public:
  // vtable 808b6798
  u8 unknown_0xa0[0xd0-0xa0];
}; // Total size 0xd0

class PlayerItemPoint {
public:
  u8 ITPT;
  u8 unknown_0x1[3];
  Vec3 unknown_0x4;
};// Total Size 0x10

class PlayerSound {
public:
    // vtable 0x808c8928
    virtual void unknown_vtable();
    u8 unknown_0x0[0x5c-0x4];
    nw4r::snd::SoundArchivePlayer *brstmData;
    u8 unknown_0x60[0xdb-0x60];
    u8 currentLap;
    u8 unknown_0xdc[0xf0-0xdc];
    u16 kclFlag;
    u16 variant;
    u8 unknown_0xF4[0xfc-0xf4];
};  // Total size 0xfc

class GFX44;

class PlayerPointers {
public:
  // all these methods use a double reference to PlayerPointers
  UnkType *getBikePartsDispParams(); // 8059091c
  UnkType *getBsp(); // 80590888
  UnkType *getControllerHolder();
  UnkType *getBspWheel(u32 bspWheelIdx); // 805908b4
  UnkType *getKartDriverDispParams(); // 805908e4
  PlayerGraphics *getPlayerGraphics(); // 8059069c
  u8 getPlayerIdx(); // 80590a5c
  PlayerPhysics *getPlayerPhysics(); // 805903cc
  PlayerPhysicsHolder *getPlayerPhysicsHolder(); // 805903ac
  HitboxGroup *getPlayerPhysicsHolderHitboxGroup(); // 805907d8
  Vec3 *getPlayerPosition(); // 8059020c
  PlayerStats *getPlayerStats(); // 80590874
  PlayerSub *getPlayerSubWeird(); // 805908d8
  PlayerSub *getPlayerSub(); // 80590764
  PlayerSub10 *getPlayerSub10(); // 8059077c
  PlayerSub14 *getPlayerSub14(); // 80590d20
  PlayerSub18 *getPlayerSub18(); // 8059084c
  Vec3 *getScale(); // 805914bc
  Vec3 *getSpeed(); // 80590d08
  Vec3 *getSpeedRatioCapped(); // 80590dc0
  VehicleType getVehicleType(); // 80590a10
  Suspensions *getSuspensions(u32 wheelIdx); // 805906b4
  Wheels *getWheels(u32 wheelIdx); // 805906dc
  u16 getWheelCount0(); // 805902dc
  u16 getWheelCount1(); // 805902ec
  WheelPhysics *getWheelPhysics(u32 wheelIdx); // 80590734
  CollisionData *getWheelPhysicsCollisionData(u32 wheelIdx); // 80590834
  WheelPhysicsHolder *getWheelPhysicsHolder(u32 wheelIdx); // 80590704
  bool isBike(); // 80590a6c
  bool isCpu(); // 80590664
  UnkType setPlayerPosition(Vec3 *position); // 80590238
  UnkType setPlayerRotation(Quat *rotation); // 80590288
  PlayerParams *params;
  PlayerSub1c *playerSub1c;
  PlayerGraphics *playerGraphics;
  Suspensions **suspensions;
  Wheels **wheels;
  PlayerModel *mode;
  PlayerSub *playerSub;
  PlayerSound *playerSound;
  int *unknown_0x20;
  int *unknown_0x24;
  PlayerSub10 *playerSub10;
  PlayerSub14 *playerSub14;
  PlayerSub18 *playerSub18;
  int *unknown_0x34[(0x44-0x34)/4];
  GFX44 *gfx44;
  int *unknown_0x48[(0x64-0x48)/4];

}; // Total size 0x64

class Player {
private:
  Player(u32 idx, VehicleId vehicle, CharacterId character, bool isBike, StatsAndBsp *statsAndBsp, void *unknown,
         UnkType *kartDriverDispParams, UnkType *kartPartsDispParams, UnkType
         *bikePartsDispParams, UnkType *driverDispParams); // 8058ddbc

public:
  Player(u32 idx, VehicleId vehicle, CharacterId character, bool isBike); // 8058f5b4
  UnkType update(); // 8058eeb4
  UnkType update2(); // 8058eebc
  UnkType initWheels(); // 8058ea0c
  bool IsLocal(); //80590650
  PlayerPointers *playerPointers; // a pointer to the inline instance at 0x1c
  int *unknown_0x4;
  int *unknown_0x8;
  // vtable 0x808b63ec
  virtual void unknown_vtable();
  PlayerSub *playerSub;
  PlayerParams *params;
  PlayerModel *model;
  PlayerPointers pointers;
}; // Total size 0x80

class PlayerBike : public Player {
public:
  UnkType initWheels(); // 8058f2e8
  // vtable 0x808b63d0
}; // Total size 0x80

class PlayerHolderSub {
public:
  // vtable 802a2b48
  virtual void unknown_0x0();
  u8 unknown_0x4[0x10-0x4];
}; // Total size 0x10

class PlayerHolder : public PlayerHolderSub { // vtable override 808b6408
public:
  static PlayerHolder * sInstance; // 809c18f8
  static PlayerHolder * getStaticInstance(); // 8058faa8
  static void destroyStaticInstance(); // 8058faf8
  PlayerHolder(); // 8058fb2c
  Player *PlayerHolderGetPlayer(u32 idx); // 80590100
  void update(); // 8058ffe8
  PlayerHolderSub secondPHS;
  Player **players;
  u8 playerCount;
  // padding 0x25 - 0x27
  u32 someBitfield; // some bits are sets depending on the played track
  u8 *array0; // contains 1 element per player, set to the player index divided by 4
  u8 *array1; // contains 1 element per player, set to the player index modulo 4
  u8 unknown_0x34[0x38-0x34];
}; // Total size 0x38

extern PlayerHolder *playerHolder;

extern "C"{
  bool ApplyTransparency(ComboIDs *comboIDs, GFX44 *gfx44, bool isGhost, u8 playerId);
}