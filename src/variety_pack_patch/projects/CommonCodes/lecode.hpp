#pragma once

#include <Kamek/kamek.hpp>
#include <System/OS.hpp>

struct LECTHeader
{
    u32 magic;
    u32 version;
    u32 buildNum;
    void * loadAddress;
    void (*mainFunc)();
    u32 size;
    u32 paramSectionOffset;
    char region;
    char debugFlag;
    u8 leVersion;
    u8 _1f;
};

class PostLECodeHook {
public:
    enum Mode {
        BRANCH,
        BRANCH_LINK,
        WRITE32
    };

private:
    u32 mAddr;
    u32 mVal;
    Mode mMode;

    PostLECodeHook * mNext;
    static PostLECodeHook * sHooks;

    void patch() {
        if (mMode == WRITE32) {
            *(u32 *)mAddr = mVal;
        }
        else {
            u32 delta = (mVal - mAddr) & 0x3FFFFFF;
            u32 instr = 0x48000000 | delta;
            if (mMode == BRANCH_LINK)
                instr |= 1;

            *(u32 *)mAddr = instr;
        }

        DCFlushRange((void *)mAddr, sizeof(mVal));
        ICInvalidateRange((void *)mAddr, sizeof(mVal));
    }

public:
    /*
        addr will not be autoported, use & of a symbol for that
        
        val depends on mode:
            BRANCH[_LINK]: function to branch to
            WRITE32: word to write
    */
    template <typename T1, typename T2>
    PostLECodeHook(T1 addr, T2 val, Mode mode) {
        mNext = sHooks;
        sHooks = this;

        mAddr = (u32)addr;
        mVal = (u32)val;
        mMode = mode;
    }

    static void exec() {
        for (PostLECodeHook * p = sHooks; p; p = p->mNext)
            p->patch();
    }
};
