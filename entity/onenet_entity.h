/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 10:12:35
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 13:05:57
 */

#ifndef _ONENET_ENTITY_H
#define _ONENET_ENTITY_H

#include <rtthread.h>

#define BC26_USE_ONENET_PROTOCOL

#ifdef __cplusplus
extern "C"
{
#endif

    struct onenet_device
    {
        int lifetime;
        int initstep;
        int event_status;
        int observer_status;
        int discover_status;
        int update_status;
        int update_time;
        int read_status;
        int write_status;
        int exec_status;
        int notify_status;
        int connect_status;
        int close_status;
        int notify_ack;
        int objcount;
        int inscount;
        int observercount;
        int discovercount;
    };

    struct _onenet_instance;
    typedef struct _onenet_resource
    {
        int resId;
        int valueType;
        struct _onenet_instance *instance;
        rt_list_t list;
    } onenet_res_t;

    typedef struct _onenet_obj
    {
        int objId;
        int observe_msgId;  // observe 返回的id
        int discover_msgId; //discover 返回的id
        int insCount;       //
        char *bitmap;
        int attrCount;
        int actCount;
        rt_list_t list;
        rt_list_t ins_list;

    } onenet_obj_t;

    typedef struct _onenet_instance
    {
        int insId;
        rt_list_t list;
        onenet_obj_t *obj;
        rt_list_t onenet_res_list; //list head for resources
    } onenet_instance_t;

#ifdef __cplusplus
}
#endif
#endif // _ONENET_ENTITY_H
