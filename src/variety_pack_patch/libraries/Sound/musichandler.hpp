#pragma once
#include <egg/egg.hpp>
#include <Race/racedata.hpp>
#include <Kamek/kamek.hpp>
#include <common.hpp>

typedef enum RaceState{
	RACEINTRO = 0x2,
	BEFORECOUNTDOWN = 0x3,
	NORMAL = 0x4,
	FAST = 0x5,
	RACEFINISHED = 0x7
};

struct TrackToCourseID{
	CourseId courseID;
};

class MusicHandlerSub{
	u8 unknown_0[0x8-0x0];
	virtual void unknown_vtable(); //vtable 0x808c91e0
	u8 unknown[0x1c-0xc];
};//total size 0x1C

class MusicHandler : public EGG::Disposer {
public:
	MusicHandler(); //0x80710688
	virtual void func_vtable(); //0x808c8fdc
	void ChangeMusic(RaceState raceState);
	CourseId courseId;
	u8 unknown_0x14[0x30-0x14];
	Timer unk_Timer;
	u8 unknown_0x3C[0x40-0x3C];
	u32 raceState;
	GameMode gameMode;
	GameType gameType;
	u8 unknown_0x4d;
	u8 playerCount;
	u8 unknown_0x4e[0x54-0x4e];
	MusicHandlerSub sub;
	u8 unknown_0x70[0x178-0x70];
};//Total Size 0x178

extern MusicHandler *musicHandler;
extern TrackToCourseID trackToCourseIDTable[42];

extern "C"{
	CourseId GetCourseMusicSlot();
}
