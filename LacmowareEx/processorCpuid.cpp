#include "processorCpuid.h"

#define __cpuid(__leaf, __eax, __ebx, __ecx, __edx) \
    __asm("cpuid" : "=a"(__eax), "=b" (__ebx), "=c"(__ecx), "=d"(__edx) \
                  : "0"(__leaf))

uint64_t getCpuidFeatures()
{
    uint32_t tmp = 0, edx = 0, ecx = 0;
    __cpuid(0x00000001, tmp, tmp, ecx, edx);
    return ((((uint64_t)ecx) << 32) ^ edx);
}
