/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 16:39:36
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 11:26:33
 */

#include "resource_controller.h"
#include "bc26_onenet_port.h"
#include <rthw.h>


/**
 * @description: 
 * @param {type} 
 * @return: 
 */
onenet_res_t *nb_onenet_create_res(onenet_instance_t *instance, int resId, int valueType)
{
    onenet_res_t *res = RT_NULL;

    res = (onenet_res_t *)rt_calloc(1, sizeof(onenet_res_t));

    if (res != RT_NULL)
    {
        res->resId = resId;

        res->valueType = valueType;

        res->instance = instance;

        onenet_init_res_to_ins(res, instance);

        return res;
    }
    else
    {
        return RT_NULL;
    }
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_delete_res(onenet_res_t *res)
{
    register rt_base_t level;

    level = rt_hw_interrupt_disable();

    rt_list_remove(&(res->list));

    rt_hw_interrupt_enable(level);

    rt_free(res);

    return RT_EOK;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_update_res(onenet_res_t *res)
{
    //to do
	return RT_EOK;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
onenet_res_t *nb_onenet_get_res_ById(onenet_instance_t *instance, int resId)
{
    rt_list_t *node;
    onenet_res_t *tmp;
    rt_list_for_each(node, &(instance->onenet_res_list))
    {
        tmp = rt_list_entry(node, onenet_res_t, list);
        if (resId == tmp->resId)
        {
            return tmp;
        }
    }
    return RT_NULL;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void nb_onenet_print_all_res(onenet_instance_t *instance)
{
    rt_list_t *node;
    onenet_res_t *tmp;
    rt_list_for_each(node, &(instance->onenet_res_list))
    {
        tmp = rt_list_entry(node, onenet_res_t, list);
        rt_kprintf("the res.resId is %d \n", tmp->resId);
    }
}

//base ops
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_notify_res(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int index)
{
#ifdef BC26_USE_ONENET_PROTOCOL
    if (bc26_at_onenet_notify(res, len, data, flag) != RT_EOK)
    {
        LOG_E("onenet notify failed");
        return -RT_ERROR;
    }
    return RT_EOK;
#endif
}

