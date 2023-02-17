#pragma once
#include <Kamek/kamek.hpp>

extern "C" {

void DCFlushRange(void * ptr, u32 size);
void ICInvalidateRange(void * ptr, u32 size);

}