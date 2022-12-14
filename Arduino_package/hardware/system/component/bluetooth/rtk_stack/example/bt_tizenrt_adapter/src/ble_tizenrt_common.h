/*
 * ble_tizenrt_common.h.c
 *
 *  Created on: 2020.5.18
 *  Author: lexi_zhao
 */

#ifndef _BLE_TIZENRT_COMMON_H_
#define _BLE_TIZENRT_COMMON_H_

typedef struct
{
  uint16_t type;
  union {
    uint32_t  param;
    void     *buf;
  } u;
} T_TIZENRT_APP_CALLBACK_MSG;

#endif
