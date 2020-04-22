/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 16:29:04
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-21 10:41:14
 */
#include <rtthread.h>

#include "at_device.h"
#include "at_device_bc26.h"

#include "onenet_entity.h"
#include "onenet_vo.h"



#define BC26_SAMPLE_DEIVCE_NAME "bc26"





extern int bc26_connect_onenet(void);
extern int bc26_disconnect_onenet(void);
extern int bc26_onenet_addobj(onenet_obj_t *object);
extern int bc26_onenet_addobjs(rt_list_t *list);
extern int bc26_onenet_open(int lifetime);

extern int bc26_onenet_observer_rsp(int msgid, int result);
extern int bc26_onenet_discover_rsp(rt_uint32_t mid, rt_uint8_t flag, int len, char *valuestring);
extern int bc26_onenet_write_rsp(int msgid, int result);
extern int bc26_onenet_read_rsp(int msgid, int result, onenet_res_t *res, int len, nb_onenet_value_t data);
extern int bc26_onenet_execute_rsp(int msgid, int result);

extern int bc26_onenet_notify(onenet_res_t *res, int len, nb_onenet_value_t data, int flag);
extern int bc26_onenet_notify_with_ack(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int ackId);

