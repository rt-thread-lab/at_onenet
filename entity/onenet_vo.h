/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 10:13:10
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 10:35:11
 */

#ifndef _ONENET_VO_H
#define _ONENET_VO_H

#include <rtthread.h>
#include "onenet_type.h"
#ifdef __cplusplus
extern "C"
{
#endif
    /* onenet vo  begin */
    struct bc26_onenet_add_obj
    {
        rt_uint16_t ref;
        int objId;
        int insCount;
        char *bitMap;
        int attrCount;
        int actCount;
    };
    typedef struct bc26_onenet_add_obj *bc26_onenet_add_obj_t;

    struct bc26_onenet_ob_rsp
    {
        int msgId;
        int result;
    };

    typedef struct bc26_onenet_ob_rsp *bc26_onenet_ob_rsp_t;

    struct bc26_onenet_dis_rsp
    {
        int msgId;
        int result;
        int resource_ids_size;
        char *resource_ids;
    };

    typedef struct bc26_onenet_dis_rsp *bc26_onenet_dis_rsp_t;

    struct bc26_onenet_notify_data
    {
        int msgId;
        int objId;
        int insId;
        int resId;
        int valueType;
        int len;
        nb_onenet_value_t data;
        int index;
        int flag;
        int ackId;
    };
    typedef struct bc26_onenet_notify_data *bc26_onenet_notify_data_t;

    struct bc26_onenet_writersp
    {
        int msgId;
        int result;
    };
    typedef struct bc26_onenet_writersp *bc26_onenet_writersp_t;

    struct bc26_onenet_executersp
    {
        int msgId;
        int result;
    };
    typedef struct bc26_onenet_executersp *bc26_onenet_executersp_t;

    struct bc26_onenet_readrsp
    {
        int msgId;
        int result;
        int objId;
        int insId;
        int resId;
        int valueType;
        int len;
        nb_onenet_value_t data;
        int index;
        int flag;
    };
    typedef struct bc26_onenet_readrsp *bc26_onenet_readrsp_t;
/* onenet vo end*/
#ifdef __cplusplus
}
#endif
#endif // _ONENET_VO_H

