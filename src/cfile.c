#include "cfile.h"

struct AppUser g_AppUser = {0};

int g_UserStatus = 0;


typedef struct stApp
{
    struct AppInfo appInfo;
    struct AppUsePlanningInfo appUserPlanningInfo;
}App;

App g_Apps[MAX_APP_INFO_CB_NUM];

int g_AppNum = 0;

#define LOG(format, args...) \
printf("%s %s %d:" format "\n", __FILE__, __FUNCTION__, __LINE__, ##args)

#define EXIT(format , args...) \
printf("%s %s %d:EXIT " format "\n", __FILE__, __FUNCTION__, __LINE__, ##args)

#define false 0
#define true 1

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
    memset(&g_AppUser, 0, sizeof(g_AppUser));
    memset(g_Apps, 0, sizeof(g_Apps));
    g_AppNum = 0;
    g_UserStatus = 0;
    return RT_SUCCESS;
}
int name_Check(const char *name)
{
    int i = 0;
    int userNameLen = 0;

    if (NULL == name)
    {
        EXIT("1");
        return false;
    }

    userNameLen = strlen(name);

    if (userNameLen == 0 || 30 < userNameLen)
    {
        EXIT("2");
        return false;
    }
    
    for (i = 0; i < userNameLen; i++)
    {
        if (('0' <= name[i] && '9' >= name[i]) ||
            ('a' <= name[i] && 'z' >= name[i]) ||
            ('A' <= name[i] && 'Z' >= name[i]))
        {
            continue;
        }
        else
        {
            EXIT("3 name[%d]=%c", i, name[i]);
            return false;
        }
        
    }

    EXIT("4");
    return true;
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
    int userNameLen = 0;
    
    if (1 == g_UserStatus)
    {
        EXIT("1");
        return RT_USER_REGISTERED;
    }

    if (false == name_Check(user_name))
    {
        EXIT("2");
        return RT_INVALID_USER_NAME;
    }
    
    g_AppUser.age = age;
    memset(g_AppUser.name, 0, sizeof(g_AppUser.name));
    memcpy(g_AppUser.name, user_name, userNameLen);
    g_UserStatus = 1;

    EXIT("3");
    return RT_SUCCESS;
}

int time_Check(const char *time, int *hour, int *minute)
{
    if (NULL == time || NULL == hour || NULL == minute)
    {
        EXIT("1");
        return false;
    }

    if (5 != strlen(time))
    {
        EXIT("2");
        return false;
    }

    if (('0' <= time[0] && '2' >= time[0]) &&
        ('0' <= time[1] && '9' >= time[1]) &&
        (':' == time[2]) &&
        ('0' <= time[3] && '5' >= time[3]) &&
        ('0' <= time[4] && '9' >= time[4]))
    {
        LOG("time string check ok");
    }
    else
    {
        EXIT("3");
        return false;
    }
    

    *hour = ((int)time[0] - '0') * 10 + ((int)time[1] - '0');
    *minute = ((int)time[3] - '0')  * 10 + ((int)time[4] - '0');

    if (24 < *hour || 59 < *minute)
    {
        LOG("hour=%d, minute=%d", *hour, *minute);
        EXIT("4");
        return false;
    }
    
    EXIT("5");
    return true;    
}

int time_start_end_check(const char *limit_time_start, const char *limit_time_end, struct AASTimeSeg *time_seg)
{
    int startHour  = 0;
    int startMinute= 0;
    int endHour    = 0;
    int endMinute  = 0;
    int startTime  = 0;
    int endTime    = 0;

    if (NULL == time_seg)
    {
        EXIT("1");
        return RT_FAILED;
    }
    
    if (false == time_Check(limit_time_start, &startHour, &startMinute))
    {
        EXIT("2");
        return RT_INVALID_START_TIME;
    }

    if (false == time_Check(limit_time_end, &endHour, &endMinute))
    {
        EXIT("3");
        return RT_INVALID_END_TIME;
    }

    startTime = startHour * 60 + startMinute;
    endTime   = endHour   * 60 + endMinute;

    if (startTime >= endTime)
    {
        EXIT("4");
        return RT_INVALID_TIME_SCOPE;
    }

    time_seg->start.hour   = (char)startHour;
    time_seg->start.minute = (char)startMinute;
    time_seg->end.hour     = (char)endHour;
    time_seg->end.minute   = (char)endMinute;

    EXIT("5");
    return RT_SUCCESS;
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
    int i   = 0;
    int ret = 0;

    struct AppInfo *app = NULL;

    if (false == name_Check(app_name))
    {
        EXIT("1");
        return RT_INVALID_APP_NAME;
    }

    for (i = 0; i < g_AppNum; i++)
    {
        if (strlen(app_name) == strlen(g_Apps[i].appInfo.name) &&
            0 == strcmp(app_name, g_Apps[i].appInfo.name))
        {
            EXIT("2");
            return RT_APP_REGISTERED;
        }
    }

    if (100 < g_AppNum)
    {
        EXIT("3");
        return RT_RESOURCE_NOT_ENOUGH;
    }

    app = &(g_Apps[g_AppNum].appInfo);

    ret = time_start_end_check(limit_time_start, limit_time_end, &(app->limit_time));

    if (RT_SUCCESS != ret)
    {
        EXIT("4");
        return ret;
    }
    app->app_type = app_type;
    memset(app->name, 0, sizeof(app->name));
    memcpy(app->name, app_name, strlen(app_name));
    g_AppNum++;

    return RT_SUCCESS;
}

int myCompare(const void *a, const void *b)
{
    struct AppInfo *app1;
    struct AppInfo *app2;

    app1 = (struct AppInfo *)a;
    app2 = (struct AppInfo *)b;

    LOG("app1->name=%s, app2->name=%s", app1->name, app2->name);

    return strcmp(app1->name, app2->name);
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
    int i = 0;

    if (NULL == app_name || NULL == result || NULL == size)
    {
        EXIT("1");
        return RT_INVALID_APP_NAME;
    }
    if (false == name_Check(app_name))
    {
        EXIT("2");
        return RT_INVALID_APP_NAME;
    }

    *size = 0;
    
    for (i = 0; i < g_AppNum; i++)
    {
        if (0 != strstr(g_Apps[i].appInfo.name, app_name))
        {
            memset(result + i, 0, sizeof(struct AppInfo));
            memcpy(result + i, &(g_Apps[i].appInfo), sizeof(struct AppInfo));
            (*size)++;
        }
    }

    if (0 == *size)
    {
        EXIT("3");
        return RT_APP_UNREGISTERED;
    }

    qsort(result, *size, sizeof(struct AppInfo), myCompare);

    return RT_SUCCESS;
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
    int i = 0;

    if (NULL == app_name)
    {
        EXIT("1");
        return RT_NOT_IMPLEMENTED;
    }

    if (false == name_Check(app_name))
    {
        EXIT("2");
        return RT_INVALID_APP_NAME;
    }

    for (i = 0; i < g_AppNum; i++)
    {
        if (strlen(app_name) == strlen(g_Apps[i].appInfo.name) &&
            0 == strcmp(g_Apps[i].appInfo.name, app_name))
        {
            memmove(&(g_Apps[i]), &(g_Apps[i + 1]), sizeof(App) * (g_AppNum - i - 1));
            memset(&(g_Apps[g_AppNum - 1]), 0 , sizeof(App));
            g_AppNum--;
        }
    }

    return RT_SUCCESS;
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
    
    if ( 0 == g_UserStatus)
    {
        EXIT("1");
        return RT_USER_UNREGISTERED;
    }

    if (NULL == app_name || false == name_Check(app_name))
    {
        EXIT("2");
        return RT_INVALID_APP_NAME;
    }
    return RT_NOT_IMPLEMENTED;
}
