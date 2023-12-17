#include "pch.h"
#include "memory.h"

#define INRANGE( x, a, b )  (x >= a && x <= b) 
#define GETBITS( x )        (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE( x )        (GETBITS(x[0]) << 4 | GETBITS(x[1]))

namespace memory
{
    DWORD fnFindPatternIDA(const char *szModule, const char *szSignature)
    {
        MODULEINFO modInfo;
        K32GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
        DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
        DWORD endAddress = startAddress + modInfo.SizeOfImage;
        const char *pat = szSignature;
        DWORD firstMatch = 0;
        for (DWORD pCur = startAddress; pCur < endAddress; pCur++)
        {
            if (!*pat) return firstMatch;
            if (*(PBYTE)pat == '\?' || *reinterpret_cast<BYTE *>(pCur) == GETBYTE(pat))
            {
                if (!firstMatch) firstMatch = pCur;
                if (!pat[2]) return firstMatch;
                if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
                else pat += 2;    //one ?
            }
            else
            {
                pat = szSignature;
                firstMatch = 0;
            }
        }

        return 0;
    }

    DWORD __FindPatternIDA(DWORD startAddress, DWORD endAddress, const char *szSignature)
    {
        const char *pat = szSignature;
        DWORD firstMatch = 0;
        for (DWORD pCur = startAddress; pCur < endAddress; pCur++)
        {
            if (!*pat) return firstMatch;
            if (*(PBYTE)pat == '\?' || *reinterpret_cast<BYTE *>(pCur) == GETBYTE(pat))
            {
                if (!firstMatch) firstMatch = pCur;
                if (!pat[2]) return firstMatch;
                if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
                else pat += 2;    //one ?
            }
            else
            {
                pat = szSignature;
                firstMatch = 0;
            }
        }

        return 0;
    }

    DWORD fnFindPatternIDA(DWORD startAddress, DWORD endAddress, const char *szSignature)
    {
        MEMORY_BASIC_INFORMATION mbi;
        DWORD currentAddress = startAddress;
        do
        {
            if (!VirtualQueryEx(GetCurrentProcess(), reinterpret_cast<void *>(currentAddress), &mbi, sizeof(MEMORY_BASIC_INFORMATION))) break;
            if ((mbi.State == MEM_COMMIT) && (mbi.Protect == PAGE_EXECUTE_READ || mbi.Protect == PAGE_EXECUTE_READWRITE || mbi.Protect == PAGE_EXECUTE_WRITECOPY
                || mbi.Protect == PAGE_READONLY || mbi.Protect == PAGE_READWRITE || mbi.Protect == PAGE_WRITECOPY))
            {
                uint32_t memoryAddress = __FindPatternIDA(currentAddress, currentAddress + mbi.RegionSize, szSignature);
                if (memoryAddress) return memoryAddress;
            }
            currentAddress += mbi.RegionSize;

        } while (currentAddress < endAddress);

        return 0;
    }

    DWORD fnFindDMAAddy(DWORD ptr, std::vector<offset_t> offsets)
    {
        DWORD address = ptr;
        for (const auto &offset : offsets)
        {
            address = *(DWORD *)address;
            if (!address) return 0;

            address += offset;
        }

        return address;
    }

    bool fnIsMemoryReadable(void *ptr, size_t byteCount)
    {
        MEMORY_BASIC_INFORMATION mbi;
        if (VirtualQuery(ptr, &mbi, sizeof(MEMORY_BASIC_INFORMATION)) == 0)
            return false;

        if (mbi.State != MEM_COMMIT)
            return false;

        if (mbi.Protect == PAGE_NOACCESS || mbi.Protect == PAGE_EXECUTE)
            return false;

        // This checks that the start of memory block is in the same "region" as the
        // end. If it isn't you "simplify" the problem into checking that the rest of 
        // the memory is readable.
        size_t blockOffset = (size_t)((char *)ptr - (char *)mbi.AllocationBase);
        size_t blockBytesPostPtr = mbi.RegionSize - blockOffset;

        if (blockBytesPostPtr < byteCount)
            return fnIsMemoryReadable((char *)ptr + blockBytesPostPtr,
                byteCount - blockBytesPostPtr);

        return true;
    }

    void fnReplaceWithNop(DWORD *address, int length)
    {
        // 0x90 - nop (asm)
        memset(address, 0x90, length);
    }

    void fnReplaceWithNop(DWORD *address, BYTE *restoreBuf, int length)
    {
        memcpy(restoreBuf, address, length);
        memset(address, 0x90, length);
    }

    void fnReplaceWithBuffer(DWORD *address, BYTE *restoreBuf, BYTE *srcBuf, int length)
    {
        memcpy(restoreBuf, address, length);
        memcpy(address, srcBuf, length);
    }

    void xorString(char *data, const char *key)
    {
        for (size_t i = 0; i < strlen(data); ++i)
        {
            data[i] ^= i ^ key[i % strlen(key)];
        }
    }
};
