
/*
ItemBehaviour is a struct containing various information about how an item should behave
Contributors:
  Seeky (main documentation)
  TheLordScruffy (object id field)
References:
  http://wiki.tockdom.com/wiki/Filesystem/rel/StaticR.rel#Item_behaviour_modifier
*/
#pragma once
#include <Kamek/kamek.hpp>

typedef enum ItemUseType {
  ITEMUSE_USE,
  ITEMUSE_FIRE,
  ITEMUSE_TAIL,
  ITEMUSE_CIRCLE
};

typedef struct ItemBehaviour {
  u8 unknkown_0x0;
  u8 unknkown_0x1;
  u8 padding[2]; // Ignored when copying to array
  u32 objectId; // see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items
  u32 numberOfItems;
  u32 unknown_0xc;
  u8 unknown_0x10;
  u8 padding2[3]; // Ignored when copying to array
  ItemUseType useType;
  void (*useFunction)(ItemHolderPlayer *itemHolderPlayer); // Item is draggable if this is null
}; // Total size 0x1c

void CopyItemBehaviourFromRelToTable(); // 807bcae0, copies individual structs from rodata into table
extern ItemBehaviour itemBehaviourTable[19]; // 809c36a0, index item id, see http://wiki.tockdom.com/wiki/List_of_Identifiers#Items