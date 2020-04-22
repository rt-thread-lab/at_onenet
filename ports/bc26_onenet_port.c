/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 16:29:04
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-22 11:15:50
 */

#include "bc26_onenet_port.h"

#ifdef BC26_USE_ONENET_PROTOCOL

struct at_device_bc26 _dev =
    {
        BC26_SAMPLE_DEIVCE_NAME,
        BC26_SAMPLE_CLIENT_NAME,

        BC26_SAMPLE_POWER_PIN,
        BC26_SAMPLE_STATUS_PIN,
        BC26_SAMPLE_RECV_BUFF_LEN,
};

int bc26_connect_onenet(void)
{
    struct at_device_bc26 *bc26 = &_dev;
    int *arg = 0;
    return at_device_control(&(bc26->device), BC26_ONENET_CREATE, arg);
}

int bc26_close_onenet(void)
{
    struct at_device_bc26 *bc26 = &_dev;
    int *arg = 0;
    return at_device_control(&(bc26->device), BC26_ONENET_CLOSE, arg);
}

int bc26_disconnect_onenet(void)
{
    struct at_device_bc26 *bc26 = &_dev;
    int *arg = 0;
    return at_device_control(&(bc26->device), BC26_ONENET_DELETE, arg);
}

int bc26_onenet_addobj(onenet_obj_t *object)
{
    struct at_device_bc26 *bc26 = &_dev;
    struct bc26_onenet_add_obj obj;
    obj.objId = object->objId;
    obj.insCount = object->insCount;
    obj.bitMap = object->bitmap;
    obj.attrCount = object->attrCount;
    obj.actCount = object->actCount;

    return at_device_control(&(bc26->device), BC26_ONENET_ADDOBJ, (void *)(&obj));
}

int bc26_onenet_addobjs(rt_list_t *list)
{
    rt_list_t *node;
    onenet_obj_t *obj;
    rt_list_for_each(node, list)
    {
        obj = rt_list_entry(node, onenet_obj_t, list);
        if (bc26_onenet_addobj(obj) != RT_EOK)
        {
            return RT_ERROR;
        }
        rt_thread_mdelay(1000);
    }
    return RT_EOK;
}

int bc26_onenet_open(int lifetime)
{
    struct at_device_bc26 *bc26 = &_dev;

    return at_device_control(&(bc26->device), BC26_ONENET_OPEN, (void *)(&lifetime));
}

int bc26_onenet_observer_rsp(int msgId, int result)
{
    struct at_device_bc26 *bc26 = &_dev;
    struct bc26_onenet_ob_rsp rsp;

    rsp.msgId = msgId;
    rsp.result = result;

    return at_device_control(&(bc26->device), BC26_ONENET_OBSERVERSP, (void *)(&rsp));
}
//
int bc26_onenet_discover_rsp(rt_uint32_t mid, rt_uint8_t flag, int len, char *valuestring)
{
    struct at_device_bc26 *bc26 = &_dev;

    struct bc26_onenet_dis_rsp rsp;

    rsp.msgId = mid;
    rsp.result = flag;
    rsp.resource_ids_size = len;
    rsp.resource_ids = valuestring;

    return at_device_control(&(bc26->device), BC26_ONENET_DISCOVER, (void *)(&rsp));
}

//<msgId>,<objId>,<insId>,<resId>,<valueType>,<len>,<value>,<index>,<flag>[,<ackid>]

int bc26_onenet_write_rsp(int msgid, int result)
{
    struct at_device_bc26 *bc26 = &_dev;
    struct bc26_onenet_writersp rsp;
    rsp.msgId = msgid;
    rsp.result = result;
    return at_device_control(&(bc26->device), BC26_ONENET_WRITERSP, (void *)(&rsp));
}

int bc26_onenet_execute_rsp(int msgid, int result)
{
    struct at_device_bc26 *bc26 = &_dev;
    struct bc26_onenet_executersp rsp;
    rsp.msgId = msgid;
    rsp.result = result;
    return at_device_control(&(bc26->device), BC26_ONENET_EXECUTERSP, (void *)(&rsp));
}

int bc26_onenet_read_rsp(int msgid, int result, onenet_res_t *res, int len, nb_onenet_value_t data)
{
    struct at_device_bc26 *bc26 = &_dev;
    struct bc26_onenet_readrsp rsp;
    rsp.msgId = msgid;
    rsp.result = result;
    rsp.objId = res->instance->obj->objId;
    rsp.insId = res->instance->insId;
    rsp.resId = res->resId;
    rsp.valueType = res->valueType;
    rsp.len = len;
    rsp.data = data;
    rsp.index = 0;
    rsp.flag = 0;

    return at_device_control(&(bc26->device), BC26_ONENET_READRSP, (void *)(&rsp));
}

int bc26_onenet_notify(onenet_res_t *res, int len, nb_onenet_value_t data, int flag)
{
    struct at_device_bc26 *bc26 = &_dev;

    struct bc26_onenet_notify_data notify_data;

    notify_data.msgId = res->instance->obj->observe_msgId;
    notify_data.objId = res->instance->obj->objId;
    notify_data.insId = res->instance->insId;
    notify_data.resId = res->resId;
    notify_data.valueType = res->valueType;
    notify_data.len = len;
    notify_data.data = data;
    notify_data.index = 0;
    notify_data.flag = 0;
    notify_data.ackId = 0;

    return at_device_control(&(bc26->device), BC26_ONENET_NOTIFY, (void *)(&notify_data));
}

int bc26_onenet_notify_with_ack(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int ackId)
{
    struct at_device_bc26 *bc26 = &_dev;

    struct bc26_onenet_notify_data notify_data;

    notify_data.msgId = res->instance->obj->observe_msgId;
    notify_data.objId = res->instance->obj->objId;
    notify_data.insId = res->instance->insId;
    notify_data.resId = res->resId;
    notify_data.valueType = res->valueType;
    notify_data.len = len;
    notify_data.data = data;
    notify_data.index = 0;
    notify_data.flag = 0;
    notify_data.ackId = ackId;

    return at_device_control(&(bc26->device), BC26_ONENET_NOTIFY, (void *)(&notify_data));
}

#endif
