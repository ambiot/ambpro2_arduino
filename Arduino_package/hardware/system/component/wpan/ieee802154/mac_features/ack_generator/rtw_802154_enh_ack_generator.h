/* Copyright (c) 2018, Realtek
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   1. Redistributions of source code must retain the above copyright notice, this
 *      list of conditions and the following disclaimer.
 *
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 *   3. Neither the name of Realtek nor the names of its
 *      contributors may be used to endorse or promote products derived from
 *      this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * @brief Module that contains an enhanced acknowledgement (Enh-Ack) generator
 * for the 802.15.4 radio driver.
 *
 */

#ifndef RTW_802154_ENH_ACK_GENERATOR_H
#define RTW_802154_ENH_ACK_GENERATOR_H

#include <stdbool.h>
#include <stdint.h>

/** Initializes the Enhanced ACK generator module. */
void rtw_802154_enh_ack_generator_init(void);

/** Creates an Enhanced ACK in response to the provided frame.
 *
 * This function creates an Enhanced ACK frame and inserts it into a radio buffer.
 *
 * @param [in]  p_frame  Pointer to the buffer that contains PHR and PSDU of the frame
 *                       to respond to.
 *
 * @returns  Pointer to a constant buffer that contains PHR and PSDU
 *           of the created Enhanced ACK frame.
 */
uint8_t *rtw_802154_enh_ack_generator_create(const uint8_t *p_frame);

#endif // RTW_802154_ENH_ACK_GENERATOR_H
