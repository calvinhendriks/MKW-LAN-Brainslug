#include <Kamek/kamek.hpp>
#include <project.hpp>

BootHook *BootHook::sHooks = NULL;
RaceLoadHook *RaceLoadHook::sHooks = NULL;
RaceFrameHook *RaceFrameHook::sHooks = NULL;
kmBranch(0x800074d4, BootHook::exec);
kmBranch(0x805320d0, RaceLoadHook::exec);
kmBranch(0x80857ac4, RaceFrameHook::exec); //RaceScreen's inherited instance AfterChildUpdate

//The QUAD ABDC has points A = (x1, y2) B = (x2, y2) C = (x2, y1) D = (x1, y1)
bool Quad2D::IsInConvexQuad(Vec2 *point){
    Vec2 *A = &this->PointA;
    Vec2 *B = &this->PointB;
    Vec2 *C = &this->PointC;
    Vec2 *D = &this->PointD;
    float side1 = (B->x - A->x) * (point->z -  A->z) - (point->x - A->x) * (B->z - A->z);
    float side2 = (C->x - B->x) * (point->z -  B->z) - (point->x - B->x) * (C->z - B->z);
    float side3 = (D->x - C->x) * (point->z -  C->z) - (point->x - C->x) * (D->z - C->z);
    float side4 = (A->x - D->x) * (point->z -  D->z) - (point->x - D->x) * (A->z - D->z);
    float zero = 0.0f;
    if ((side1 >= zero && side2 >= zero && side3 >= zero && side4 >= zero) ||
    (side1 <= zero && side2 <= zero && side3 <= zero && side4 <= zero))
    {
        return true;
    }
    return false;
}