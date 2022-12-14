/**
*****************************************************************************************
*     Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
*****************************************************************************************
   * @file      bt_config_app_task.h
   * @brief     Routines to create App task and handle events & messages
   * @author
   * @date
   * @version
   **************************************************************************************
   * @attention
   * <h2><center>&copy; COPYRIGHT 2017 Realtek Semiconductor Corporation</center></h2>
   **************************************************************************************
  */
#ifndef _RMESH_BT_CONFIG_APP_TASK_H_
#define _RMESH_BT_CONFIG_APP_TASK_H_

/**
 * @brief  Initialize App task
 * @return void
 */
void rmesh_bt_config_send_msg(uint16_t sub_type);
void rmesh_bt_config_app_task_init(void);
void rmesh_bt_config_app_task_deinit(void);
#endif
