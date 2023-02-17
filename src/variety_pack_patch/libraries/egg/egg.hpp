#pragma once

#include <Kamek/kamek.hpp>
#include <nw4r/ut/ut.hpp>

namespace EGG {
	class Heap;

	class Disposer {
	public:
		Disposer();
		virtual ~Disposer();

	private:
		Heap *heap;
        UnkType *unknown_0x8;
        UnkType *unknown_0xc;
	}; // Total size 0x10

	class Allocator {
	private:
		u8 _unk00[0x10];

	public:
		Allocator(Heap *heap, long alignment);
		virtual ~Allocator();
		virtual void *alloc(unsigned long size);
		virtual void free(void *buffer);

	private:
		Heap *heap;
		long alignment;
	};

	class Heap : public Disposer {
	public:
		Heap(/*MEMiHeapHead*/ void *rvlHeap); //802296e8
		virtual ~Heap(); //802a30c0
		virtual int getHeapKind() const = 0;
		virtual void initAllocator(Allocator *allocator, long alignment) = 0;
		virtual void *alloc(unsigned long size, long alignment) = 0;
		virtual void free(void *buffer) = 0;
		virtual void destroy() = 0;
		virtual unsigned long resizeForMBlock(void *buffer, u32 newSize) = 0;
		virtual u32 getTotalFreeSize() = 0;
		virtual u32 getAllocatableSize(long alignment) = 0;


		static void *alloc(unsigned long size, int align, Heap *heap);
		static Heap *findHeap(/*MEMiHeapHead*/ void *rvlHeap);
		Heap *findParentHeap();
		static Heap *findContainHeap(void *buffer);
		static void free(void *buffer, Heap *heap);
		void dispose();
		void dump();
		static void dumpAll();
		Heap *becomeCurrentHeap();
		Heap *becomeCurrentHeapWithoutLocking();
	private:
		nw4r::ut::Link parentLink;
		void *rvlHeap; //0x10
		void *parentHeapMBlock; //0x14
		Heap *parentHeap; //0x18
		u16 dameFlag; //0x18
		nw4r::ut::Link globalLink;
		nw4r::ut::List childList; //0x28
		const char *name; //0x34
	}; //total size 0x38

	class ExpHeap : public Heap{
	public:
		ExpHeap(); //80226a1c
		virtual ~ExpHeap(); //802aff8
		virtual int getHeapKind();
		virtual void initAllocator(Allocator *allocator, long alignment);
		virtual void *alloc(unsigned long size, long alignment);
		virtual void free(void *buffer);
		virtual void destroy();
		virtual unsigned long resizeForMBlock(void *buffer, u32 newSize);
		virtual u32 getTotalFreeSize();
		virtual u32 getAllocatableSize(long alignment);
		u32 adjust();

	};

	class MsgRes {
	private:
		const u8 *bmg, *INF1, *DAT1, *STR1, *MID1, *FLW1, *FLI1;
	public:
		MsgRes(const u8 *bmgFile, u32 unusedParam);
		virtual ~MsgRes();
		static void parseFormatCode(wchar_t initialTag, const wchar_t *string, u8 *outArgsSize, u32 *outCmd, const wchar_t **args);
		const wchar_t *findStringForMessageID(int category, int message) const;
	private:
		void setBMG(const u8 *ptr);
		void setINF(const u8 *ptr);
		void setDAT(const u8 *ptr);
		void setSTR(const u8 *ptr);
		void setMID(const u8 *ptr);
		void setFLW(const u8 *ptr);
		void setFLI(const u8 *ptr);
		int identifySectionByMagic(u32 magic) const;

	protected:
		struct INFEntry {
			u32 stringOffset;
		};
		const INFEntry *findINFForMessageID(int category, int message) const;
		u32 getEntryFromMID(int index) const;
	};
	void *LoadToMainRam(char *path, void *buffer, EGG::Heap *heap, u32 allocDirection, u32 offset, u32 r8, u32 *r9);
	
	class AudioSystem{
	public:
		AudioSystem(); //0x80213cc8
		float unknown_0x0;
		u32 unknown_0x4[2];
	}; //total size 0xC
}
