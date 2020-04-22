/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 11:15:50
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:22:49
 */
#include "object_service.h"
#include <rthw.h>

rt_list_t onenet_obj_g_list;

int _object_init(onenet_obj_t *object)
{
    register rt_base_t level;

    rt_list_init(&(object->ins_list));

    level = rt_hw_interrupt_disable();

    rt_list_insert_after(&onenet_obj_g_list, &(object->list));

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

int _object_deinit(onenet_obj_t *object)
{
    register rt_base_t level;

    rt_list_init(&(object->ins_list));

    level = rt_hw_interrupt_disable();

    rt_list_remove(&(object->list));

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}
