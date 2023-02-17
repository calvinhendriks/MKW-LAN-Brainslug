#pragma once
#include <Kamek/kamek.hpp>
#include <egg/egg.hpp>

class AudioManager;
class GXRModeObj;
class SceneManager;

struct Video{
    GXRModeObj *mode;
    u32 unknown[2];
};//total size 0xc
#define NAND_CODE_OK 0
#define NAND_CODE_BUSY -3
#define NAND_CODE_EXISTS -6
#define NAND_CODE_NOT_EXIST -12

#define NAND_PERM_READ 0x10
#define NAND_PERM_WRITE 0x20
#define NAND_PERM_READ_WRITE (NAND_PERM_READ | NAND_PERM_WRITE)

#define NAND_MODE_READ 1
#define NAND_MODE_WRITE 2
#define NAND_MODE_READ_WRITE (NAND_MODE_READ | NAND_MODE_WRITE)

enum {
    NAND_MAX_PATH = 64,
    NAND_MAX_NAME = 12,
};
struct NANDFileInfo{
    u8 unknown_0x0[0x90];
}; //total size 0x90





s32 NANDCreate( const char *filename, u8 permissions, u8 attributes);
s32 NANDRead(NANDFileInfo *info, void *buf, u32 length);
s32 NANDGetLength(NANDFileInfo *info, u32 *length);
s32 NANDOpen(const char *path, NANDFileInfo *info, u8 accType); //1 to read, 2 to write
s32 NANDClose(NANDFileInfo *info);
s32 NANDWrite(NANDFileInfo * fileInfo, void * buffer, u32 size);


s32 NANDSeek(NANDFileInfo *info, s32 offset, s32 whence);

s32 NANDGetHomeDir(char path[NAND_MAX_PATH]);



s32 NANDMove(const char *path, const char *destDir);




class RKSystem{
public:
    RKSystem(); //not a true ctor 800099cc
    virtual void func_vtable(); //80270bf0
    void *MEM1ArenaLo;
    void *MEM1ArenaHi;
    void *MEM2ArenaLo;
    void *MEM2ArenaHi;    
    u32 memorySize; //0x14
    EGG::ExpHeap *EGGRootMEM1; 
    EGG::ExpHeap *EGGRootMEM2; 
    EGG::ExpHeap *EGGRootDebug;
    EGG::ExpHeap *EGGSystem;  //0x18 
    void *heapSystem; //thread
    u32 unknown_0x2C; //just the start of mem1?
    u32 unknown_0x30; //idk
    u32 sysHeapSize;
    u32 gxFifoBufSize;
    GXRModeObj *mode;
    AudioManager *audioManager;
    Video *video;
    void *xfbManager;
    void *asyncDisplay;
    void *processMeter;
    SceneManager *sceneManager;
    EGG::ExpHeap *kpadWorkHeap;
    u32 unknown_0x5c;
    void *relLinkHeap;
    EGG::ExpHeap *heapSystem2; //the one I use 0x64
    u8 frameClock;
    u8 unknown_0x68;
    bool drawFrame;
    u8 unknown_0x6b[0x74-0x6b];
}; //total size 0x74
extern RKSystem rkSystem;

class SystemManager{
public: 
    void RipFromDiscAsync(char* path, void *heap, u32 allocDirection, u32 r7, u32 *buffer);
    char rippedPath[64]; //which file to rip from disc, such as ghost, savebanner.tpl etc...
    u8 unknown_0x40[0x58-0x40];
    u32 isWideScreen;
    u32 gameLanguage;
    u32 strapScreenLanguage;
    u32 isProgressiveScan;
    u32 isRGB60;
    u32 unknown_0x6c[2];
    float framerate;
    float frameratePAL50;
    float frameDuration;
    bool isNdev;
    u8 unknown_0x81[0x84-0x81];
    u32 regionId;
    u8 unknown_0x88[0X98-0X88];
    const char *ndevArg;
    u32 dolStart;
    u32 dolEnd;
    u32 dolSize;
    u8 unknown_0xa8[0x10Fc-0xa8];
    u16 latitude;
    u16 longitude;
}; //total size 0x1100

extern SystemManager *systemManager;

class ArchiveFile{
    u32 unknown_0x0;
    u32 arcHandle;
    void *filePtr;
    u32 size;
    void *heap;
    void *filePtrTmp;
    u32 sizeTmp;
    void *heapPtrTmp;
    u32 status;
};//total size 0x24


class ArchiveLoader{
    ArchiveLoader(); //0x8052a538 vtable 
    virtual void func_vtable(); //0x808b31c8
    u16 sourceCount;
    u8 unknown_0xA[0x10-0xA];
    char **archiveSuffix;
    UnkType *unknown_0x14;
    u32 *srcType;
};//total size 0x1c

class ArchiveLoadHandle{
    ArchiveLoader *archive;
    u8 unknown_0x4[0xc-0x4];
    char archivePath[40];
    u8 unknown_0x34[0x4c-0x34];
    void *heap;
    void *targetHeap;
}; //total size 0x54


class ArchiveRoot{
public:
    ArchiveRoot(); //0x8053fcec vtable 0x808b3bfc
    virtual void func_vtable();
    ArchiveLoader *archives[0x9];
    ArchiveLoader kartArchiveHandles[12];
    ArchiveLoader kartArchiveHandles2[12];
    ArchiveFile contentArchives[4];
    ArchiveLoadHandle loadHandles[7];
    void* taskThread;
    EGG::Disposer disposer;
    u8 unknown_0x598[0x61c-0x598];
}; //total size 0x61C

extern "C"{
    s32 ISFSOpen(char *path, u32 r4);
    s32 ISFSGetFileStats(u32 fd, FileStats *stats);
    s32 ISFSRead(s32 fd, void *buffer, u32 length);
    s32 ISFSClose(s32 fd);
    s32 ISFSCreateFile(char *path, u32 r4, u32 r5, u32 r6, u32 r7);
    s32 ISFSWrite(s32 fd, void *buffer, u32 length);
    u32 Util_RandInt(u32 low, u32 high);
}