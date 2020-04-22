/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 13:12:29
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:27:58
 */
#ifndef _RESOURCECONTROLLER_H
#define _RESOURCECONTROLLER_H

#include <rtthread.h>


#include "resource_service.h"

#define DBG_TAG "onenet"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef __cplusplus
extern "C"
{
#endif
    //curd
    extern onenet_res_t *nb_onenet_create_res(onenet_instance_t *instance, int resId, int valueType);
    extern int nb_onenet_delete_res(onenet_res_t *res);
    extern int nb_onenet_update_res(onenet_res_t *res);
    extern onenet_res_t *nb_onenet_get_res_ById(onenet_instance_t *instance, int resId);
    extern void nb_onenet_print_all_res(onenet_instance_t *instance);

    //base ops
    extern int nb_onenet_notify_res(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int index);
    extern int nb_onenet_notify_res_with_ack(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int index);

#ifdef __cplusplus
}
#endif
#endif // _RESOURCECONTROLLER_H

