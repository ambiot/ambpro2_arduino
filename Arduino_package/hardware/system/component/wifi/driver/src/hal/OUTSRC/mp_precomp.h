/******************************************************************************
 *
 * Copyright(c) 2007 - 2011 Realtek Corporation. All rights reserved.
 *                                        
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/
#ifndef __MP_PRECOMP_H__
#define __MP_PRECOMP_H__

#include <drv_types.h>
#include <hal_data.h>

#define BT_TMP_BUF_SIZE	100

#ifdef CONFIG_BT_COEXIST
#define BT_SUPPORT		1
#define COEX_SUPPORT	1
#define HS_SUPPORT		1

#define rsprintf			snprintf
#define DCMD_Printf			DBG_BT_INFO
#define delay_ms(ms)		rtw_mdelay_os(ms)

typedef enum _BTC_MSG_COMP_TYPE {
	COMP_COEX		= 0,
	COMP_MAX
} BTC_MSG_COMP_TYPE;

#include "halbtcoutsrc.h"
#include "halbtc8195a1ant.h"
#include "halbtc8195a2ant.h"

#else
#define BT_SUPPORT		0
#define COEX_SUPPORT	0
#define HS_SUPPORT		0
#endif

#endif /*  __MP_PRECOMP_H__ */


