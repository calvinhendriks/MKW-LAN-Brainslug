/*
Random is the game's class used for RNG
Contributors:
    Kevin (main documentation)
*/

#pragma once
#include <Kamek/kamek.hpp>

class Random {
  virtual ~Random(); // 80555538
  Random(); // 80555464
  s32 next(); // 80555578
  s32 nextLimited(int limit); // 805555cc
  // vtable 808b42e0
  u8 unknown_0x4[0x18-0x4];
  // 0x4-17 is unknown
}; // Total size 0x18