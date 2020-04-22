/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 16:50:42
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 12:16:29
 */

#include "instance_controller.h"


/**
 * @description: 
 * @param {type} 
 * @return: 
 */
onenet_instance_t *nb_onenet_create_instance(onenet_obj_t *obj)
{
    onenet_instance_t *instance = RT_NULL;

    instance = (onenet_instance_t *)rt_calloc(1, sizeof(onenet_instance_t));

    if (instance != RT_NULL)
    {
        instance->obj = obj;
				
        int len = rt_list_len(&(obj->ins_list));

        instance->insId = len;

        _instance_init(instance);

        return instance;
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
int nb_onenet_delete_instance(onenet_instance_t *instance)
{
    return _instance_deinit(instance);
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_update_instance(onenet_instance_t *instance)
{
    //to do
	return RT_EOK;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
onenet_instance_t *nb_onenet_get_instance_ById(onenet_obj_t *obj, int insId)
{
    rt_list_t *node;
    onenet_instance_t *tmp;
    rt_list_for_each(node, &(obj->ins_list))
    {
        tmp = rt_list_entry(node, onenet_instance_t, list);
        if (tmp->insId == insId)
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
onenet_instance_t *get_first_instance(onenet_obj_t *object)
{
    return rt_list_first_entry(&(object->ins_list), onenet_instance_t, list);
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void nb_onenet_print_instances(onenet_obj_t *obj)
{
    rt_list_t *node;
    onenet_instance_t *tmp;
    rt_list_for_each(node, &(obj->ins_list))
    {
        tmp = rt_list_entry(node, onenet_instance_t, list);
        rt_kprintf("the instance.insId is %d\n", tmp->insId);
    }
}

//base ops
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_notify_instance(onenet_instance_t *instance)
{
    return RT_EOK;
}
