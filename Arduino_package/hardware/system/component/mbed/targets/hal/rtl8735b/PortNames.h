/* mbed Microcontroller Library
  ******************************************************************************
  * @attention
  *
  * Copyright(c) 2006 - 2022 Realtek Corporation. All rights reserved.
  *
  * SPDX-License-Identifier: Apache-2.0
  *
  * Licensed under the Apache License, Version 2.0 (the License); you may
  * not use this file except in compliance with the License.
  * You may obtain a copy of the License at
  *
  * http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an AS IS BASIS, WITHOUT
  * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */
#ifndef MBED_PORTNAMES_H
#define MBED_PORTNAMES_H

#ifdef __cplusplus
extern "C" {
#endif
#include "rtl8735b_pin_name.h"
typedef enum {
	PortA   = PORT_A,
	PortB   = PORT_B,
	PortC   = PORT_C,
	PortD   = PORT_D,
	PortE   = PORT_E,
	PortF   = PORT_F,
	PortS   = PORT_S
} PortName;

#ifdef __cplusplus
}
#endif
#endif
