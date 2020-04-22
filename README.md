<!--
 * @Description: 
 * @Version: 1.0
 * @Autor: liang.shao
 * @Date: 2020-04-22 10:07:49
 * @LastEditors: liang.shao
 * @LastEditTime: 2020-04-22 11:06:55
 -->
OneNet by AT commands
========================
0.作用
------
该软件包是[at_device](https://github.com/RT-Thread-packages/at_device)中bc26的一个增强包，添加了对bc26模组内部lwm2m协议的支持,目前整体只是简单的通过at_device_control接口发at命令来实现。
1.目的
------
rt-thread目前已经有了[支持mqtt的onenet软件包](https://github.com/RT-Thread-packages/onenet),而且实现的也比较好,支持断线重连,但是目前OneNet把mqtt协议弄成了旧版，新版本需要支持MQTTS，对于部分内存比较小的mcu来说不是太方便。
考虑到有许多需要连接onenet的用户，都会直接采用支持lwm2m协议的NB-Iot模组，通过at指令来连接onenet，而目前at_device默认只使用支持了tcp/ip协议栈，所以就编写了现在这个增强包。



2.目录结构
------
| 名称 | 说明 | 备注 |
| :------: | :------: | :------: |
| bc26 | 对at_device中bc26的一些修改 | 测试时备份原有项目后，覆盖bc26下对应文件|
| controller | controller层，用户操作层 |  |
| service | onenet服务层，主要是考虑将来实现数据在本地持久化 |  |
| entity | 软件内部实体，vo和一些定义 |  |
| ports | 模组使用lwm2m的at命令 | 目前只实现了bc26 |
| sample | demo | 目前只实现了bc26 |

3.使用介绍
------
目前还是处于测试状态，所以还不打算支持做成软件包形式，等测试完成，思考好如何再抽象出一层onenet_device层后，适配多个模组后，再制作成软件包。

首先，将bc26下的文件覆盖之前项目中的文件（请备份好之前的项目）;

然后，在工程目录下新建ports目录（有就不用了），将本文件拷贝到ports目录下，scons 导入到工程就可以了。

4.测试
------
在sample目录下写了一个简单的demo用例，可以测试一下


5.感谢
------
需要感谢rtthread相关工作人员和工作小组成员，骑士智能张君辉，项目中有部分借鉴了m5311的实现方法。

