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
#ifndef __RTL8723D_HAL_H__
#define __RTL8723D_HAL_H__

#include "hal_data.h"

#include "rtl8723d_spec.h"
#include "rtl8723d_rf.h"
#include "rtl8723d_dm.h"
#include "rtl8723d_recv.h"
#include "rtl8723d_xmit.h"
#include "rtl8723d_cmd.h"
#include "Hal8723DPwrSeq.h"
#include "Hal8723DPhyReg.h"
#include "Hal8723DPhyCfg.h"
#ifdef DBG_CONFIG_ERROR_DETECT
#include "rtl8723d_sreset.h"
#endif

#include "../phydm/phydm_precomp.h" //frankieodm add ODMLJM
//---------------------------------------------------------------------
//		RTL8723D From file
//---------------------------------------------------------------------
#define RTL8723D_FW_IMG					"rtl8723d/FW_NIC.bin"
#define RTL8723D_FW_WW_IMG				"rtl8723d/FW_WoWLAN.bin"
#define RTL8723D_PHY_REG					"rtl8723d/PHY_REG.txt"
#define RTL8723D_PHY_RADIO_A				"rtl8723d/RadioA.txt"
#define RTL8723D_PHY_RADIO_B				"rtl8723d/RadioB.txt"
#define RTL8723D_TXPWR_TRACK				"rtl8723d/TxPowerTrack.txt"
#define RTL8723D_AGC_TAB					"rtl8723d/AGC_TAB.txt"
#define RTL8723D_PHY_MACREG 				"rtl8723d/MAC_REG.txt"
#define RTL8723D_PHY_REG_PG				"rtl8723d/PHY_REG_PG.txt"
#define RTL8723D_PHY_REG_MP				"rtl8723d/PHY_REG_MP.txt"
#define RTL8723D_TXPWR_LMT 				"rtl8723d/TXPWR_LMT.txt"

//---------------------------------------------------------------------
//		RTL8723D From header
//---------------------------------------------------------------------

#if MP_DRIVER == 1
#define Rtl8723D_FwBTImgArray				Rtl8723DFwBTImgArray
#define Rtl8723D_FwBTImgArrayLength		Rtl8723DFwBTImgArrayLength

#define Rtl8723D_FwMPImageArray			Rtl8723DFwMPImgArray
#define Rtl8723D_FwMPImgArrayLength		Rtl8723DMPImgArrayLength

#define Rtl8723D_PHY_REG_Array_MP			Rtl8723D_PHYREG_Array_MP
#define Rtl8723D_PHY_REG_Array_MPLength	Rtl8723D_PHYREG_Array_MPLength
#endif


#define FW_8723D_SIZE			0x8000
#define FW_8723D_START_ADDRESS	0x1000
#define FW_8723D_END_ADDRESS		0x1FFF //0x5FFF

#define IS_FW_HEADER_EXIST_8723D(_pFwHdr)	((le16_to_cpu(_pFwHdr->Signature)&0xFFF0) ==0x23D0)

typedef struct _RT_FIRMWARE {
	FIRMWARE_SOURCE	eFWSource;
	u8			*szFwBuffer;
	u32			ulFwLength;
} RT_FIRMWARE_8723D, *PRT_FIRMWARE_8723D;

#ifdef CONFIG_GPIO_WAKEUP
#define WAKEUP_GPIO_IDX	0//frankie_aaa need to modify
#endif
//
// This structure must be cared byte-ordering
//
// Added by tynli. 2009.12.04.
typedef struct _RT_8723D_FIRMWARE_HDR {
	// 8-byte alinment required

	//--- LONG WORD 0 ----
	u16		Signature;	// 92C0: test chip; 92C, 88C0: test chip; 88C1: MP A-cut; 92C1: MP A-cut
	u8		Category;	// AP/NIC and USB/PCI
	u8		Function;	// Reserved for different FW function indcation, for further use when driver needs to download different FW in different conditions
	u16		Version;		// FW Version
	u16		Subversion;	// FW Subversion, default 0x00

	//--- LONG WORD 1 ----
	u8		Month;	// Release time Month field
	u8		Date;	// Release time Date field
	u8		Hour;	// Release time Hour field
	u8		Minute;	// Release time Minute field
	u16		RamCodeSize;	// The size of RAM code
	u16		Rsvd2;

	//--- LONG WORD 2 ----
	u32		SvnIdx;	// The SVN entry index
	u32		Rsvd3;

	//--- LONG WORD 3 ----
	u32		Rsvd4;
	u32		Rsvd5;
} RT_8723D_FIRMWARE_HDR, *PRT_8723D_FIRMWARE_HDR;

#define DRIVER_EARLY_INT_TIME_8723D		0x05
#define BCN_DMA_ATIME_INT_TIME_8723D		0x02

// for 8723D
// TX 32K, RX 16K, Page size 128B for TX, 8B for RX
#define PAGE_SIZE_TX_8723D			128
#define PAGE_SIZE_RX_8723D			8

#define RX_DMA_SIZE_8723D			0x4000	// 16K
#ifdef CONFIG_FW_C2H_DEBUG
#define RX_DMA_RESERVED_SIZE_8723D	0x100	// 256B, reserved for c2h debug message
#else
#define RX_DMA_RESERVED_SIZE_8723D	0x80	// 128B, reserved for tx report
#endif
#define RX_DMA_BOUNDARY_8723D		(RX_DMA_SIZE_8723D - RX_DMA_RESERVED_SIZE_8723D - 1)

#ifdef CONFIG_WOWLAN
#define MAX_WKFM_NUM 16
#define WKFMCAM_SIZE 24
#define RESV_FMWF	WKFMCAM_SIZE*MAX_WKFM_NUM /* 16 entries, for each is 24 bytes*/
#else
#define RESV_FMWF	0
#endif
// Note: We will divide number of page equally for each queue other than public queue!

//For General Reserved Page Number(Beacon Queue is reserved page)
//Beacon:2, PS-Poll:1, Null Data:1,Qos Null Data:1,BT Qos Null Data:1
#define BCNQ_PAGE_NUM_8723D		0x08
#ifdef CONFIG_CONCURRENT_MODE
#define BCNQ1_PAGE_NUM_8723D		0x08 // 0x04
#else
#define BCNQ1_PAGE_NUM_8723D		0x00
#endif

#ifdef CONFIG_PNO_SUPPORT
#undef BCNQ1_PAGE_NUM_8723D
#define BCNQ1_PAGE_NUM_8723D		0x00 // 0x04
#endif
#define MAX_RX_DMA_BUFFER_SIZE_8723D	0x2800	// RX 10K

//For WoWLan , more reserved page
//ARP Rsp:1, RWC:1, GTK Info:1,GTK RSP:2,GTK EXT MEM:2, PNO: 6
#ifdef CONFIG_WOWLAN
#define WOWLAN_PAGE_NUM_8723D	0x07
#else
#define WOWLAN_PAGE_NUM_8723D	0x00
#endif

#ifdef CONFIG_PNO_SUPPORT
#undef WOWLAN_PAGE_NUM_8723D
#define WOWLAN_PAGE_NUM_8723D	0x15
#endif

#ifdef CONFIG_AP_WOWLAN
#define AP_WOWLAN_PAGE_NUM_8723D	0x02
#endif

#define TX_TOTAL_PAGE_NUMBER_8723D	(0xFF - BCNQ_PAGE_NUM_8723D - BCNQ1_PAGE_NUM_8723D - WOWLAN_PAGE_NUM_8723D)
#define TX_PAGE_BOUNDARY_8723D		(TX_TOTAL_PAGE_NUMBER_8723D + 1)

#define WMM_NORMAL_TX_TOTAL_PAGE_NUMBER_8723D	TX_TOTAL_PAGE_NUMBER_8723D
#define WMM_NORMAL_TX_PAGE_BOUNDARY_8723D		(WMM_NORMAL_TX_TOTAL_PAGE_NUMBER_8723D + 1)

// For Normal Chip Setting
// (HPQ + LPQ + NPQ + PUBQ) shall be TX_TOTAL_PAGE_NUMBER_8723D
#define NORMAL_PAGE_NUM_HPQ_8723D		0x0C
#define NORMAL_PAGE_NUM_LPQ_8723D		0x02
#define NORMAL_PAGE_NUM_NPQ_8723D		0x02
#define NORMAL_PAGE_NUM_EPQ_8723D		0x04

// Note: For Normal Chip Setting, modify later
#define WMM_NORMAL_PAGE_NUM_HPQ_8723D		0x30
#define WMM_NORMAL_PAGE_NUM_LPQ_8723D		0x20
#define WMM_NORMAL_PAGE_NUM_NPQ_8723D		0x20
#define WMM_NORMAL_PAGE_NUM_EPQ_8723D		0x00

#include "HalVerDef.h"
#include "hal_com.h"

#define EFUSE_OOB_PROTECT_BYTES 		(96 + 1)

#define HWSET_MAX_SIZE_8723D			512
#define EFUSE_REAL_CONTENT_LEN_8723D		512
#define EFUSE_MAP_LEN_8723D				512
#define EFUSE_MAX_SECTION_8723D			64

#define EFUSE_IC_ID_OFFSET			506	//For some inferiority IC purpose. added by Roger, 2009.09.02.
#define AVAILABLE_EFUSE_ADDR(addr) 	(addr < EFUSE_REAL_CONTENT_LEN_8723D)

#define EFUSE_ACCESS_ON			0x69	// For RTL8188 only.
#define EFUSE_ACCESS_OFF			0x00	// For RTL8188 only.

//========================================================
//			EFUSE for BT definition
//========================================================
#define BANK_NUM			1
#define EFUSE_BT_REAL_BANK_CONTENT_LEN	128
#define EFUSE_BT_REAL_CONTENT_LEN	\
	(EFUSE_BT_REAL_BANK_CONTENT_LEN * BANK_NUM)
#define EFUSE_BT_MAP_LEN		1024	/* 1k bytes */
#define EFUSE_BT_MAX_SECTION		(EFUSE_BT_MAP_LEN / 8)

#define EFUSE_PROTECT_BYTES_BANK		16



typedef enum tag_Package_Definition {
	PACKAGE_DEFAULT,
	PACKAGE_QFN68,
	PACKAGE_TFBGA90,
	PACKAGE_TFBGA80,
	PACKAGE_TFBGA79
} PACKAGE_TYPE_E;

#define INCLUDE_MULTI_FUNC_BT(_Adapter)		(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_BT)
#define INCLUDE_MULTI_FUNC_GPS(_Adapter)	(GET_HAL_DATA(_Adapter)->MultiFunc & RT_MULTI_FUNC_GPS)

#define GET_RF_TYPE(priv)			(GET_HAL_DATA(priv)->rf_type)
#define GET_HAL_DATA(__pAdapter)	((HAL_DATA_TYPE *)((__pAdapter)->HalData))
// rtl8188a_hal_init.c
s32 rtl8723d_FirmwareDownload(PADAPTER padapter, BOOLEAN  bUsedWoWLANFw);
void rtl8723d_FirmwareSelfReset(PADAPTER padapter);
void rtl8723d_InitializeFirmwareVars(PADAPTER padapter);

void rtl8723d_InitAntenna_Selection(PADAPTER padapter);
void rtl8723d_DeinitAntenna_Selection(PADAPTER padapter);
void rtl8723d_CheckAntenna_Selection(PADAPTER padapter);
void rtl8723d_init_default_value(PADAPTER padapter);

s32 rtl8723d_InitLLTTable(PADAPTER padapter);

s32 CardDisableHWSM(PADAPTER padapter, u8 resetMCU);
s32 CardDisableWithoutHWSM(PADAPTER padapter);

// EFuse
u8 GetEEPROMSize8723D(PADAPTER padapter);
void Hal_InitPGData(PADAPTER padapter, u8 *PROMContent);
void Hal_EfuseParseIDCode(PADAPTER padapter, u8 *hwinfo);
void Hal_EfuseParseTxPowerInfo_8723D(PADAPTER padapter, u8 *PROMContent, BOOLEAN AutoLoadFail);
void Hal_EfuseParseBTCoexistInfo_8723D(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseEEPROMVer_8723D(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseChnlPlan_8723D(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseCustomerID_8723D(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseAntennaDiversity_8723D(PADAPTER padapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
void Hal_EfuseParseXtal_8723D(PADAPTER pAdapter, u8 *hwinfo, u8 AutoLoadFail);
void Hal_EfuseParseThermalMeter_8723D(PADAPTER padapter, u8 *hwinfo, u8 AutoLoadFail);
VOID Hal_EfuseParsePackageType_8723D(PADAPTER pAdapter, u8 *hwinfo, BOOLEAN AutoLoadFail);
VOID Hal_EfuseParseVoltage_8723D(PADAPTER pAdapter, u8 *hwinfo, BOOLEAN 	AutoLoadFail);
VOID Hal_EfuseParseBoardType_8723D(PADAPTER Adapter, u8	*PROMContent, BOOLEAN AutoloadFail);

#ifdef CONFIG_C2H_PACKET_EN
void rtl8723d_c2h_packet_handler(PADAPTER padapter, u8 *pbuf, u16 length);
#endif


void rtl8723d_set_hal_ops(struct hal_ops *pHalFunc);
void SetHwReg8723D(PADAPTER padapter, u8 variable, u8 *val);
void GetHwReg8723D(PADAPTER padapter, u8 variable, u8 *val);
#ifdef CONFIG_C2H_PACKET_EN
void SetHwRegWithBuf8723D(PADAPTER padapter, u8 variable, u8 *pbuf, int len);
#endif // CONFIG_C2H_PACKET_EN
u8 SetHalDefVar8723D(PADAPTER padapter, HAL_DEF_VARIABLE variable, void *pval);
u8 GetHalDefVar8723D(PADAPTER padapter, HAL_DEF_VARIABLE variable, void *pval);

// register
void rtl8723d_InitBeaconParameters(PADAPTER padapter);
void rtl8723d_InitBeaconMaxError(PADAPTER padapter, u8 InfraMode);
void	_InitBurstPktLen_8723DS(PADAPTER Adapter);
void _8051Reset8723(PADAPTER padapter);
#ifdef CONFIG_WOWLAN
void Hal_DetectWoWMode(PADAPTER pAdapter);
void rtw_get_current_ip_address(PADAPTER padapter, u8 *pcurrentip);
void rtw_get_sec_iv(PADAPTER padapter, u8 *pcur_dot11txpn, u8 *StaAddr);
#endif //CONFIG_WOWLAN
void rtw_set_sec_pn(PADAPTER padapter);
void rtl8723d_start_thread(_adapter *padapter);
void rtl8723d_stop_thread(_adapter *padapter);

#if defined(CONFIG_CHECK_BT_HANG) && defined(CONFIG_BT_COEXIST)
void rtl8723ds_init_checkbthang_workqueue(_adapter *adapter);
void rtl8723ds_free_checkbthang_workqueue(_adapter *adapter);
void rtl8723ds_cancle_checkbthang_workqueue(_adapter *adapter);
void rtl8723ds_hal_check_bt_hang(_adapter *adapter);
#endif

#ifdef CONFIG_GPIO_WAKEUP
void HalSetOutPutGPIO(PADAPTER padapter, u8 index, u8 OutPutValue);
#endif
#ifdef CONFIG_MP_INCLUDED
#ifdef CONFIG_BT_COEXIST
int FirmwareDownloadBT(IN PADAPTER Adapter, PRT_MP_FIRMWARE pFirmware);
#endif
#endif
void CCX_FwC2HTxRpt_8723d(PADAPTER padapter, u8 *pdata, u8 len);
#ifdef CONFIG_FW_C2H_DEBUG
void Debug_FwC2H_8723d(PADAPTER padapter, u8 *pdata, u8 len);
#endif //CONFIG_FW_C2H_DEBUG
s32 c2h_id_filter_ccx_8723d(u8 *buf);
s32 c2h_handler_8723d(PADAPTER padapter, u8 *pC2hEvent);
u8 MRateToHwRate8723D(u8  rate);
u8 HwRateToMRate8723D(u8	 rate);

#ifdef CONFIG_PCI_HCI
BOOLEAN	InterruptRecognized8723DE(PADAPTER Adapter);
VOID	UpdateInterruptMask8723DE(PADAPTER Adapter, u32 AddMSR, u32 AddMSR1, u32 RemoveMSR, u32 RemoveMSR1);
#endif
extern void InitInterrupt8723DSdio(PADAPTER padapter);
extern void InitSysInterrupt8723DSdio(PADAPTER padapter);
extern void EnableInterrupt8723DSdio(PADAPTER padapter);
extern void DisableInterrupt8723DSdio(PADAPTER padapter);
extern s32  rtl8723d_interrupt_handler(PADAPTER padapter);
extern void rtl8723d_read_chip_version(PADAPTER padapter);
extern void UpdateHalRAMask8723D(PADAPTER padapter, u32 mac_id, u8 rssi_level);
void rtl8723d_SetBeaconRelatedRegisters(PADAPTER padapter);
//void rtl8723d_Add_RateATid(PADAPTER pAdapter, u64 bitmap, u8* arg, u8 rssi_level);
void rtl8723d_recv_tasklet(void *priv);
void rtl8723d_free_hal_data(_adapter *padapter);
void Hal_EfusePowerSwitch(PADAPTER	padapter, u8 bWrite, u8 PwrState);
void
Hal_ReadEFuse(
	PADAPTER	padapter,
	u8			efuseType,
	u16			_offset,
	u16			_size_byte,
	u8			*pbuf,
	u8			bPseudoTest);
void
Hal_GetEfuseDefinition(
	PADAPTER	padapter,
	u8			efuseType,
	u8			type,
	void		*pOut,
	u8			bPseudoTest);
u16
Hal_EfuseGetCurrentSize(
	PADAPTER	pAdapter,
	u8			efuseType,
	u8			bPseudoTest);
s32
Hal_EfusePgPacketRead(
	PADAPTER	padapter,
	u8			offset,
	u8			*data,
	u8			bPseudoTest);
s32
Hal_EfusePgPacketWrite(
	PADAPTER	padapter,
	u8 			offset,
	u8			word_en,
	u8			*pData,
	u8			bPseudoTest);
u8
Hal_EfuseWordEnableDataWrite(
	PADAPTER	padapter,
	u16			efuse_addr,
	u8			word_en,
	u8			*data,
	u8			bPseudoTest);

u8
rtw_config_map_read(
	PADAPTER	 padapter,
	u16			 addr,
	u16 			cnts,
	u8 			*data,
	u8 			efuse);

u8
rtw_config_map_write(
	PADAPTER	 padapter,
	u16			 addr,
	u16 			cnts,
	u8 			*data,
	u8 			efuse);

void rtl8723d_GetHalODMVar(
	PADAPTER				Adapter,
	HAL_ODM_VARIABLE		eVariable,
	PVOID					pValue1,
	PVOID					pValue2);
void rtl8723d_SetHalODMVar(
	PADAPTER				Adapter,
	HAL_ODM_VARIABLE		eVariable,
	PVOID					pValue1,
	BOOLEAN					bSet);
void hal_notch_filter_8723d(_adapter *adapter, bool enable);
extern u8 HalQueryTxBufferStatus8723DSdio(PADAPTER padapter);
extern u8 HalQueryTxOQTBufferStatus8723DSdio(PADAPTER padapter);
#if defined(CONFIG_WOWLAN) || defined(CONFIG_AP_WOWLAN)
extern void DisableInterruptButCpwm28723DSdio(PADAPTER padapter);
extern void ClearInterrupt8723DSdio(PADAPTER padapter);
#endif

#endif

