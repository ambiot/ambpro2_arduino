#ifndef _BT_MESH_APP_HTTP_INTF_H_
#define _BT_MESH_APP_HTTP_INTF_H_

typedef enum
{
	RTW_BT_MESH_CMD = 0x1,
	RTW_BT_MESH_EVENT = 0x2,
} T_MESH_CMD_EVENT_TYPE;

typedef enum
{
	RTW_BT_MESH_CMD_START_PROVISIONER = 0x1,
	RTW_BT_MESH_CMD_GET_UNPROVISIONED_DEVICE = 0x2,
	RTW_BT_MESH_CMD_CONNECT_DEVICE = 0x3,
	RTW_BT_MESH_CMD_DELETE_NODE = 0x4,
	RTW_BT_MESH_CMD_GET_NODE_STATUS = 0x5,
	RTW_BT_MESH_CMD_SET_NODE_STATE = 0x6,
	RTW_BT_MESH_CMD_SET_NODE_GROUP = 0x7,
    RTW_BT_MESH_CMD_SET_NODE_NAME = 0x8,
} T_MESH_CMD_TYPE;

typedef enum
{
	RTW_BT_MESH_EVENT_PROVISIONER_STATE = 0x1,
	RTW_BT_MESH_EVENT_UNPROVISIONED_DEVICE = 0x2,
	RTW_BT_MESH_EVENT_DEVICE_CONNECT_INFO = 0x3,
	RTW_BT_MESH_EVENT_NODE_DELETE_INFO = 0x4,
	RTW_BT_MESH_EVENT_NODE_STATUS = 0x5,
    RTW_BT_MESH_EVENT_DEVICE_INFO = 0x6,
} T_MESH_VENT_TYPE;

#endif

