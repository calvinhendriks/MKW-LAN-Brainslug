#include <Kamek/kamek.hpp>

struct DVDHandle
{
	u32 _unk[12];
	u32 address, length;
	u32 _unk38;
};

struct loaderFunctions;

typedef void (*OSReport_t) (const char *str, ...);
typedef void (*OSFatal_t) (u32 *fg, u32 *bg, const char *str, ...);
typedef int (*DVDConvertPathToEntrynum_t) (const char *path);
typedef bool (*DVDFastOpen_t) (int entrynum, DVDHandle *handle);
typedef int (*DVDReadPrio_t) (DVDHandle *handle, void *buffer, int length, int offset, int unk);
typedef bool (*DVDClose_t) (DVDHandle *handle);
typedef int (*sprintf_t) (char *str, const char *format, ...);
typedef void* (*EGG_Heap_Alloc_t) (u32 size, s32 align, int heap);
typedef void (*EGG_Heap_Free_t) (void *buffer, int heap);


struct loaderFunctions {
	OSReport_t OSReport;
	OSFatal_t OSFatal;
	DVDConvertPathToEntrynum_t DVDConvertPathToEntrynum;
	DVDFastOpen_t DVDFastOpen;
	DVDReadPrio_t DVDReadPrio;
	DVDClose_t DVDClose;
	sprintf_t sprintf;
	EGG_Heap_Alloc_t kamekAlloc;
	EGG_Heap_Free_t kamekFree;
    int *heap;
};

void loadKamekBinaryFromDisc(loaderFunctions *funcs, const char *path);

