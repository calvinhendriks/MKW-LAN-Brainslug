#include <Kamek/kamek.hpp>
#include <System/dvd.hpp>
#include <base/rvl_sdk.h>
#include <lecode.hpp>
#include <project.hpp>

#ifdef LECODE

PostLECodeHook * PostLECodeHook::sHooks = NULL;

static void notFoundError()
{
    u32 fg = 0xffffffff;
    u32 bg = 0x000000ff;
    OSFatal(&fg, &bg, "Error: LE-Code bin not found");
}

void loadLECode()
{
    DVDCommandBlock file;
    LECTHeader header __attribute__((aligned(0x20)));
    
    // Get path
    const char * path;
    switch (*(char *)0x80000003)
    {
        case 'E':
            path = "/rel/lecode-USA.bin";
            break;
        case 'J':
            path = "/rel/lecode-JAP.bin";
            break;
        case 'P':
            path = "/rel/lecode-PAL.bin";
            break;
        case 'K':
            path = "/rel/lecode-KOR.bin";
            break;
    }

    OSReport("Loading %s\n", path);

    // Open file
    if (!DVDOpen(path, &file))
        notFoundError();

    // Read header
    DVDReadPrio(&file, (void *)&header, sizeof(header), 0, 2);

    // Read full file
    DVDReadPrio(&file, header.loadAddress, header.size, 0, 2);

    // Call entry function
    LECTHeader * newHeader = (LECTHeader *) header.loadAddress;
    newHeader->mainFunc();

    // Call post LE-Code hooks
    PostLECodeHook::exec();
}

static BootHook loadLECodeHook(loadLECode);

#endif