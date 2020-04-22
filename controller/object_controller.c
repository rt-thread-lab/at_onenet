/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 20:45:34
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 13:07:34
 */

#include "object_controller.h"

/**
 * @description: 
 * @param {type} 
 * @return: 
 */

extern struct onenet_device onenet_device_table;
onenet_obj_t *nb_onenet_create_object(int objId, int insCount, char *bitmap, int atts, int acts)
{
    onenet_obj_t *obj = RT_NULL;

    obj = (onenet_obj_t *)rt_calloc(1, sizeof(onenet_obj_t));

    if (obj != RT_NULL)
    {
        obj->objId = objId;
        obj->insCount = insCount;
        obj->bitmap = bitmap;
        obj->attrCount = atts;
        obj->actCount = acts;

        if (_object_init(obj) == RT_EOK)
        {
            onenet_device_table.objcount++;
            return obj;
        }
    }
    else
    {
        return RT_NULL;
    }
    return RT_NULL;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_delete_object(onenet_obj_t *obj)
{
    onenet_device_table.objcount--;
    return _object_deinit(obj);
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_update_object(onenet_obj_t *obj)
{
    //to do
    return RT_EOK;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
onenet_obj_t *nb_onenet_get_object_ById(int objId)
{
    rt_list_t *node;
    onenet_obj_t *tmp;
    rt_list_for_each(node, &onenet_obj_g_list)
    {
        tmp = rt_list_entry(node, onenet_obj_t, list);
        if (tmp->objId == objId)
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
void nb_onenet_print_all_object()
{
    rt_list_t *node;
    onenet_obj_t *tmp;
    rt_list_for_each(node, &onenet_obj_g_list)
    {
        tmp = rt_list_entry(node, onenet_obj_t, list);
        rt_kprintf("the object.objId is %d\n", tmp->objId);
    }
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
void nb_onenet_print_instance(onenet_obj_t *obj)
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
 * @description: notify all the res under this object
 * @param {type} 
 * @return: 
 */
int nb_onenet_notify_obj(onenet_obj_t *obj)
{
    //not recommand func

    return RT_EOK;
}
