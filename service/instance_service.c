/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 11:16:12
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:20:09
 */

#include "instance_service.h"

#include <rthw.h>
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int _instance_init(onenet_instance_t *instance)
{
    register rt_base_t level;

    rt_list_init(&(instance->onenet_res_list));

    level = rt_hw_interrupt_disable();

    rt_list_insert_after(&(instance->obj->ins_list), &(instance->list));

    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

int _instance_deinit(onenet_instance_t *instance)
{
    register rt_base_t level;

    level = rt_hw_interrupt_disable();

    rt_list_remove(&(instance->list));

    rt_hw_interrupt_enable(level);

    rt_free(instance);

    return RT_EOK;
}
