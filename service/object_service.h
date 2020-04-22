/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 11:15:41
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:23:43
 */

#ifndef _OBJECT_SERVICE_H
#define _OBJECT_SERVICE_H

#include "onenet_type.h"
#include "onenet_entity.h"

#ifdef __cplusplus
extern "C"
{
#endif
    extern int _object_init(onenet_obj_t *object);
    extern int _object_deinit(onenet_obj_t *object);
		extern rt_list_t onenet_obj_g_list;

#ifdef __cplusplus
}
#endif
#endif // _OBJECT_SERVICE_H
