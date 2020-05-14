/*
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-20 23:50:53
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-24 12:34:03
 */
#include <rtthread.h>

#include <stdio.h>
#include "string.h"
#include "onenet_controller.h"

onenet_obj_t *self;
onenet_obj_t *device0;
onenet_res_t *string_res;

static int nb_onenet_thread_closed = RT_FALSE;

void demo_onenet(void *arg)
{
	rt_uint8_t *string_value = (rt_uint8_t *)"Hello , Rt-Thread !";
	//rt_uint8_t *string_value = (rt_uint8_t *)"6811240005010724000401642400567E13080E040C0E000001403A000301403B000601403B000901403B000D01403B001001403B001301403B001601403B001901403B001D01403B002001403B002301403B002601403C002901403B002D01403B003001403B003301403B003601403B003901403C003D01403C004001403C004301363C004601363C004901363C6C16";
	
	
	if (!nb_onenet_is_inited())
	{
		nb_onenet_init_environment();

		self = nb_onenet_create_object(3200, 1, "1", 10, 1);	//创建对象，增加一个自身的对象
		device0 = nb_onenet_create_object(3201, 1, "1", 10, 1); //创建对象，增加一个自身的对象

		nb_onenet_print_all_object();

		onenet_instance_t *instance = nb_onenet_create_instance(self); //创建自身的实例
		onenet_instance_t *device0_instance = nb_onenet_create_instance(device0);
		if (instance == RT_NULL || device0_instance == RT_NULL)
		{
			LOG_E("create instance error");
			return;
		}

		nb_onenet_print_instances(self);
		nb_onenet_print_instances(device0);

		//为自身添加属性 8个自身属性
		nb_onenet_create_res(instance, 5500, nb_onenet_value_bool);								 //R
		nb_onenet_create_res(instance, 5501, nb_onenet_value_integer);							 //R
		nb_onenet_create_res(instance, 5502, nb_onenet_value_bool);								 //RW
		nb_onenet_create_res(instance, 5503, nb_onenet_value_integer);							 //RW
		nb_onenet_create_res(instance, 5504, nb_onenet_value_integer);							 //RW
		nb_onenet_create_res(instance, 5505, nb_onenet_value_opaque);							 //E
		string_res = nb_onenet_create_res(instance, 5750, nb_onenet_value_string); //RW
		nb_onenet_create_res(instance, 5751, nb_onenet_value_string);							 //R

		nb_onenet_create_res(device0_instance, 5500, nb_onenet_value_bool);	   //RW
		nb_onenet_create_res(device0_instance, 5501, nb_onenet_value_integer); //RW
		nb_onenet_create_res(device0_instance, 5750, nb_onenet_value_string);  //RW

		if (self == RT_NULL)
		{
			LOG_E("self object create failure");
			return;
		}

		if (instance == RT_NULL)
		{
		}
	}

	if (nb_onenet_quick_start() != RT_EOK)
	{
		LOG_E("ONENET REG FAILED");
		return;
	}
	else
	{
		LOG_I("ONENET REG SUCCESS");
		nb_onenet_notify_res(string_res, rt_strlen((const char *)string_value), (nb_onenet_value_t)&string_value, 0, 0);
	}

	rt_thread_mdelay(1000);
	while (!nb_onenet_thread_closed)
	{
		rt_thread_mdelay(60000);
		if (nb_onenet_get_connectiton_status() == RT_EOK)
		{
			if (nb_onenet_notify_res_with_ack(string_res, rt_strlen((const char *)string_value), (nb_onenet_value_t)&string_value, 0, 0) != RT_EOK)
			// if(nb_onenet_notify_res(string_res, rt_strlen((const char *)string_value), (nb_onenet_value_t)&string_value, 0))
			{
				LOG_D("notify error");
			}
			else
			{
				LOG_D("notify success");
			}
		}
	}
}

static void _demo_onenet(void)
{
	rt_thread_t tid;
	tid = rt_thread_create("demo_onenet", demo_onenet, NULL, 8192 * 2, 18, 10);
	if (tid)
		rt_thread_startup(tid);
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT_ALIAS(_demo_onenet, demo_onenet, nbiot onenet test);
#endif /* FINSH_USING_MSH */

static void close_demo_onenet(void)
{	
	nb_onenet_thread_closed = RT_TRUE;
	nb_onenet_close();
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT_ALIAS(close_demo_onenet, close_demo_onenet, nbiot onenet test);
#endif /* FINSH_USING_MSH */

static void reboot_bc26(void)
{
	bc26_reboot();
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT_ALIAS(reboot_bc26, reboot_bc26, nbiot onenet test);
#endif /* FINSH_USING_MSH */


static void _sleep_bc26(void)
{
	set_bc26_sleep();
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT_ALIAS(_sleep_bc26, bc26_sleep, nbiot onenet test);
#endif /* FINSH_USING_MSH */


static void _wakeup_bc26(void)
{
	set_bc26_wakeup();
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT_ALIAS(_wakeup_bc26, bc26_wakeup, nbiot onenet test);
#endif /* FINSH_USING_MSH */