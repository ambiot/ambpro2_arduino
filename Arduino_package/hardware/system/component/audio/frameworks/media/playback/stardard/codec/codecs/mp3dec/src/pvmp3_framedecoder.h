/* ------------------------------------------------------------------
 * Copyright (C) 1998-2009 PacketVideo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 * -------------------------------------------------------------------
 */
/*
------------------------------------------------------------------------------
   PacketVideo Corp.
   MP3 Decoder Library

   Filename: pvmp3_framedecoder.h

   Date: 09/21/2007

------------------------------------------------------------------------------
 REVISION HISTORY

 Description:

------------------------------------------------------------------------------
 INCLUDE DESCRIPTION

------------------------------------------------------------------------------
*/

/*----------------------------------------------------------------------------
; CONTINUE ONLY IF NOT ALREADY DEFINED
----------------------------------------------------------------------------*/
#ifndef PVMP3_FRAMEDECODER_H
#define PVMP3_FRAMEDECODER_H

/*----------------------------------------------------------------------------
; INCLUDES
----------------------------------------------------------------------------*/
#include "pvmp3_dec_defs.h"
#include "pvmp3_audio_type_defs.h"
#include "pvmp3decoder_api.h"
#include "s_mp3bits.h"

/*----------------------------------------------------------------------------
; MACROS
; Define module specific macros here
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; DEFINES
; Include all pre-processor statements here.
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; EXTERNAL VARIABLES REFERENCES
; Declare variables used in this module but defined elsewhere
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; SIMPLE TYPEDEF'S
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; ENUMERATED TYPEDEF'S
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; STRUCTURES TYPEDEF'S
----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
; GLOBAL FUNCTION DEFINITIONS
; Function Prototype declaration
----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C"
{
#endif


ERROR_CODE pvmp3_framedecoder(tPVMP3DecoderExternal *pExt,
							  void                  *pMem);



uint32 pvmp3_decoderMemRequirements(void);

void pvmp3_InitDecoder(tPVMP3DecoderExternal *pExt,
					   void  *pMem);


void pvmp3_resetDecoder(void                  *pMem);


void fillMainDataBuf(void  *pMem, int32 temp);


#ifdef __cplusplus
}
#endif

/*----------------------------------------------------------------------------
; END
----------------------------------------------------------------------------*/
#endif

