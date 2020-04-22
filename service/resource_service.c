/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-21 11:16:24
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:26:40
 */

#include "resource_service.h"
#include <rthw.h>

int onenet_init_res_to_ins(onenet_res_t *res, onenet_instance_t *instance)
{
    register rt_base_t level;
    level = rt_hw_interrupt_disable();
    rt_list_insert_after(&(instance->onenet_res_list), &(res->list));
    rt_hw_interrupt_enable(level);
    return RT_EOK;
}

