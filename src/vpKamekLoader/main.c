#include <bslug.h>
#include <rvl/cache.h>
#include <io/fat-sd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>


BSLUG_MODULE_GAME("RMC?");
BSLUG_MODULE_NAME("Variety Pack V3 loader");
BSLUG_MODULE_VERSION("v1.0");
BSLUG_MODULE_AUTHOR("Lami");
BSLUG_MODULE_LICENSE("MIT");

#define loaderPath "sd:/varietypack/boot/loader.bin" // Path to the loader
int ret;
bool mounted;

static int MountSDCard()
{
    int r = SD_Mount();
    mounted = (r == 0);
    return r;
}

static void vpKamekLoader()
{
    // Load the loader
    if (!mounted)
    {
        MountSDCard();
    }
    static FILE_STRUCT fs;
    ret = SD_open(&fs, loaderPath, O_RDONLY);
    // Error out if we cannot open the loader
    if (ret == -1)
    {
        printf("Could not open the loader");
    }
    int loaderSize = SD_read(&fs, 0x80004000, fs.filesize);
    // Error out if we cannot read the loader
    if (loaderSize == -1)
    {
        printf("Could not read the loader");
    }
    // Close the file
    SD_close(&fs);


    // Insert branch to the loader
    switch (*(char *)0x80000003) // Get the region from the game ID
    {
    case 'P':
        *(unsigned int *)0x8000A3F4 = 0x4BFF9C1C;
        break;
    case 'E':
        *(unsigned int *)0x8000A3B4 = 0x4BFF9C5C;
        break;
    case 'J':
        *(unsigned int *)0x8000A350 = 0x4BFF9CC0;
        break;
    case 'K':
        *(unsigned int *)0x8000A4FC = 0x4BFF9B14;
        break;
    default:
        // The only way we get here is if the region letter is one that mkw doesn't have, so crash the game
        printf("Invalid region");
        // The following code sets the screen to red and loop forever
        unsigned int *HW_VISOLID = (unsigned int *)0xcd000024;
        *HW_VISOLID = 0x5aef5101;
        for (;;)
            ;
    }

    return;
}


BSLUG_MUST_REPLACE(SystemManager_loadSymbols, vpKamekLoader);
