/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 11:16:04
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 12:14:36
 */

#ifndef _INSTANCE_SERVICE_H
#define _INSTANCE_SERVICE_H

#include "onenet_type.h"
#include "onenet_entity.h"

#ifdef __cplusplus
extern "C"
{
#endif

    extern int _instance_init(onenet_instance_t *instance);
    extern int _instance_deinit(onenet_instance_t *instance);

#ifdef __cplusplus
}
#endif
#endif // _INSTANCE_SERVICE_H
