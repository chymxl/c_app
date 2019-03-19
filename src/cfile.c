#include "cfile.h"



/*****************************************************************************
函 数 名  : sys_init
功能：系统初始化接口，初始化系统，系统运行前或者测试用例执行完毕后可以使用该接口进行清理工作。
输入：void
输出：NULL
返回：RT_NOT_IMPLEMENTED：未实现。
      RT_SUCCESS：初始化成功
      RT_FAILED：初始化失败
*****************************************************************************/
int sys_init()
{
    return RT_NOT_IMPLEMENTED;
}

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
int user_register(const char *user_name, unsigned int age)
{
    return RT_NOT_IMPLEMENTED;
}

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
int app_register(const char *app_name, const char *limit_time_start, const char *limit_time_end, AppType app_type)
{
    return RT_NOT_IMPLEMENTED;
}


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
int app_search(const char *app_name, struct AppInfo *result, unsigned int *size)
{
    return RT_NOT_IMPLEMENTED;
}

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
int del_app(const char *app_name)
{
    return RT_NOT_IMPLEMENTED;
}

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
int app_use_planning(const char *app_name, const char *use_time_start, const char *use_time_end, struct AppUsePlanningInfo *result, unsigned int *size)
{
    return RT_NOT_IMPLEMENTED;
}
