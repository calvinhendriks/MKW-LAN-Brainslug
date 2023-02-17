#pragma once

#include <Kamek/kamek.hpp>

struct FileStats{
    u32 fileSize;
    u32 filePos;
};

class DVDCommandBlock{
public:
    s32 DVDReadPrio(DVDCommandBlock * fileInfo, void * buffer, u32 len, u32 offset, u32 prio);
    bool DVDClose(DVDCommandBlock * fileInfo);
    DVDCommandBlock *next;
    DVDCommandBlock *prev;
    u32 command;
    u32 state;
    u32 offset;
    u32 size;
    void *addr;
    u32 curTransferSize;
    u32 transferredSize;
    char gameName[4];
    char company[2];
    u8 diskNumber;
    u8 gameVersion;
    u8 streaming;
    u8 streamingBuffSize;
    u8 unknown_0x2e[2];
    u32 *address;
    u32 length;
    u32 unknown_0x38;
};
extern "C" {
    bool DVDOpen(const char * path, DVDCommandBlock * fileInfo);
    s32 DVDConvertPathToEntryNum(char *path);
    s32 DVDReadPrio(DVDCommandBlock * fileInfo, void * buffer, u32 len, u32 offset, u32 prio);
    bool DVDClose(DVDCommandBlock * fileInfo);
}