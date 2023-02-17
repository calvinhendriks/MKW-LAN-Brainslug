#pragma once

#include <Kamek/kamek.hpp>
#include <nw4r/ut/ut.hpp>
#include <System/dvd.hpp>

enum SoundType{
	SOUND_TYPE_INVALID,
	SOUND_TYPE_SEQ,
	SOUND_TYPE_STRM_,
	SOUND_TYPE_WAVE
};

namespace nw4r{
    namespace snd {
		class StrmPlayer;

		class FrameHeap{
			void *unknown_0x0;
			ut::LinkList list;
		};//total size 0x10

		class SoundHeap{
			SoundHeap(); //800a2ed0
			virtual void func_vtable(); //80274a30
			OSMutex mutex;
			FrameHeap frameHeap; //0x1C
		}; //total size 0x2C

		class SoundPlayer{
		public:
			ut::LinkList soundList;
			ut::LinkList priorityList;
			ut::LinkList heapList;
			u32 playableCount;
			u32 playableLimit;
			float volumeRatio;
			float lpfFreq;
			u32 outputLineFlag;
			float mainOutVolume;
			float remoteOutVolume[4];
			float mainSend;
			float fxSend[3];
		}; //total size 0x5C

		class SoundInstanceManager{
		public:
			SoundInstanceManager *nextInstance;
			ut::LinkList priorityList;
			OSMutex mutex; //0x10
		}; //total size 0x28

		class SoundArchiveFileReader{ //https://wiki.tockdom.com/wiki/BRSAR_(File_Format)
		public:
			SoundArchiveFileReader(); //8009e690
			char magic[4]; //RSAR
			u16 byteOrderMark; //0xFEFF for big endian
			u16 version; //01 04 for revo_kart
			u32 length;
			u16 headerLength;
			u16 sectionCount;
			u32 offsetSYMB;
			u32 sizeSYMB;
			u32 offsetINFO;
			u32 sizeINFO;
			u32 offsetFILE;
			u32 sizeFILE;
			UnkType *soundInfo;
			void *stringBase;
			u8 *stringTable;
			u8 *soundStringTree;
			u8 *playerStringTree;
			u8 *groupStringTree;
			u8 *bankStringTree;
		}; //total size 0x44

		class SoundArchive{
			SoundArchive(); //8009de00
			virtual void func_vtable();
			SoundArchiveFileReader *fileReader;
			char extFileRoot[256];
		}; //total size 0x108

		class SoundArchivePlayer{
		public:
			SoundArchivePlayer(); //800a0500
			ut::LinkListNode node;
			void *unknown_0x8; //0x802749e0 idk soundStartable vtable
			virtual void func_vtable();  //802749f4 
			SoundArchive *soundArchive;
			u32 *groupTable;
			u32 *fileManager;
			UnkType *seqCallBack; //actually a function but idk how to declare it
			UnkType *wsdCallBack;
			UnkType *seqTrackAllocator;
			UnkType *seqUserprocCallback;
			void *seqUserprocCallBackarg; //2c
			u32 soundPlayerCount;
			SoundPlayer *soundPlayer; //0x34
			SoundInstanceManager seqSoundInstanceManager; //0x38
			SoundInstanceManager strmSoundInstanceManager;
			SoundInstanceManager waveSoundInstanceManager;
			u8 unknown_0xB0[0xE0-0xB0]; //has two classes related to seq and strm it seems
		}; //total size 0xe0

		class UnkSoundClass{
			UnkSoundClass(); //8009d8a0
			virtual void func_vtable(); //80274968
			u8 unknown_0x4[0x28-0x4];
		}; //total size 0x28

		class UnkSoundClass2{
			UnkSoundClass2(); //8009d550
			Mat34 mat;
			float unknown_0x30[6];
			u32 unknown_0x48;
			u8 unknown_0x4C[4];
			u32 unknown_0x50[2];
		}; //total size 0x58

		class UnkArchiveClass : public SoundArchive{
		public:
			UnkArchiveClass(); //80097570
			virtual void func_vtable(); //80274808
			SoundArchiveFileReader fileReader;
			u8 unknown_0x14C[0x1DC-0x14c];
		}; //total size 0x1DC

		class UnkArchiveClass2 : public SoundArchive{
		public:
			UnkArchiveClass2(); //80095d80
			virtual void func_vtable(); //802744d8
			u32 unknown_0x108;
			SoundArchiveFileReader fileReader;
		}; //total size 0x150

		class DVDSoundArchive : public SoundArchive{
		public:
			class DVDFileStream : public nw4r::ut::DVDLockedFileStream {
			public:
				DVDFileStream (); //inlined 8009132c
				virtual void func_vtable(); //802742b0
			};

			DVDSoundArchive();
			virtual void func_vtable(); //80274318
			DVDFileStream *OpenExtStream(DVDFileStream *dvdFileStream, u32 size, char *path, u32 begin, u32 length);
			SoundArchiveFileReader fileReader;
			DVDCommandBlock fileInfo;
			bool isOpen;
			u8 unknown_0x189[3];
		
		}; //total size 0x18c

		class PlayerParamSet {
		public:
			PlayerParamSet(); //8008dc60
			virtual void func_vtable(); //0x80274250
			float unknown_0x4[5];
			u32 unknown_0x18[2];
			float unknown_0x20[2];
			u32 unknown_0x28[2];
			float unknown_0x30[39];
			u32 soundId; //0xCC
		}; //total size 0xD0

		class HEADdatabase { //-C for all offsets
		public:
			u32 type; //3 for strm, 800a4ec4, base on soundtype
			bool isLooped; //0x10
			u8 unknown_0x11[3]; //might be padding //
			u32 channelCount;
			u32 sampleRate; //44100Hz for example
			u16 unknown_0x1C[2]; //2nd might be padding
			u32 loopStartSample;
			u32 samplesCount;
			u32 uncompressedFileSize; //in bytes
			u32 blocksCount;
			u32 blockSize;
			u32 unknown_0x34[5];
			u32 bitsPerSample;
		}; //total size 0x3C

		class HEADdata {
		public:
			HEADdata(); //idk
			nw4r::ut::LinkListNode node1;
			virtual void func_vtable(); //80274aac
			HEADdatabase base;
		};//total size 0x4C

		class UnkStrmClass{
		public:
			virtual void func_vtable(); //80274ae8
			nw4r::ut::LinkListNode node1;
			u8 unknown_0xC;
			u8 unknown_0xD[3];
			StrmPlayer *strmPlayer;
			DVDSoundArchive::DVDFileStream *stream; //0x14
			u32 unknown_0x18; //copied from 0x168 of the strm player
			u32 unknown_0x1C; //copied from 0x16C of the strm player
			nw4r::ut::LinkList list; //0x20

		}; //total size 0x2C

		class UnkStrmPlayerClass {
			UnkStrmPlayerClass(); //800a8180
			virtual void func_vtable(); //0x80274ad0
			u8 unknown_0x4[0x34-0x4];
		}; //total size 0x34

		class StrmPlayer : public PlayerParamSet {
		public:
			StrmPlayer(); //0x800a5860
			virtual void func_vtable(); //0x80274a88
			HEADdata headData; //copied from HEAD
			u8 unknown_0x11C;
			bool isNotMuted;
			bool isPlaying;
			bool canStart;
			u8 unknown_0x120[0x12b-0x120];
			u32 unknown_0x12C;
			u32 unknown_0x130;
			u32 unknown_0x134;
			u32 blockSize;
			u32 blocksPerChunk; //??total size allocated divided by blockSize? 800a6c64
			u32 unknown_0x140[2]; //just seems to be prev -1
			u32 nextblockChunkID; //within its chunk
			u32 nextBlockID;
			u32 unknown_0x150;
			u32 blockChunkID;
			u32 currentlyStreamedBlockID;
			u32 loopBlockID; //ID of the block that matches the loopStartSample
			u32 lastBlockID; //block count -1 //0x160
			u8 unknown_0x164[0x170-0x164];
			UnkStrmClass class_0x170; //unknown class 80274ae8
			u32 unknown_0x19c; //some kind of list thing, idk
			UnkStrmPlayerClass array[0x20]; //800a8180 ctor size 0x34, one per track?
			UnkType *strmBufferPool; //0x820
			DVDSoundArchive::DVDFileStream *stream;
			u32 streamCount; //channel / 2
			u32 channelsNeeded; //sound ID dependant
			u32 unknown_0x830;
			u8 unknown_0x834[0xD34-0x834]; //has pointers to the streams
		}; // total size 0xd34

		class BasicSound{
		public:
			BasicSound(u8 size, u32 r5); //8008e0e0, size seems to be headerSize
			virtual void func_vtable(); //0x80274278
			u32 unknown_0x4[3];
			SoundPlayer *soundPlayer;
			u32 unknown_0x14[7];
			float unknown_0x30;
			float ambientPitch; //0x34
			float unknown_0x38[4];
			u32 r5; //0x48
			float actorPitch;
			float unknown_0x50[4];
			u32 unknown_0x60[2];
			float unknown_0x68[2];
			u32 unknown_0x70[2];
			u8 unknown_0x78[4];
			u32 unknown_0x7C;
			u8 unknown_0x80[0x88-0x80];
			u32 frames; //frames since the strm (_n and_f combined) started
			u8 size; //0x8C
			u8 unknown_0x8D;
			u8 unknown_0x8E[2];
			u32 soundId;
			float unknown_0x94[2];
			u32 unknown_0x9C[2];
			float volumeRatio;
			u8 unknown_0xA8[0xB0-0xA8];
			float unknown_0xB0;
			u8 unknown_0xB4[7];
			u8 unknown_0xBB;
			float unknown_0xBC;
			u8 unknown_0xC0[0xD0-0xC0];
			float unknown_0xD0[4];
			nw4r::ut::LinkListNode node1;
			nw4r::ut::LinkListNode soundList; //the one used in muscispeedup, you arrive there so must subtract E8 (where this node is) to get to the start of the struct
			nw4r::ut::LinkListNode node3; //priority list stuff, next changes when strm starts
			u32 unknown_0xF8[2];
		}; //total size 0x100

		struct floatAndInt{
			float unknown_0x0[2];
			u32 unknown_0x4[2];
		};

		class StrmSound : public BasicSound{ //don't have the official name
		public:
			StrmSound(u32 *r4, u8 size, u32 r6); //0x800a8480
			virtual void func_vtable(); //0x80274b00
			void Setup(); //800a87c0
			void Prepare(); //800a8840
			StrmPlayer GetPlayer();
			StrmPlayer strmPlayer; //0x100
			u32 unknown_0xE34[2];
			float unknown_0xE3C;
			float volumeRatio2; //yet another one lol
			u32 unknown_0xE44[2];
			floatAndInt unknown_0xE4C[7];
			u32 unknown_0xEBC;
		};//total size 0xEC0

		struct RSTMHeader{
			char magic[4]; //RSTM
			u16 byteOrderMask; //FEFF
			u16 unknown_0x06;
			u32 length;
			u16 headerLength; //always 0x40
			u16 unknown_0x0e;
			u32 offsetToHEAD;
			u32 headLength;
			u32 offsetToADPC;
			u32 adpcLength;
			u32 offsetToDATA;
			u32 dataLength;
			u8 unknown_0x28[0x16];
			u8 speedUpByte; //artificial
			u8 volumeByte; //artifical
		}; //total size 0x40

		struct HEADSection{
			char magic[4]; //HEAD
			u32 length;
			u8 unknown_0x8[0x20-0x8]; //first is probably version, last is likely length of the subHeader
			u8 type; //soundtype but as a u8
			bool isLooped;
			u8 channelCount;
			u8 unknwon_0x23; //gets shifted and added to sample rate
			u16 sampleRate;
			u16 unknown_0x26;
			u32 loopStartSample; //0x28
			u32 samplesCount;
			u32 uncompressedFileSize; //in bytes
			u32 blocksCount;
			u32 blockSize;
			u32 unknown_0x3C[5];
			u32 bitsPerSample;
			u8 unknown_0x54[0x2c0-0x54];
		};//total size 0x2C0

		struct StrmFileReader{
			StrmFileReader(); //800a4e90
			RSTMHeader *header;
			HEADSection *section;
		};

		struct DVDFileReader{
			bool InitHeadData(HEADdatabase *base);
			DVDSoundArchive::DVDFileStream *stream;
			StrmFileReader strmFileReader;
		}; //total size 0xC
		

		int DetailUtilCalcRandom();
		
	}
}