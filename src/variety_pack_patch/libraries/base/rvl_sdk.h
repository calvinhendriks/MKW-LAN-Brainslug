#ifndef __KAMEK_BASE_RVL_SDK_H
#define __KAMEK_BASE_RVL_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

/* OS Module */
struct OSMutex{
    u8 unknown[0x18];
}; //total size 0x18

struct OSThreadQueue{
    void *head;
    void *tail;
};
struct OSMessageQueue{
    OSThreadQueue queue1;
    OSThreadQueue queue2;
    u8 unknown_0x10[0X30-0X10];
};
void OSReport(const char *format, ...);
u64 OSGetTime();
u32 OSGetTick();
void OSFatal(u32 *fg, u32 *bg, const char *message);

typedef struct {
	int sec, min, hour, mday, mon, year, wday, yday, msec, usec;
} OSCalendarTime;
void OSTicksToCalendarTime(u64 time, OSCalendarTime *result);

/* MTX Module */
typedef struct Vec2{
	 f32 x, z;
} ;

typedef struct Vec3{
  float x, y, z;
}; // total size 0xc

typedef struct Quat{
  float x, y, z, w;
}; // total size 0x10

typedef struct { s16 x, y, z; } S16Vec3;
typedef f32 Mat[3][4];
typedef f32 Mat44[4][4];
typedef f32 Mat43[4][3];
typedef f32 Mat34[3][4];

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];
typedef f32 Mtx43[4][3];
typedef f32 Mtx34[3][4];
typedef struct { f32 x, y, z, w; } Quaternion;

void PSMTXIdentity(Mtx matrix);
void PSMTXCopy(const Mtx source, Mtx dest);
void PSMTXConcat(const Mtx sourceA, const Mtx sourceB, Mtx dest);
void PSMTXConcatArray(const Mtx sourceA, const Mtx *sourcesB, Mtx *destsB, int count);
u32 PSMTXInverse(const Mtx source, Mtx dest);
u32 PSMTXInvXpose(const Mtx source, Mtx dest);
void PSMTXRotRad(Mtx matrix, u8 axis, f32 radians);
void PSMTXRotTrig(Mtx matrix, u8 axis, f32 sin, f32 cos);
void PSMTXRotAxisRad(Mtx matrix, Vec3 *axis, f32 radians);
void PSMTXTrans(Mtx matrix, f32 x, f32 y, f32 z);
void PSMTXTransApply(const Mtx source, Mtx dest, f32 x, f32 y, f32 z);
void PSMTXScale(Mtx matrix, f32 x, f32 y, f32 z);
void PSMTXScaleApply(const Mtx source, Mtx dest, f32 x, f32 y, f32 z);
void PSMTXQuat(Mtx dest, const Quaternion *quat);
void C_MTXLookAt(Mtx dest, const Vec3 *cameraPos, const Vec3 *cameraUp, const Vec3 *target);
void C_MTXLightFrustum(Mtx dest, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLightPerspective(Mtx dest, f32 fovy, f32 aspect, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void C_MTXLightOrtho(Mtx dest, f32 top, f32 bottom, f32 left, f32 right, f32 scaleS, f32 scaleT, f32 transS, f32 transT);
void PSMTXMultVec3(const Mtx matrix, const Vec3 *source, Vec3 *dest);
void C_MTXFrustum(Mtx44 dest, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);
void C_MTXPerspective(Mtx44 dest, f32 fovy, f32 aspect, f32 near, f32 far);
void C_MTXOrtho(Mtx44 dest, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);
void PSVECAdd(const Vec3 *sourceA, const Vec3 *sourceB, Vec3 *dest);
void PSVECSubtract(const Vec3 *sourceA, const Vec3 *sourceB, Vec3 *dest);
void PSVECScale(const Vec3 *source, Vec3 *dest, f32 scale);
void PSVECNormalize(const Vec3 *source, Vec3 *dest);
f32 PSVECMag(const Vec3 *Vec3);
f32 PSVECDotProduct(const Vec3 *sourceA, const Vec3 *sourceB);
void PSVECCrossProduct(const Vec3 *sourceA, const Vec3 *sourceB, Vec3 *dest);
void C_Vec3HalfAngle(const Vec3 *sourceA, const Vec3 *sourceB, Vec3 *dest);
f32 PSVECSquareDistance(const Vec3 *sourceA, const Vec3 *sourceB);
void C_QUATMtx(Quaternion *dest, const Mtx source);
void C_QUATSlerp(const Quaternion *sourceA, const Quaternion *sourceB, Quaternion *dest, f32 value);

#define MTXIdentity PSMTXIdentity
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXConcatArray PSMTXConcatArray
#define MTXInverse PSMTXInverse
#define MTXInvXpose PSMTXInvXpose
#define MTXRotRad PSMTXRotRad
#define MTXRotTrig PSMTXRotTrig
#define MTXRotAxisRad PSMTXRotAxisRad
#define MTXTrans PSMTXTrans
#define MTXTransApply PSMTXTransApply
#define MTXScale PSMTXScale
#define MTXScaleApply PSMTXScaleApply
#define MTXQuat PSMTXQuat
#define MTXLookAt C_MTXLookAt
#define MTXLightFrustum C_MTXLightFrustum
#define MTXLightPerspective C_MTXLightPerspective
#define MTXLightOrtho C_MTXLightOrtho
#define MTXMultVec3 PSMTXMultVec3
#define MTXFrustum C_MTXFrustum
#define MTXPerspective C_MTXPerspective
#define MTXOrtho C_MTXOrtho
#define Vec3Add PSVECAdd
#define Vec3Subtract PSVECSubtract
#define Vec3Scale PSVECScale
#define Vec3Normalize PSVECNormalize
#define Vec3Mag PSVECMag
#define Vec3DotProduct PSVECDotProduct
#define Vec3CrossProduct PSVECCrossProduct
#define Vec3HalfAngle C_Vec3HalfAngle
#define Vec3SquareDistance PSVECSquareDistance
#define QUATMtx C_QUATMtx
#define QUATSlerp C_QUATSlerp

// TODO: GX, CX, IOS ... and then of course NW4R

#ifdef __cplusplus
}
#endif

#endif
