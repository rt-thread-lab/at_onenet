/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 10:08:45
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-22 11:22:05
 */
#ifndef _ONENETCONTROLLER_H
#define _ONENETCONTROLLER_H

#include <rtthread.h>


#include "object_controller.h"
#include "instance_controller.h"
#include "resource_controller.h"

#define DBG_TAG "onenet"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define ONENET_EVENT_MSG_NUM 10
#define NB_ONENET_LIFE_TIME 3600
#define TIMEOUT_NORMAL 10000


#ifdef __cplusplus
extern "C"
{
#endif

    


    //base fun
    extern int nb_onenet_init_environment(void);
    extern rt_bool_t nb_onenet_is_inited(void);
    extern int nb_onenet_open(void);
    extern int nb_onenet_close(void);
    extern int nb_onenet_quick_start(void);
    extern int nb_onenet_get_connectiton_status(void);
    extern int nb_onenet_close(void);
    //
    extern int nb_onenet_update_time(int flag);
    //int nb_onenet_notify_with_ack(onenet_res_t *res, int len, nb_onenet_value_t data, int flag);

    //callback fun
    //extern int nb_onenet_close_callback(void);
    extern int nb_onenet_read_rsp_callback(int msgid, int objid, int insid, int resid);
    extern int nb_onenet_write_rsp_callback(int len, nb_onenet_value_t value);
    extern int nb_onenet_exec_rsp_callback(int len, char *cmd);
    extern void nb_onenet_fota_callback(void);

#ifdef __cplusplus
}
#endif
#endif // _ONENETCONTROLLER_H

