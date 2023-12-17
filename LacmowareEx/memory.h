#pragma once

#define LENGTH(arr) sizeof(arr) / sizeof(*arr)

#include "offsets.h"

namespace memory
{
    DWORD fnFindPatternIDA(const char *szModule, const char *szSignature);
    DWORD fnFindPatternIDA(DWORD startAddress, DWORD endAddress, const char *szSignature);
    DWORD fnFindDMAAddy(DWORD ptr, std::vector<offset_t> offsets);
    bool fnIsMemoryReadable(void *ptr, size_t byteCount);
    void fnReplaceWithNop(DWORD *address, int length);
    void fnReplaceWithNop(DWORD *address, BYTE *restoreBuf, int length);
    void fnReplaceWithBuffer(DWORD *address, BYTE *restoreBuf, BYTE *srcBuf, int length);
    void xorString(char *data, const char *key);
}
