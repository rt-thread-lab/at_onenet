/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 12:50:39
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:28:21
 */
#ifndef _OBJECTCONTROLLER_H
#define _OBJECTCONTROLLER_H

#include <rtthread.h>


#include "object_service.h"


#define DBG_TAG "onenet"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef __cplusplus
extern "C"
{
#endif
    //curd
    extern onenet_obj_t *nb_onenet_create_object(int objId, int insCount, char *bitmap, int atts, int acts);
    extern int nb_onenet_delete_object(onenet_obj_t *obj);
    extern int nb_onenet_update_object(onenet_obj_t *obj);
    extern onenet_obj_t *nb_onenet_get_object_ById(int objId);
    extern void nb_onenet_print_all_object(void);
    extern void nb_onenet_print_instance(onenet_obj_t *obj);
    //base ops
    extern int nb_onenet_notify_obj(onenet_obj_t *obj);

#ifdef __cplusplus
}
#endif
#endif // _OBJECTCONTROLLER_H

