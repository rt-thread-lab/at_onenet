/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 15:30:26
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-22 01:46:44
 */

#include "onenet_controller.h"
#include "bc26_onenet_port.h"
#include "string.h"

//定义EVENT事件编号
#define event_bootstrap_fail (1 << 1)
#define event_connect_fail (1 << 2)
#define event_reg_success (1 << 3)
#define event_reg_fail (1 << 4)
#define event_reg_timeout (1 << 5)
#define event_lifetime_timeout (1 << 6)
#define event_update_success (1 << 7)
#define event_update_fail (1 << 8)
#define event_update_timeout (1 << 9)
#define event_update_need (1 << 10)
#define event_unreg_done (1 << 11)
#define event_response_fail (1 << 12)
#define event_response_success (1 << 13)
#define event_notify_fail (1 << 14)
#define event_notify_success (1 << 15)
#define event_observer_success (1 << 16)
#define event_discover_success (1 << 17)

struct onenet_device onenet_device_table = {0};

static int local_nb_onenet_inited = 0;
static rt_event_t onenet_event = RT_NULL;
onenet_event_msg_t event_msg[ONENET_EVENT_MSG_NUM];
struct rt_messagequeue onenet_event_mq;

extern rt_list_t onenet_obj_g_list;

void onenet_event_callback(rt_int32_t id)
{
    switch (id)
    {
    case 1:
        LOG_D("Bootstrap start    ");
        onenet_device_table.event_status = nb_onenet_status_run;
        break;
    case 2:
        LOG_D("Bootstrap success  ");
        onenet_device_table.event_status = nb_onenet_status_run;
        break;
    case 3:
        LOG_E("Bootstrap failure,Device not registered on onenet");
        onenet_device_table.event_status = nb_onenet_status_failure;
        rt_event_send(onenet_event, event_bootstrap_fail);
        break;
    case 4:
        LOG_D("Connect success");
        onenet_device_table.event_status = nb_onenet_status_run;
        break;
    case 5:
        LOG_E("Connect failure");
        onenet_device_table.event_status = nb_onenet_status_failure;
        rt_event_send(onenet_event, event_connect_fail);
        break;
    case 6:
        LOG_D("Reg onenet success");
        onenet_device_table.event_status = nb_onenet_status_success;
        rt_event_send(onenet_event, event_reg_success);
        break;
    case 7:
        if (onenet_device_table.event_status != nb_onenet_status_failure)
        {
            LOG_E("Device not registered on onenet Or the onenet Device Auth_code parameter is set");
            onenet_device_table.event_status = nb_onenet_status_failure;
            rt_event_send(onenet_event, event_reg_fail);
        }
        break;
    case 8:
        LOG_D("Reg onenet timeout");
        onenet_device_table.event_status = nb_onenet_status_failure;
        rt_event_send(onenet_event, event_reg_timeout);
        break;
    case 9:
        LOG_D("Life_time timeout");
        break;
    case 10:
        LOG_D("Status halt");
        break;
    case 11:
        LOG_D("Update success");
        onenet_device_table.update_time = nb_onenet_status_update_success;
        rt_event_send(onenet_event, event_update_success);
        break;
    case 12:
        LOG_E("Update failure");
        onenet_device_table.update_time = nb_onenet_status_update_failure;
        rt_event_send(onenet_event, event_update_fail);
        break;
    case 13:
        LOG_E("Update timeout");
        onenet_device_table.update_time = nb_onenet_status_update_timeout;
        rt_event_send(onenet_event, event_update_timeout);
        break;
    case 14:
        LOG_D("Update need");
        onenet_device_table.update_time = nb_onenet_status_update_need;
        break;
    case 15:
        LOG_D("onenet Unreg success");
        onenet_device_table.connect_status = nb_onenet_status_failure;
        if (onenet_device_table.close_status == nb_onenet_status_close_start)
        {
            onenet_device_table.close_status = nb_onenet_status_close_init;
            rt_event_send(onenet_event, event_unreg_done);
        }
        else
        {
#if 0
            if (nb_onenet_close_callback() != RT_EOK)
            {
                LOG_E("close onenet instance failure");
            }
#endif
        }
        break;
    case 20:
        LOG_E("Response failure");
        break;
    case 21:
        LOG_D("Response success");
        break;
    case 25:
        LOG_E("Notify failure");
        onenet_device_table.notify_status = nb_onenet_status_failure;
        rt_event_send(onenet_event, event_notify_fail);
        break;
    case 26:
        LOG_D("Notify success");
        onenet_device_table.notify_status = nb_onenet_status_success;
        rt_event_send(onenet_event, event_notify_success);
        break;
    case 40:
        LOG_D("enter onenet fota down start");
        break;
    case 41:
        LOG_E("onenet fota down fail");
        break;
    case 42:
        LOG_D("onenet fota down success");
        break;
    case 43:
        LOG_D("onenet enter fotaing ");

        break;
    case 44:
        LOG_D("onenet fota success");
        break;
    case 45:
        LOG_E("onenet fota failure");
        break;
    case 46:
        LOG_D("onenet fota update success");
        break;
    case 47:
        LOG_E("onenet fota event interrupt failure");
        break;
    case 48:

        break;
    default:
        break;
    }
}

char *get_instance_resString(onenet_instance_t *instance)
{
#define RESID_LEN 4

    char *valueString = RT_NULL;
    int len = 0;
    if (!rt_list_isempty(&(instance->onenet_res_list)))
    {
        len = rt_list_len(&(instance->onenet_res_list));
    }
    else
    {
        return valueString;
    }

    int index = 0;
    if (len == 0)
    {
        return RT_NULL;
    }
    else
    {
        int val_len = (len * (RESID_LEN) + (len));
        valueString = rt_malloc(val_len); //rt_free
        rt_kprintf("malloc %d res and the string len is %d\n", len, val_len);
        rt_memset(valueString, 0, val_len);
    }

    rt_list_t *node;
    onenet_res_t *tmp;
    rt_list_for_each(node, &(instance->onenet_res_list))
    {
        tmp = rt_list_entry(node, onenet_res_t, list);
        if (len == 1)
        {
            rt_sprintf(valueString, "%d", tmp->resId);
            break;
        }
        else
        {
            char resString[RESID_LEN];
            if (index < (len - 1))
            {
                rt_sprintf(resString, "%d;", tmp->resId);
                strcat(valueString, resString);
                // valueString = valueString + RESID_LEN + 1;
            }
            else
            {
                rt_sprintf(resString, "%d", tmp->resId);
                strcat(valueString, resString);
            }
        }

        index++;
    }
    return valueString;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int onenet_discover_rsp(onenet_obj_t *obj)
{
#ifdef BC26_USE_ONENET_PROTOCOL
    onenet_obj_t *object = obj;
    int result = 1;

    if (object != RT_NULL)
    {
        result = 1;
        onenet_instance_t *instance = get_first_instance(obj);
        if (instance != RT_NULL)
        {
            char *valueString = get_instance_resString(instance);
            if (valueString == RT_NULL)
            {
                return -RT_ERROR;
            }
            if (bc26_onenet_discover_rsp(object->discover_msgId, result, rt_strlen(valueString), valueString) != RT_EOK)
            {
                rt_free(valueString);
                return -RT_ERROR;
            }
            else
            {
                rt_free(valueString);
                onenet_device_table.discover_status = nb_onenet_status_success;
                onenet_device_table.connect_status = nb_onenet_status_success;
                rt_event_send(onenet_event, event_discover_success);
                return RT_EOK;
            }
        }
        else
        {
            LOG_E("there is no instance from the first object");
            return -RT_ERROR;
        }
    }
    else
    {
        result = 0;
        return -RT_ERROR;
    }
#endif
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int onenet_observe_rsp(int msgid, int objId, int flag)
{
#ifdef BC26_USE_ONENET_PROTOCOL
    int result = 1;
    onenet_obj_t *obj = nb_onenet_get_object_ById(objId);
    obj->observe_msgId = msgid;
    if (obj != RT_NULL)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    if (bc26_onenet_observer_rsp(obj->observe_msgId, result) != RT_EOK)
    {
        LOG_E("onenet observer rsp failed");
        return -RT_ERROR;
    }

#endif

    onenet_device_table.observercount++;
    if (onenet_device_table.observercount == onenet_device_table.objcount)
    {
        //find observe success
        onenet_device_table.observercount = 0;
        onenet_device_table.observer_status = nb_onenet_status_success;
#ifdef NB_ONENET_USING_DEBUG
        LOG_D("observer success ");
#endif
        rt_event_send(onenet_event, event_observer_success);
    }

    LOG_D("onenet_observe_rsp pass");
    return RT_EOK;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int onenet_write_rsp(int msgid, int objid, int insid, int resid, int valuetype, int len, char *data)
{
    if (bc26_onenet_write_rsp(msgid, 2) != RT_EOK)
    {
        return (-RT_ERROR);
    }
    else
    {
        return RT_EOK;
    }
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int onenet_read_rsp(int msgid, int objid, int insid, int resid)
{
    if (insid == -1 && resid == -1)
    {
        //get all obj
    }
    else if (resid == -1)
    {
        //get obj all instance
    }
    else
    {
        //get res
        onenet_obj_t *obj = nb_onenet_get_object_ById(objid);
        if (obj == RT_NULL)
        {
            return (-RT_ERROR);
        }

        onenet_instance_t *instance = nb_onenet_get_instance_ById(obj, insid);
        if (instance == RT_NULL)
        {
            return (-RT_ERROR);
        }

        onenet_res_t *res = nb_onenet_get_res_ById(instance, resid);
        if (res == RT_NULL)
        {
            return (-RT_ERROR);
        }
        rt_uint8_t *string_value = (rt_uint8_t *)"hello,world!";

        bc26_onenet_read_rsp(msgid, 1, res, rt_strlen((const char *)string_value), (nb_onenet_value_t)&string_value);
    }
    return RT_EOK;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int onenet_execute_rsp(int msgid, int objid, int insid, int resid, int len, char *cmd)
{
    rt_kprintf("the cmd is %s\n", cmd);

    if (bc26_onenet_execute_rsp(msgid, 2) != RT_EOK)
    {
        return (-RT_ERROR);
    }
    else
    {
        return RT_EOK;
    }
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
rt_err_t onenet_event_put(onenet_event_msg_t *msg)
{
    rt_err_t rst = RT_EOK;

    rst = rt_mq_send(&onenet_event_mq, msg, sizeof(onenet_event_msg_t));
    if (rst == -RT_EFULL)
    {
        LOG_I("onenet event queue is full");
        rt_thread_mdelay(100);
        rst = -RT_EFULL;
    }
    return rst;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
rt_err_t onenet_event_get(onenet_event_msg_t *msg, int timeout)
{
    rt_err_t rst = RT_EOK;

    rst = rt_mq_recv(&onenet_event_mq, msg, sizeof(onenet_event_msg_t), timeout);
    if ((rst != RT_EOK) && (rst != -RT_ETIMEOUT))
    {
        LOG_E("onenet event get failed! Errno: %d", rst);
    }
    return rst;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
static rt_err_t onenet_event_process(onenet_event_msg_t *msg)
{
    rt_err_t rst = RT_EOK;
    switch (msg->event.event_src)
    {
    case ONENET_EVENT_SRC_DISCOVER:
    {
        onenet_obj_t *obj = nb_onenet_get_object_ById(msg->event.type.objId);
				
        if (obj != RT_NULL)
        {		
						LOG_I("discover obj %d",msg->event.type.objId);
            obj->discover_msgId = msg->event.type.msgId;
            onenet_discover_rsp(obj);
        }
    }
    break;
    case ONENET_EVENT_SRC_OBSERVE:
    {
        //onenet_obj_t *obj = nb_onenet_get_object_ById(msg->event.type.objId);
        //obj->observe_msgId = msg->event.type.msgId;

        onenet_observe_rsp(msg->event.type.msgId, msg->event.type.objId, msg->event.type.flag);
    }
    break;
    case ONENET_EVENT_SRC_WRITE:
    {
        onenet_write_rsp(msg->event.type.msgId, msg->event.type.objId, msg->event.type.insId, msg->event.type.resId, msg->event.type.valueType, msg->event.type.len, msg->event.type.data);
    }
    break;
    case ONENET_EVENT_SRC_READ:
    {
        onenet_read_rsp(msg->event.type.msgId, msg->event.type.objId, msg->event.type.insId, msg->event.type.resId);
    }
    break;
    case ONENET_EVENT_SRC_EXECUTE:
    {
        onenet_execute_rsp(msg->event.type.msgId, msg->event.type.objId, msg->event.type.insId, msg->event.type.resId, msg->event.type.len, msg->event.type.data);
    }
    break;
    default:
        rst = RT_ERROR;
        break;
    }
    return rst;
}

static void onenet_event_handler(void *arg)
{
    rt_err_t rst = RT_EOK;
    onenet_event_msg_t msg;

    while (1)
    {
        rst = onenet_event_get(&msg, RT_WAITING_FOREVER);
        if (rst == RT_EOK)
        {
            onenet_event_process(&msg);
        }
    }
}

static rt_err_t onenet_event_start(void)
{
    rt_thread_t onenet_event_tid;
    onenet_event_tid = rt_thread_create("onenet_event",
                                        onenet_event_handler,
                                        RT_NULL,
                                        1024, RT_THREAD_PRIORITY_MAX / 2 - 4, 20);
    if (onenet_event_tid != RT_NULL)
        rt_thread_startup(onenet_event_tid);

    return RT_EOK;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_init_environment(void)
{
    if (local_nb_onenet_inited)
        return RT_EOK;

    onenet_event = rt_event_create("on_event", RT_IPC_FLAG_FIFO);
    if (!onenet_event)
    {
        LOG_E("onenet event create failed");
        return -RT_ERROR;
    }

    rt_mq_init(&onenet_event_mq, "onenet_event_mq",
               &event_msg[0],
               sizeof(onenet_event_msg_t),
               sizeof(event_msg),
               RT_IPC_FLAG_FIFO);

    if (onenet_event_start() != RT_EOK)
    {
        LOG_E("onenet event start failed");
    }

    rt_memset(&onenet_device_table, 0, sizeof(onenet_device_table));

    onenet_device_table.lifetime = NB_ONENET_LIFE_TIME;
    onenet_device_table.connect_status = nb_onenet_status_init;
    onenet_device_table.initstep = 0;

    rt_list_init(&onenet_obj_g_list);

    local_nb_onenet_inited = 1;
    LOG_D("nb.onenet init success");

    return RT_EOK;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
rt_bool_t nb_onenet_is_inited(void)
{
    return local_nb_onenet_inited == 1;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_open(void)
{
    rt_uint32_t status;
#ifdef BC26_USE_ONENET_PROTOCOL
    if (bc26_onenet_open(onenet_device_table.lifetime) != RT_EOK)
    {
        LOG_E("onenet open failed");
        return -RT_ERROR;
    }
#endif
    onenet_device_table.initstep = 4;
    onenet_device_table.event_status = nb_onenet_status_init;
    if (rt_event_recv(onenet_event, event_bootstrap_fail | event_connect_fail | event_reg_fail | event_reg_success | event_reg_timeout, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, TIMEOUT_NORMAL, &status) != RT_EOK)
    {
        LOG_E("onenet wait reg timeout");
        return -RT_ERROR;
    }
    if (status == event_bootstrap_fail || status == event_connect_fail || status == event_reg_fail)
    {
        LOG_E("onenet reg failure");
        return -RT_ERROR;
    }
    if (status == event_reg_timeout)
    {
        LOG_E("The device is not registered in the platform or filled in Auto Code");
        return -RT_ERROR;
    }
    onenet_device_table.initstep = 5;
    if (rt_event_recv(onenet_event, event_observer_success, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, TIMEOUT_NORMAL, &status) != RT_EOK)
    {

        LOG_E("wait onenet observe event timeout");
        return -RT_ERROR;
    }
    onenet_device_table.initstep = 6;
    if (rt_event_recv(onenet_event, event_discover_success, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, TIMEOUT_NORMAL, &status) != RT_EOK)
    {
        LOG_E("Please turn on auto discovery resource in onenet platform device management");
        return -RT_ERROR;
    }
    if (onenet_device_table.discover_status == nb_onenet_status_success)
    {
        LOG_D("onenet lwm2m connect success");
        onenet_device_table.initstep = 13;
        return RT_EOK;
    }
    else
    {
        LOG_E("discover failure,Please turn on auto discovery resource in onenet platform device management");
        return -RT_ERROR;
    }
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_close(void)
{
    rt_uint32_t status;
    onenet_device_table.close_status = nb_onenet_status_close_start;
#ifdef NB_ONENET_USING_DEBUG
    LOG_D("onenet will close");
#endif
    if (rt_event_recv(onenet_event, event_unreg_done, RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR, 20000, &status) != RT_EOK)
    {
        LOG_E("close onenet instance failure");
        return -RT_ERROR;
    }
    LOG_D("close onenet instance success");
    onenet_device_table.connect_status = nb_onenet_status_init;
    return RT_EOK;
}

static int onenet_create_objects(void)
{
#ifdef BC26_USE_ONENET_PROTOCOL
    if (bc26_onenet_addobjs(&onenet_obj_g_list) == RT_EOK)
    {
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }

#endif
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
static int onenet_create(void)
{
#ifdef BC26_USE_ONENET_PROTOCOL
    if (bc26_connect_onenet() != RT_EOK)
    {
        LOG_E("create init failed");
        return -RT_ERROR;
    }
    return RT_EOK;
#endif
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_quick_start(void)
{
    if (onenet_create() != RT_EOK)
    {
        LOG_E("onenet create instance failure");
        goto __failure;
    }
    onenet_device_table.initstep = 1;
    rt_thread_mdelay(1000);
    if (onenet_create_objects() != RT_EOK)
    {
        LOG_E("onenet create object failure");
        return -RT_ERROR;
    }
    onenet_device_table.initstep = 2;

    if (nb_onenet_open() != RT_EOK)
        goto __failure;

    return RT_EOK;

__failure:
    if (onenet_device_table.initstep > 5)
    {
        nb_onenet_close();
    }
    return -RT_ERROR;
}
/**
 * @description: 
 * @param {type} 
 * @return: 
 */
int nb_onenet_get_connectiton_status(void)
{
    if (onenet_device_table.connect_status == nb_onenet_status_success)
        return RT_EOK;
    return -RT_ERROR;
}

/**
 * @description: 
 * @param {type} 
 * @return: 
 */

int nb_onenet_notify_res_with_ack(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int index)
{
    rt_uint32_t status = 0;
#ifdef BC26_USE_ONENET_PROTOCOL
    if (bc26_onenet_notify_with_ack(res, len, data, flag, onenet_device_table.notify_ack) != RT_EOK)
    {
        LOG_E("onenet notify failed");
        return -RT_ERROR;
    }
    rt_event_recv(onenet_event, event_notify_fail | event_notify_success, RT_EVENT_FLAG_OR | RT_EVENT_FLAG_CLEAR, 20000, &status);
    if (status == event_notify_fail)
    {
        LOG_E("ack notify to onenet failure, objectid:%d 	instanceid:%d 	resourceid:%d		msgid:%d", res->instance->obj->objId,
              res->instance->insId, res->resId, res->instance->obj->observe_msgId);
        onenet_device_table.notify_status = nb_onenet_status_init;
        return -RT_ERROR;
    }

#ifdef NB_ONENET_USING_LOG
    LOG_D("ack notify to onenet success, objectid:%d 	instanceid:%d 	resourceid:%d		msgid:%d", res->instance->obj->objid, res->instance->insid, res->resid, res->instance->obj->observe_msgId);
#endif
    onenet_device_table.notify_status = nb_onenet_status_init;
    onenet_device_table.notify_ack++;
    if (onenet_device_table.notify_ack > 5000)
        onenet_device_table.notify_ack = 1;
    return RT_EOK;
#endif
}
