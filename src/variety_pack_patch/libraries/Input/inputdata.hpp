/*
InputData is the class that handles all controller inputs
Contributors:
  Seeky (main documentation)
  SwareJonge
  _tZ
*/

#pragma once
#include <common.hpp>
#include <Kamek/kamek.hpp>

enum UniversalButtons{
  BUTTON_NONE             = 0,
  BUTTON_DPAD_LEFT        = 1 << 0,
  BUTTON_DPAD_RIGHT       = 1 << 1,
  BUTTON_DPAD_DOWN        = 1 << 2,
  BUTTON_DPAD_UP          = 1 << 3,
  BUTTON_A                = 1 << 4,
  BUTTON_B                = 1 << 5,
  BUTTON_X                = 1 << 6,
  BUTTON_Y                = 1 << 7,
  BUTTON_MINUS            = 1 << 8,
  BUTTON_PLUS             = 1 << 9,
  BUTTON_HOME             = 1 << 10,
  BUTTON_1                = 1 << 11,
  BUTTON_2                = 1 << 12,
  BUTTON_L                = 1 << 13,
  BUTTON_R                = 1 << 14,
  BUTTON_C                = 1 << 15,
  BUTTON_Z                = 1 << 16,
  BUTTON_ZL               = 1 << 17,
  C_STICK_UP_EIGHT        = 1 << 18,
  C_STICK_UPRIGHT_EIGHT   = 1 << 19,
  C_STICK_RIGHT_EIGHT     = 1 << 20,
  C_STICK_DOWNRIGHT_EIGHT = 1 << 21,
  C_STICK_DOWN_EIGHT      = 1 << 22,
  C_STICK_DOWNLEFT_EIGHT  = 1 << 23,
  C_STICK_LEFT_EIGHT      = 1 << 24,
  C_STICK_UPLEFT_EIGHT    = 1 << 25,
};

typedef enum Buttons{
  WHEEL_DPAD_LEFT=0x1,
  WHEEL_DPAD_RIGHT=0x2,
  WHEEL_DPAD_DOWN=0x4,
  WHEEL_DPAD_UP=0x8,
  WHEEL_A=0x800,
  WHEEL_B=0x400,
  WHEEL_MINUS=0x1000,
  WHEEL_PLUS=0x10,
  WHEEL_HOME=0x8000,
  WHEEL_1=0x200,
  WHEEL_2=0x100,

  NUNCHUCK_DPAD_LEFT=0x1,
  NUNCHUCK_DPAD_RIGHT=0x2,
  NUNCHUCK_DPAD_DOWN=0x4,
  NUNCHUCK_DPAD_UP=0x8,
  NUNCHUCK_A=0x800,
  NUNCHUCK_B=0x400,
  NUNCHUCK_MINUS=0x1000,
  NUNCHUCK_PLUS=0x10,
  NUNCHUCK_HOME=0x8000,
  NUNCHUCK_1=0x200,
  NUNCHUCK_2=0x100,
  NUNCHUCK_C=0x4000,
  NUNCHUCK_Z=0x2000,

  CLASSIC_DPAD_LEFT=0x2,
  CLASSIC_DPAD_RIGHT=0x2000,
  CLASSIC_DPAD_DOWN=0x4000,
  CLASSIC_DPAD_UP=0x1,
  CLASSIC_A=0x10,
  CLASSIC_B=0x40,
  CLASSIC_X=0x8,
  CLASSIC_Y=0x20,
  CLASSIC_MINUS=0x1000,
  CLASSIC_PLUS=0x40,
  CLASSIC_HOME=0x800,
  CLASSIC_L=0x2000,
  CLASSIC_R=0x200,
  CLASSIC_ZL=0x80,
  CLASSIC_Z=0x4,

  GCN_DPAD_LEFT=0x1,
  GCN_DPAD_RIGHT=0x2,
  GCN_DPAD_DOWN=0x4,
  GCN_DPAD_UP=0x8,
  GCN_A=0x100,
  GCN_B=0x200,
  GCN_X=0x400,
  GCN_Y=0x800,
  GCN_Z=0x10,
  GCN_START=0x1000,
  GCN_L=0x40,
  GCN_R=0x20
};


class InputDataSub3{
  virtual void func_vtable();
  u8 unknown_0x4[0x90-0x4];
};//total size 0x80 


class InputDataSub6{
  u8 unknown_0x0[0xa8-0x0];
};//total size 0xa8



class InputState {
public:
  virtual void unknown_vtable();
  // vtable 808b2f2c
  u16 buttonActions; // bit flags:
    /* 
      0x1 = accelerate
      0x2 = brake + reverse (used for SSMT)
      0x4 = use item
      0x8 = hop + drift
      0x20 = rear-view camera
    */
  u16 buttonRaw; // bit flags, vary slightly by controller
  float stickX; // -1.0 to 1.0 //0x8
  float stickY; // -1.0 to 1.0 //0xC
  u8 quantisedStickX; // 0-14
  u8 quantisedStickY; // 0-14
  u8 motionControlFlick; // 1 up, 2 down, 3 left, 4 right; includes the first frame of d-pad presses
  u8 motionControlFlick2; // not sure what the difference is from the other one
  u8 unknown_0x14[0x18-0x14];
}; // Total size 0x18

class UIInputState {
public:
  virtual void unknown_vtable(); //0x808b2f20
  u16 buttonActions; //bit flags: //0x4
  /*
    0x1 = forward press
    0x2 = back press
    0x4 = start/+ press
    0x8 = up press
    0x10 = down press
    0x20 = left press
    0x40 = right press
    0x100 = x/Z
  */
  u16 rawButtons; //0x6
  u16 buttonRaw; // bit flags, vary slightly by controller //0x8
  float stickX; // -1.0 to 1.0 //0xC
  float stickY; // -1.0 to 1.0 //0x10
  u8 unknown_0x14[0x18-0x14]; //0x14
  u8 quantisedStickX; // 0-14 0x18
  u8 quantisedStickY; // 0-14 0x19
  u8 unknown_0x1A[0x34-0x1A];
}; //total size 0x34

class Controller{
public:
  virtual void func_vtable();
  InputState inputState;  //0x4
  UIInputState uiinputState; //0x1c
  u8 unknown_0x50;
  bool isDriftAuto;
  u8 unknown_0x52[2];
  u32 battery;
  u8 unknown_0x54[0x90-0x58];
}; //total size 0x90

struct KPADStatus {
  u8 unknown_0x0[0x10-0x0];
  float acc_value;
  float acc_speed;
  u8 unknown_0x18[0x74-0x18];
  float cStickHorizontal;
  float cStickVertical;
  u8 unknown_7C[0x84-0x7C];
}; //total size 0x84

struct WPADInfo {
  u32 dpd;
  u32 speaker;
  u32 attach;
  u32 lowBat;
  u32 nearempty;
  u8 battery;
  u8 led;
  u8 protocol;
  u8 firmware;
}; //total size 0x18

struct PADStatus {
  u16 buttons;
  s8 horizontalStickU8;
  s8 verticalStickU8; // -62 to 62
  s8 horizontalCStickU8;
  s8 verticalCStickU8; // -50 to 50
  u8 unknown_0x6[0xC-0x6];
}; //total size 0xC

class WiiController : Controller {
public:
  KPADStatus kpadStatus[16];
  u8 unknown_0x8d0[0x8d4-0x8d0];
  u32 channel;
  u32 type;
  u32 type2;
  WPADInfo wpadInfo;
  u8 unknown_0x8F8[0x900-0x8f8];
  u32 wpadType;
  u8 unknown_0x904[0x920-0x904];
};//total size 0x920 seems other controllers related

class GCNController : Controller {
public:
  PADStatus padStatus; //0x90
  u32 channel;
  float cStickHorizontal;
  float cStickVertical;
  u8 unknown_0xa8[0xb0-0xa8];
};//total size 0xb0 seems GCN related

class ControllerHolder {
public:
  ControllerHolder(); // 80520f64 - inlined in RealControllerHolder()
  virtual ~ControllerHolder(); // 805222b4
  virtual int unknown1(); // 80521198
  virtual int unknown2(); // 80521110
  virtual int unknown3();// 805226f4
  virtual int unknown4();// 8051ce84
  virtual int  unknown5();// 8051ce8c
  virtual int  unknown6();// 80520ebc
  // vtable 808b2dd8
  Controller *controller; //0x4
  Controller *controller2;
  Controller *controller3; //0xc
  u8 unknown_0x10[0x28-0x10];
  InputState inputStates[2]; // 0 is current frame, 1 is previous    0x28
  UIInputState uiinputStates[2]; //0 is current frame, 1 is previous 0x58
  u8 unknown_0xC0[0xd8-0xc0];
}; // Total size 0xd8

class RealControllerHolder : public ControllerHolder {
public:
  RealControllerHolder(); // 805220bc
  virtual ~RealControllerHolder(); // 805222f4
  virtual int  unknown1(); // 80521768
  virtual int unknown2(); // 80522708
  virtual int unknown4(); // 80522700
  virtual int unknown5(); // 805226f8
  virtual int unknown6(); // 80520ebc
  
  // vtable 808b2d90
  void * rkgInputBuffer; // 0x2774 byte buffer for storing a controller input section of an RKG file
  u8 unknown_0xdc[0xe8-0xdc];
  void * unknown_0xe8; // 0x1c class with constructor 80524ac4
}; // Total size 0xec

class VirtualControllerHolder : public ControllerHolder {
public:
  virtual ~VirtualControllerHolder(); // 8052279c
  virtual int unknown3(); // 805219ac
  
  // vtable 808b2db4
  u8 unknown_0xd8[0x180-0xd8];
}; // Total size 0x180




class InputData {
public:
  static InputData * sInstance; // 809bd70c
  static InputData * getStaticInstance(); // 8052313c
  static void destroyStaticInstance(); // 8052318c
  InputData(); // 805232f0
  virtual ~InputData(); // 805231dc
  // vtable 808b2fc8
  RealControllerHolder realControllerHolders[4]; // Stores inputs from a real controller at the same console
  VirtualControllerHolder virtualControllerHolders[12]; // Stores inputs for all the other players in a race (I think the ones with a matching realControllerHolder go unused)
  ControllerHolder controllerHolder;
  u32 unknown_0x168c;
  InputDataSub3 sub3;
  WiiController wiiControllers[4];
  GCNController gcnControllers[4];
  InputDataSub6 sub6s[4];
  u32 inputDatasub7_vt;
  u8 unknown_0x15b4[0x415c-0x4104];
}; // Total size 0x415c


extern "C"{
    void StoreCorrectInputDataSub(RealControllerHolder *realControllerHolder, void *inputDataSub, u32 r5);
}




extern InputData *inputData;


