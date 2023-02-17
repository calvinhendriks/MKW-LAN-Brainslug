#pragma once
#include <Kamek/kamek.hpp>

union SpeedModConv{
    float speedMod;
    u32 kmpValue;
};

namespace KMP{
    struct PointGroup{
        u8 start;
        u8 length;
        u8 prevLinks[6];
        u8 nextLinks[6];
        u16 unknown_0xE;
    }; //total size 0x10


    class KMPSectionHeader{
    public:
        char magic[4];
        u16 count;
        s16 flag;
        u8 data[10000];
    }; //total size 0x2718

    class HeaderAc{ 
	public:
        char magic[4];
        u32 fileSize;
        u16 sectionCount;
        u16 headerSize;
        u32 versionNumber;
        u8 unknown_0x10[0x4C-0x10];
    }; //total size 0x4c

    class Header{
    public:
        HeaderAc *rawKMP;
        KMPSectionHeader **sectionPointerList;
        u32 versionNumber;
        u32 mainHeaderLength;
    }; //total size 0x10

    class SectionHolder{ 
	public:
        UnkType **rawHolderPointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xc

    class KTPT{ public:
        Vec3 position;
        Vec3 rotation;
        u16 playerId;
        u16 unknown_0x1A;
    }; //total size 0x1C

    class StartPoint{ 
	public:
        KTPT *raw;
        u8 enemyLink;
        u8 unknown_0x5[3];
    }; //total size 0x8

    class StartSectionHolder{ 
	public:
        StartPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC



    class EnemyGroup{ 
    public:
        PointGroup *rawENPH;
        u32 unknown_0x4;
        u32 unknown_0x8;
    }; //total size 0x10

    class EnemyGroupSectionHolder{ 
	public:
        EnemyGroup **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC

    class ENPT{
        Vec3 position;
        float width;
        u16 setting1;
        u8 setting2;
        u8 setting3;
    }; //total size 0x14

    class EnemyPoint{
        virtual void func_vtable();
        ENPT *raw;
        u8 prevLinks[6];
        u8 nextLinks[6];
        u8 inCount;
        u8 outCount;
        u8 inCount2;
        u8 outCount2;
        u8 unknown_0x14[4];
    }; //total size 0x18

    class EnemyPointSectionHolder{ 
	public:
        EnemyPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC


    class ItemGroup{ public:
        PointGroup *rawITPH;
    }; //total size 0x4

    class ItemGroupSectionHolder{
	public:
        ItemGroup **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xCpointgro

    class ITPT{ 
	public:
        Vec3 position;
        float width;
        u16 setting1;
        u16 setting2;
    }; //total size 0x14

    class ItemPoint{ 
	public:
        ITPT *raw;
        u8 prevLinks[6];
        u8 nextLinks[6];
        u8 inCount;
        u8 outCount;
        u8 unknown_0x12[2];
    }; //total size 0x14

    class ItemPointSectionHolder{ 
	public:
        ItemPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC

    class CheckpointGroupSectionHolder : public SectionHolder{ 
    public:
        float invLayerSize;
    };

    struct CKPT {
        Vec2 leftPoint;
        Vec2 rightPoint;
        u8 respawn;
        u8 type;
        u8 previous;
        u8 next;
    };

    struct CheckPoint {
        CKPT *raw;
        u16 nextCKTPTCount;
        u16 prevCKPTCount;
        float midpointX;
        float midpointZ;
        float boxProportions[2];
        u16 scanned;
        s16 id;
        u8 type;
        u8 unknown_0x1D[3];
        CheckPoint *prevCKPTs[6];
        CheckPoint *nextCKTPTs[6];
    };

    class CheckPointSectionHolder{ 
	public:
        CheckPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xc
    
    class AREA{ 
	public:
        u8 shape; //0 box 1 cylinder
        u8 type;
        u8 camera;
        u8 priority;
        Vec3 position;
        Vec3 rotation;
        Vec3 scale;
        u16 setting1;
        u16 setting2;
        u8 routeId;
        u8 enemyRouteId;
        u16 unknown_0x2e;
    }; //total size 0x30

    class AreaPoint{
	public:
        virtual void func_vtable();
        AREA *rawData;
        Vec3 xVector;
        Vec3 yVector;
        Vec3 zVector;
        float halfWidth;
        float height;
        float halfLength;
        float unknown_0x38[2];
        float radius;
        u16 id;
        u8 unknown_0x46[0x48-0x46];
    }; //total size 0x48

    class AreaSectionHolder{
	public:
        AreaPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        u32 unknown_0x8;
        KMPSectionHeader *sectionPtr;
        AreaPoint **sortedArray;
    }; //total size 0x14

    class CAME{ 
	public:
        u8 type;
        u8 nextCam;
        u8 shake;
        u8 routeId;
        u16 speed;
        u16 zoomSpeed;
        u16 viewSpeed;
        u8 startFlag;
        u8 movieFlag;
        Vec3 position;
        Vec3 rotation;
        float zoomStart;
        float zoomEnd;
        Vec3 viewPositionStart;
        Vec3 viewPositionEnd;
        float duration;
    }; //total size 0x48

    class CameraPoint{ 
	public:
        CAME *rawData;
    };

    class CameraSectionHolder{ 
	public:
        CameraPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC

    class JGPT{ 
	public:
        Vec3 position;
        Vec3 rotation;
        u16 id;
        u16 range;
    }; //total size 0x1c

    class RespawnPoint{ 
	public:
        JGPT *rawData;
        Vec3 rotation;
        Vec3 zScale;
        Vec3 xScale;
        u8 enemyLink;
        u8 itemLink;
        u16 range;
        u16 rangeScale;
        u16 unknown_0x2E;
    }; //total size 0x30

    class RespawnSectionHolder{ 
	public:
        RespawnPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC

    struct STGI{ 
	public:
        u8 lapCount;
        u8 polePosition;
        u8 narrow;
        u8 enableFlashing;
        u8 padding;
        u8 flareColor[4]; //at offset 0x5
        u8 unknown_0x9;
        u16 speedMod; //usually 0 but for the code
    }; //total size 0xc

    class StageInfoPoint{ 
	public:
        STGI *rawData;
    }; //total size 0x4

    class StageInfoSectionHolder{ 
	public:
        StageInfoPoint **pointArray;
        u16 pointCount;
        u16 unknown_0x6;
        KMPSectionHeader *sectionPtr;
    }; //total size 0xC

    class Controller{ 
    public:
        Controller(); //0x8051271c
        virtual ~Controller(); //0x808B2C30 805127ac
        Header *header;
        StartSectionHolder *kartPoint;
        EnemyGroupSectionHolder *enemyGroup;
        EnemyPointSectionHolder *enemyPoint;
        ItemGroupSectionHolder *itemGroup;
        ItemPointSectionHolder *itemPoint;
        CheckpointGroupSectionHolder *checkGroup;
        CheckPointSectionHolder *checkPoint;
        SectionHolder *pointInfo;
        SectionHolder *object;
        AreaSectionHolder *area;
        CameraSectionHolder *camera;
        RespawnSectionHolder *respawnPoint;
        SectionHolder *cannonPoint;
        StageInfoSectionHolder *stageInfo;
        SectionHolder *missionSuccessPoint;
        CameraPoint *goalCamera;
        CameraPoint *msptCamera;
        CameraPoint *openingCam;
        u32 unknown_0x50;
    };
    extern Controller *controller;
}
