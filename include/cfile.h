#ifndef _TSLB_HPP
#define _TSLB_HPP
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AAS_TRUE 1
#define AAS_FALSE 0

#define MAX_APP_INFO_CB_NUM 100
#define MAX_GROUP_CB_NUM 100
#define MAX_APP_USE_PLANNING_CB_NUM 100

// 时间字符串的长度
#define TIME_STR_LEN 5

/* 返回值枚举 */
enum TReturnCode
{
    // 未实现
    RT_NOT_IMPLEMENTED = 0,
    // 成功    
    RT_SUCCESS         = 1,
    // 失败
    RT_FAILED          = 2,

    // 非法的用户名
    RT_INVALID_USER_NAME = 500, 
    // 已有用户注册
    RT_USER_REGISTERED,
    // 非法的App名称
    RT_INVALID_APP_NAME,
    // App已注册
    RT_APP_REGISTERED,
    // 起始时间不合法
    RT_INVALID_START_TIME,
    // 终止时间不合法
    RT_INVALID_END_TIME,
    // 时间范围不合法
    RT_INVALID_TIME_SCOPE,
    // 资源不足
    RT_RESOURCE_NOT_ENOUGH,
    // APP不存在
    RT_APP_UNREGISTERED,
    // 非法的群组名称
    RT_INVALID_GROUP_NAME,
    // APP已存在于监控组中
    RT_APP_ALREADY_IN_GROUP,
    // App使用被限制
    RT_APP_USE_LIMITED,
    // 使用时段已经被占用
    RT_TIME_SEG_OCCUPIED,
    // 用户未注册
    RT_USER_UNREGISTERED,
};

/* App类型 */
typedef enum
{
    AppType_Work,        /* 工作 */
    APPType_Study,        /* 学习 */
    APPType_Recreation  /* 娱乐 */
}AppType;

/* 时间 */
struct AASTime
{
    unsigned char hour;        /* 小时 */
    unsigned char minute;    /* 分钟 */
};

/* 时间段 */
struct AASTimeSeg
{
    struct AASTime start;    /* 起始时间 */
    struct AASTime end;        /* 结束时间 */
};

/* App注册信息 */
struct AppInfo
{
    char name[32];                    /* App名称 */
    struct AASTimeSeg limit_time;    /* App限制使用时间段 */
    AppType app_type;            /* App类型 */
};

/* 用户信息 */
struct AppUser
{
    /* 用户名 */
    char name[32];    

    /* 用户年龄 */
    unsigned int age;    
};

/* App使用信息 */
struct AppUsePlanningInfo
{
    struct AppInfo app_info;
    struct AASTimeSeg time_of_use; /* App使用时段 */
};

/*****************************************************************************
函 数 名  : sys_init
功能：系统初始化接口，初始化系统，系统运行前或者测试用例执行完毕后可以使用该接口进行清理工作。
输入：void
输出：NULL
返回：RT_NOT_IMPLEMENTED：未实现。
      RT_SUCCESS：初始化成功
      RT_FAILED：初始化失败
*****************************************************************************/
int sys_init();

/*****************************************************************************
函 数 名  :user_register
功能：用户注册，设置用户名和年龄。
输入：
    const char *user_name: 用户名
    unsigned int age: 用户年龄
输出：NULL
返回：
    RT_NOT_IMPLEMENTED：未实现
    RT_SUCCESS：用户注册成功
    RT_USER_REGISTERED：已存在注册用户
    RT_INVALID_USER_NAME：用户名非法
*****************************************************************************/
int user_register(const char *user_name, unsigned int age);

/*****************************************************************************
函 数 名  : app_register
功能：注册App信息，包括限制时段、App类型等。
输入：
    const char *app_name：app名称
    const char *limit_time_start：限制使用时段的起始时间
    const char *limit_time_end：限制使用时段的结束时间
    enum AppType app_type：App类型
        
输出：NULL
返回：RT_NOT_IMPLEMENTED：未实现。
      RT_SUCCESS：App注册成功。
      RT_INVALID_APP_NAME：App名称不合法
      RT_APP_REGISTERED：App已注册。
      RT_INVALID_START_TIME：限制时段起始时间非法
      RT_INVALID_END_TIME：限制时段结束时间非法
      RT_INVALID_TIME_SCOPE：时间段不合法
      RT_RESOURCE_NOT_ENOUGH: 资源超限
*****************************************************************************/
int app_register(const char *app_name, const char *limit_time_start, const char *limit_time_end, AppType app_type);


/*****************************************************************************
函 数 名  : app_search
功能：根据app名称，检索已经注册的App信息，支持简单的模糊查询。
输入：const char *app_name app名称
输出：
    struct AppInfo *result：匹配结果，存储空间由用例分配，用例保证空间足够，指针非空
    unsigned int *size：匹配结果数目，由用例定义并保证非空
返回：RT_NOT_IMPLEMENTED：未实现。
      RT_SUCCESS：查询成功
      RT_INVALID_APP_NAME：用户名不合法
      RT_APP_UNREGISTERED：App未注册
*****************************************************************************/
int app_search(const char *app_name, struct AppInfo *result, unsigned int *size);

/*****************************************************************************
函 数 名  :  del_app
功能：删除指定的app注册信息。
输入：const char *app_name：App名称
输出：无
返回：RT_NOT_IMPLEMENTED：未实现。
      RT_SUCCESS：删除成功
      RT_INVALID_APP_NAME：App名称不合法
      RT_APP_UNREGISTERED：App未注册
*****************************************************************************/
int del_app(const char *app_name);

/*****************************************************************************
函 数 名  :  app_use_planning 
功能：用户规划使用app
输入：
    const char *app_name：app名称
    const char *use_time_start：起始使用时间
    const char *use_time_end：结束使用时间
输出：
    struct AppUsePlanningInfo *result：接口调用后的最新规划结果
    unsigned int *size：接口调用后最新结果中的有效数据个数
返回：RT_NOT_IMPLEMENTED：未实现。
      RT_SUCCESS：规划成功
      RT_USER_UNREGISTERED：用户未注册
      RT_APP_UNREGISTERED：App未注册
      RT_INVALID_APP_NAME：App名称不合法
      RT_INVALID_START_TIME：起始时间不合法
      RT_INVALID_TIME_SCOPE：时间区间不合法
      RT_INVALID_END_TIME：结束时间不合法
      RT_APP_USE_LIMITED：App使用受限
      RT_TIME_SEG_OCCUPIED：App使用时段已经被占用
*****************************************************************************/
int app_use_planning(const char *app_name, const char *use_time_start, const char *use_time_end, struct AppUsePlanningInfo *result, unsigned int *size);

/*****************************************************************************
 函 数 名  : AAS_TestCase
 功能描述  : 提供给（选择函数实现方式的）考生的测试用例样例。
 输入参数  : 无。
 输出参数  : 无。
 返 回 值  : 无。
 重要说明  : 选择函数实现方式的考生可以在本接口中调整或者增加测试用例。
             选择命令方式的考生不需要关注本接口，也不要改动本接口。
*****************************************************************************/
void AAS_TestCase();

#endif
