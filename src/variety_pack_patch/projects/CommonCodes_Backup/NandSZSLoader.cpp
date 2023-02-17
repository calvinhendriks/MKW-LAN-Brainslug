#include <Kamek/kamek.hpp>
#include <egg/egg.hpp>
#include <System/system.hpp>

#ifdef NANDSZSLOADER

void* NANDSZSLoader(char *path, void* buffer, EGG::Heap *heap, u32 allocDirection, u32 offset, u32 r8, u32 *sizeTmp){
    s32 fd = -1;
    char *occurrence = strstr(path, "Race/Course/");
    if (occurrence != NULL){
        char trackName[0x30];
        sscanf(occurrence, "Race/Course/%s", &trackName);
        char nandPath[0x50];
        snprintf(nandPath, 0x50, "/Course/%s", trackName);
        fd = ISFSOpen(nandPath, 1);
        if (fd >= 0){
            FileStats fileStats __attribute((aligned (0x20)));
            ISFSGetFileStats(fd, &fileStats);
            u32 fileSize = fileStats.fileSize;
            buffer = EGG::Heap::alloc(fileSize, 0x20, heap);
            ISFSRead(fd, buffer, fileSize);
            ISFSClose(fd);
            *sizeTmp = fileSize;
            return buffer;
        }
    }
    return EGG::LoadToMainRam(path, buffer, heap, allocDirection, offset, r8, sizeTmp);
}
kmCall(0x80518e94, &NANDSZSLoader);
kmWrite32(0x80857aa0, 0x60000000); //disable ghost cannot be saved message

#endif