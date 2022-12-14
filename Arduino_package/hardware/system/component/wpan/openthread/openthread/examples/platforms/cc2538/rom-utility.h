/*
 *  Copyright (c) 2016, The OpenThread Authors.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name of the copyright holder nor the
 *     names of its contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ROM_UTILITY_H_
#define ROM_UTILITY_H_

#define ROM_API_TABLE_ADDR 0x00000048

typedef uint32_t (*volatile FPTR_CRC32_T)(uint8_t * /*pData*/, uint32_t /*byteCount*/);
typedef uint32_t (*volatile FPTR_GETFLSIZE_T)(void);
typedef uint32_t (*volatile FPTR_GETCHIPID_T)(void);
typedef int32_t (*volatile FPTR_PAGEERASE_T)(uint32_t /*FlashAddr*/, uint32_t /*Size*/);
typedef int32_t (*volatile FPTR_PROGFLASH_T)(uint32_t * /*pRamData*/, uint32_t /*FlashAdr*/, uint32_t /*ByteCount*/);
typedef void (*volatile FPTR_RESETDEV_T)(void);
typedef void *(*volatile FPTR_MEMSET_T)(void * /*s*/, int32_t /*c*/, uint32_t /*n*/);
typedef void *(*volatile FPTR_MEMCPY_T)(void * /*s1*/, const void * /*s2*/, uint32_t /*n*/);
typedef int32_t (*volatile FPTR_MEMCMP_T)(const void * /*s1*/, const void * /*s2*/, uint32_t /*n*/);
typedef void *(*volatile FPTR_MEMMOVE_T)(void * /*s1*/, const void * /*s2*/, uint32_t /*n*/);

typedef struct {
	FPTR_CRC32_T     Crc32;
	FPTR_GETFLSIZE_T GetFlashSize;
	FPTR_GETCHIPID_T GetChipId;
	FPTR_PAGEERASE_T PageErase;
	FPTR_PROGFLASH_T ProgramFlash;
	FPTR_RESETDEV_T  ResetDevice;
	FPTR_MEMSET_T    memset;
	FPTR_MEMCPY_T    memcpy;
	FPTR_MEMCMP_T    memcmp;
	FPTR_MEMMOVE_T   memmove;
} ROM_API_T;

// clang-format off

#define P_ROM_API               ((ROM_API_T*)ROM_API_TABLE_ADDR)

#define ROM_Crc32(a,b)          P_ROM_API->Crc32(a,b)
#define ROM_GetFlashSize()      P_ROM_API->GetFlashSize()
#define ROM_GetChipId()         P_ROM_API->GetChipId()
#define ROM_PageErase(a,b)      P_ROM_API->PageErase(a,b)
#define ROM_ProgramFlash(a,b,c) P_ROM_API->ProgramFlash(a,b,c)
#define ROM_ResetDevice()       P_ROM_API->ResetDevice()
#define ROM_Memset(a,b,c)       P_ROM_API->memset(a,b,c)
#define ROM_Memcpy(a,b,c)       P_ROM_API->memcpy(a,b,c)
#define ROM_Memcmp(a,b,c)       P_ROM_API->memcmp(a,b,c)
#define ROM_Memmove(a,b,c)      P_ROM_API->memmove(a,b,c)

// clang-format on

#endif // ROM_UTILITY_H_
