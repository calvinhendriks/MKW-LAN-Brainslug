#pragma once

#include <Kamek/kamek.hpp>
#include <System/dvd.hpp>

namespace nw4r {
	namespace ut {
		struct Color {
			union {
				struct { u8 r,g,b,a; };
				u32 rgba;
			};
		}; // Total size 0x4


		struct Link {
			void *prev, *next;
		}; // Total size 0x8
		struct List {
			Link *head;
			Link *tail;
			u16 count;  //0x8
			u16 offset; //0xA
		}; // Total size 0xc

		void List_Init(List *list, u16 offset);
		void List_Append(List *list, void *newObj);
		void List_Insert(List *list, void *insertBefore, void *newObj);
		void List_Remove(List *list, void *obj);
		void *List_GetNext(List *list, void *obj);
		void *List_GetPrev(List *list, void *obj);

		class LinkListNode {
		public:
			LinkListNode *next;
			LinkListNode *prev;
		}; // Total size 0x8

		class LinkList {
		public:
			int count;
			LinkListNode initialNode;
		}; // Total size 0xc

		// TODO: Character/text/font utility classes
		template <class T>
		class TagProcessorBase { };

		class IOStream{
		public:
			IOStream();
			virtual void func_vtable();
			bool isAvailable;
			u8 unknown_0x5[3];
			u32 asyncResult;
			UnkType *callBack; //actually a func
			void *arg;
		}; //total size 0x14

		class DVDFileStream : public IOStream{
		public:
			DVDFileStream(u32 entryNum); //800b00d0 
			virtual void func_vtable(); //80274c40
			void Seek(u32 begin, u32 r5);
			int Read(void *buffer, u32 size);
			FileStats stats;
			u32 unknown_0x1C;
			void *cancelArg;
			bool isCancelling;
			u8 unknown_0x25[3];
			DVDCommandBlock dvdInfo;
			DVDFileStream *stream;
			u32 priority;
			bool isBusy;
			bool closeOnDestroyFlg;
			bool closeEnableFlg;
			bool isLocked;
			u32 offset;
			u32 size;
		};

		class DVDLockedFileStream : public DVDFileStream{
		public:
			DVDLockedFileStream(u32 entryNum); //800b06b0
		};
	}
}