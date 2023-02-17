#pragma once
#include <Kamek/kamek.hpp>
#include <Race/Item/itemholder.hpp>

/*
ItemSlotData is the class that handles data from ItemSlot.bin / ItemSlotTable.slt

Contributors:
  Seeky (main documentation)
  Star (checkSpawnTimer)
References:
  http://wiki.tockdom.com/wiki/Filesystem/Race/Common.szs/ItemSlot.bin
*/

typedef struct {
  u32 columns;
  short * data;
} ItemSlotTableHolder; // Total size 0x8

class ItemSlotData {
public:
  static ItemSlotData * sInstance(); // 809c3670
  static ItemSlotData * getStaticInstance(); // 807ba77c
  static void destroyStaticInstance(); // 807ba814

  virtual ~ItemSlotData(); // 807ba650
  s32 decideItem(s32 itemBoxSetting, s32 position, s32 r6, s32 r7, ItemHolderPlayer *itemHolderPlayer); // 807bb42c
  s32 decideRandomItem(s32 itemBoxSetting, s32 position, s32 r6, s32 r7); // 807bb8d0
  u8 * processTableAndIter(u8 * itemTable, ItemSlotTableHolder * tableHolder, bool updateItemsInWheek, bool isSpecialTable); // 807ba9d8, takes a pointer to a raw table in an item slot file, processes the values and writes them to the data field of the table holder, then returns the pointer to the start of the next table
  void scaleTableForPlayerCount(ItemSlotTableHolder * tableHolder); // 807bad20
  void resetLightningTimer(); // 807bb9bc
  void resetBlueShellTimer(); // 807bb9c8, goes unused
  void resetBlooperTimer(); // 807bb9d4
  void resetPowTimer(); // 807bb9e0
  void updateTimers(); // 807bb9ec, also responsible for setting them to their initial values on the first frame
  bool checkSpawnTimer(s32 objectId, s32 r5); // 807bb380
  // Always constructed inline
  
  // vtable 808d27b4
  u8 unknown_0x4[0x10-0x4];
  ItemSlotTableHolder playerChances;
  ItemSlotTableHolder cpuChances;
  ItemSlotTableHolder specialChances;
  s32 * itemsInWheel; // first s32 is number of items, followed by the item ids (visual only, doesn't stop you pulling other items)
  s32 * specialBoxItemsInWheel; // a series of lists in same structure as itemsInWheel, one for each column of the special table
  u8 unknown_0x30[0x34-0x30];
  u32 itemSpawnTimers[4]; // timers in frames for when an item can next be pulled. 0 = lightning, 1 = blue shell, 2 = blooper, 3 = pow
  u32 playerCount; // copied from the global variable by constructor, used to check when the player count changes online
}; // Total size 0x48

extern ItemSlotData *itemSlotData;