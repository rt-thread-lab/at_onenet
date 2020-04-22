/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 13:12:17
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:28:28
 */
#ifndef _INSTANCECONTROLLER_H
#define _INSTANCECONTROLLER_H

#include <rtthread.h>
#include "instance_service.h"

#define DBG_TAG "onenet"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef __cplusplus
extern "C"
{
#endif
    //curd

    extern onenet_instance_t *nb_onenet_create_instance(onenet_obj_t *obj);
    extern int nb_onenet_delete_instance(onenet_instance_t *instance);
    extern int nb_onenet_update_instance(onenet_instance_t *instance); //
    extern onenet_instance_t *nb_onenet_get_instance_ById(onenet_obj_t *obj, int insId);
    extern void nb_onenet_print_instances(onenet_obj_t *obj);
    extern onenet_instance_t *get_first_instance(onenet_obj_t *object);

    //base ops
    extern int nb_onenet_notify_instance(onenet_instance_t *instance);

#ifdef __cplusplus
}
#endif
#endif // _INSTANCECONTROLLER_H
