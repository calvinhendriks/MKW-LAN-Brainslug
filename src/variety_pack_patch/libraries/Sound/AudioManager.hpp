#pragma once
#include <nw4r/snd/snd.hpp>
#include <Kamek/kamek.hpp>
#include <egg/egg.hpp>

class SoundArchive{ //place holder name
public:
    SoundArchive(nw4r::snd::SoundArchivePlayer *soundArchivePlayer, nw4r::snd::SoundHeap *heap); //0x80210590
    virtual void func_vtable(); //0x802a288c rewrites 0x802a2730
    bool isOpen;
    u8 unknown_0x5;
    u8 unknown_0x6[2];
    nw4r::snd::DVDSoundArchive *dvdSoundArchiveptr; //ptr to the instance right below
    nw4r::snd::DVDSoundArchive dvdSoundArchive;
    nw4r::snd::UnkArchiveClass unkArchiveClass; //0x198
    nw4r::snd::UnkArchiveClass2 unkArchiveClass2; //0x374
    nw4r::snd::SoundArchivePlayer *soundArchivePlayer;
    nw4r::snd::SoundHeap *heap;
    u32 unknown_0x4CC;
    u32 unknown_0x4D0;
    void *unknown_0x4D4;
}; //total size 0x4D8

class UnkAudioMgrClassArray{
public:
    UnkAudioMgrClassArray(); //80211a14
    u32 unknown_0x0[4];
    u8 unknown_0x14[8];
}; //total size 0x18

class UnkAudioMgrClass{
public:
    UnkAudioMgrClass(); //80211c14
    UnkAudioMgrClassArray array[3];
}; //total size 0x48


class SimpleAudioMgr{ //likely an egg struct
public:
    SimpleAudioMgr(); //8021329c
    virtual void func_vtable(); //802a2868, the class actually inherits from something else with vtable 802a2910
    u8 unknown_0x4[4];
    void *vtable; //802a2878 overwrites 802a2950
    nw4r::snd::SoundHeap heap;
    u8 unknown_0x38[0x68-0x38];
    OSMessageQueue messageQueues[3];
    SoundArchive archive; //0xf8
    EGG::AudioSystem audioSystem; //0x5d0
    nw4r::snd::SoundArchivePlayer soundArchivePlayer; //0x5dc 
}; //total size 0x6bc

class SimpleAudioMgr2 : public SimpleAudioMgr { //also an egg struct
public:
    SimpleAudioMgr2(); //80211320
    nw4r::snd::UnkSoundClass soundClass; //0x6bc
    nw4r::snd::UnkSoundClass2 soundClass2[4];
    u32 unknown_0x844;
    u32 unknown_0x848;
    UnkAudioMgrClass unkAudioMgrClass;
}; //total size 0x894

class SoundDisposer : public EGG::Disposer{ //terrible name
public:
    virtual void func_vtable(); //0x808c91d0
};

class AudioManager : public SimpleAudioMgr2 { //chain of inheritance
public:
    AudioManager(); //0x80716e2c allocates and construct, so ctor might be inlined
    virtual void unknown_vtable(); //vtable 0x808c9118 update 8071763c vtable at 0x8 from audioMgr also gets overwritten 808c9128
    SoundDisposer disposer; //0x894, has the dtor
    u8 unknown_0x8A4[4]; //0x8A4
    u32 unknown_0x8A8[3];
    float unknown_0x8B4[3];
}; // Total size 0x8c0

extern AudioManager *soundData;