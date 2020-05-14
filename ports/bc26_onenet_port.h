/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 16:29:04
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-22 11:16:06
 */
#include <rtthread.h>

#include "at_device.h"
#include "at_device_bc26.h"

#include "onenet_entity.h"
#include "onenet_vo.h"



#define BC26_SAMPLE_DEIVCE_NAME "bc26"

/* bc26 ONENET  opreations*/
#ifdef BC26_USE_ONENET_PROTOCOL

#define BC26_ONENET_CREATE 0x0100U
#define BC26_ONENET_DELETE 0x0200U
#define BC26_ONENET_ADDOBJ 0x0300U
#define BC26_ONENET_DELOBJ 0x0400U
#define BC26_ONENET_OPEN 0x0500U
#define BC26_ONENET_CLOSE 0x0600U
#define BC26_ONENET_NOTIFY 0x0700U
#define BC26_ONENET_OBSERVERSP 0x0800U
#define BC26_ONENET_DISCOVER 0x0900U
#define BC26_ONENET_WRITERSP 0x0A00U
#define BC26_ONENET_READRSP 0x0B00U
#define BC26_ONENET_EXECUTERSP 0x0C00U
#endif




extern int bc26_connect_onenet(void);
extern int bc26_disconnect_onenet(void);
extern int bc26_close_onenet(void);
extern int bc26_onenet_addobj(onenet_obj_t *object);
extern int bc26_onenet_addobjs(rt_list_t *list);
extern int bc26_onenet_open(int lifetime);

extern int bc26_onenet_observer_rsp(int msgid, int result);
extern int bc26_onenet_discover_rsp(rt_uint32_t mid, rt_uint8_t flag, int len, char *valuestring);
extern int bc26_onenet_write_rsp(int msgid, int result);
extern int bc26_onenet_read_rsp(int msgid, int result, onenet_res_t *res, int len, nb_onenet_value_t data);
extern int bc26_onenet_execute_rsp(int msgid, int result);

extern int bc26_at_onenet_notify(onenet_res_t *res, int len, nb_onenet_value_t data, int flag);
extern int bc26_at_onenet_notify_with_ack(onenet_res_t *res, int len, nb_onenet_value_t data, int flag, int ackId);

extern int set_bc26_sleep(void);
extern int set_bc26_wakeup(void);