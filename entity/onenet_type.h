/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 10:10:34
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 13:02:23
 */

#ifndef _ONENET_TYPE_H
#define _ONENET_TYPE_H

#include <rtthread.h>

#ifdef __cplusplus
extern "C"
{
#endif
    enum nb_onenet_value_type
    {
        nb_onenet_value_string = 1,
        nb_onenet_value_opaque,
        nb_onenet_value_integer,
        nb_onenet_value_float,
        nb_onenet_value_bool,
    };

    enum nb_onenet_status_type
    {
        nb_onenet_status_init = 0,
        nb_onenet_status_run,
        nb_onenet_status_failure,
        nb_onenet_status_success = 4,
        nb_onenet_status_close_init = 0,
        nb_onenet_status_close_start,
        nb_onenet_status_update_init = 10,
        nb_onenet_status_update_failure,
        nb_onenet_status_update_success,
        nb_onenet_status_update_timeout = 14,
        nb_onenet_status_update_need = 18,
        nb_onenet_status_result_read_success = 1,
        nb_onenet_status_result_write_success,
        nb_onenet_status_result_Bad_Request = 11,
        nb_onenet_status_result_Unauthorized,
        nb_onenet_status_result_Not_Found,
        nb_onenet_status_result_Method_Not_Allowed,
        nb_onenet_status_result_Not_Acceptable
    };

    union nb_onenet_value {
        char *string_value;
        rt_uint32_t int_value;
        float float_value;
        rt_bool_t bool_value;
    };
    typedef union nb_onenet_value *nb_onenet_value_t;

    typedef enum
    {
        ONENET_EVENT_SRC_NONE,
        ONENET_EVENT_SRC_DISCOVER,
        ONENET_EVENT_SRC_OBSERVE,
        ONENET_EVENT_SRC_WRITE,
        ONENET_EVENT_SRC_READ,
        ONENET_EVENT_SRC_EXECUTE
    } onenet_event_src_t;

    typedef struct _onenet_msg
    {
        int msgId;
        int objId;
        int insId;
        int resId;
        int valueType;
        int len;
        int flag;
        char *data;

    } onenet_msg_type_t;

    typedef struct _event
    {
        onenet_event_src_t event_src;
        onenet_msg_type_t type;
    } onenet_event_t;

    typedef struct _event_msg
    {
        onenet_event_t event;

    } onenet_event_msg_t;

#ifdef __cplusplus
}
#endif
#endif // _ONENET_TYPE_H
