#include "cfile.h"
#include <assert.h>

#define ASSERT assert

/************************************************************************/
/* 请注意：该文件所含用例仅供考生调测功能使用，并非最终评分用例。       */
/************************************************************************/

void TestUserRegister01()
{
    ASSERT(RT_SUCCESS == sys_init());
    ASSERT(RT_SUCCESS == user_register("Tom", 19));
}

void TestAppRegister01()
{
    ASSERT(RT_SUCCESS == sys_init());
    ASSERT(RT_SUCCESS == app_register("WeLink", "00:00", "09:00", AppType_Work));
}

void create_app_info(const char *app_name, unsigned char h1, unsigned char m1, unsigned char h2, unsigned char m2, AppType app_type, struct AppInfo *out)
{
	ASSERT(out != NULL);
	strcpy(out->name, app_name);
	out->limit_time.start.hour = h1;
	out->limit_time.start.minute = m1;
	out->limit_time.end.hour = h2;
	out->limit_time.end.minute = m2;
	out->app_type = app_type;
}

void TestAppSearch09()
{
	ASSERT(RT_SUCCESS == sys_init());
	ASSERT(RT_SUCCESS == app_register("WeLink123", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("WeLinkabc", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("123WeLink", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("abcWeLink", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("abcWeLink123", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("WeLink", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("welink", "00:00", "09:30", AppType_Work));
	ASSERT(RT_SUCCESS == app_register("WeChat", "00:00", "09:30", AppType_Work));

	AppInfo result[MAX_APP_INFO_CB_NUM] = {0};
	unsigned int size = 0;
	ASSERT(RT_INVALID_APP_NAME == app_search("WeLink2.0", result, &size));
	ASSERT(size == 0);
	ASSERT(RT_SUCCESS == app_search("WeLink", result, &size));
	ASSERT(size == 6);

	struct AppInfo target_result[6] = {0};
	create_app_info("123WeLink", 0, 0, 9, 30, AppType_Work, &target_result[0]);
	create_app_info("WeLink", 0, 0, 9, 30, AppType_Work, &target_result[1]);
	create_app_info("WeLink123", 0, 0, 9, 30, AppType_Work, &target_result[2]);
	create_app_info("WeLinkabc", 0, 0, 9, 30, AppType_Work, &target_result[3]);
	create_app_info("abcWeLink", 0, 0, 9, 30, AppType_Work, &target_result[4]);
	create_app_info("abcWeLink123", 0, 0, 9, 30, AppType_Work, &target_result[5]);

	ASSERT(0 == memcmp(result, target_result, sizeof(struct AppInfo) * size));
}

void TestDelApp01()
{
    ASSERT(RT_SUCCESS == sys_init());
    ASSERT(RT_SUCCESS == app_register("WeLink", "00:00", "09:30", AppType_Work));

    ASSERT(RT_SUCCESS == del_app("WeLink"));
	AppInfo result[MAX_APP_INFO_CB_NUM] = {0};
	unsigned int size = 0;
	ASSERT(RT_APP_UNREGISTERED == app_search("WeLink", result, &size));
	ASSERT(size == 0);
	ASSERT(0 == strcmp("", result[0].name));	
}

void create_time_of_use(unsigned char h1, unsigned char m1, unsigned char h2, unsigned char m2, struct AASTimeSeg *out)
{
    out->start.hour = h1;
    out->start.minute = m1;
    out->end.hour = h2;
    out->end.minute = m2;
}

void TestAppUsePlanning27()
{
    struct AppUsePlanningInfo result[MAX_APP_USE_PLANNING_CB_NUM] = {0};
	unsigned int rlt_count = 0;

	struct AppUsePlanningInfo target_result[MAX_APP_USE_PLANNING_CB_NUM] = {0};
	unsigned int target_rlt_count = 0;

	ASSERT(RT_SUCCESS == sys_init());
    ASSERT(RT_SUCCESS == user_register("IronMan", 33));
	
    ASSERT(RT_SUCCESS == app_register("WeLink", "23:00", "23:30", AppType_Work));
    ASSERT(RT_SUCCESS == app_register("iLearning", "23:00", "23:30", APPType_Study));

    ASSERT(RT_SUCCESS == app_use_planning("iLearning", "07:00", "10:00", result, &rlt_count));
    create_app_info("iLearning", 23, 0, 23, 30, APPType_Study, &target_result[0].app_info);
    create_time_of_use(7, 0, 10, 0, &target_result[0].time_of_use);
    ASSERT(rlt_count == 1); 
    ASSERT(0 == memcmp(target_result, result, sizeof(struct AppUsePlanningInfo) * MAX_APP_USE_PLANNING_CB_NUM));
    
	memset(target_result, 0, sizeof(struct AppUsePlanningInfo) * MAX_APP_USE_PLANNING_CB_NUM);
    ASSERT(RT_SUCCESS == app_use_planning("WeLink", "07:00", "09:00", result, &rlt_count));
    create_app_info("WeLink", 23, 0, 23, 30, AppType_Work, &target_result[0].app_info);
    create_time_of_use(7, 0, 9, 0, &target_result[0].time_of_use);
    create_app_info("iLearning", 23, 0, 23, 30, APPType_Study, &target_result[1].app_info);
    create_time_of_use(9, 0, 10, 0, &target_result[1].time_of_use);
    ASSERT(rlt_count == 2); 
    ASSERT(0 == memcmp(target_result, result, sizeof(struct AppUsePlanningInfo) * MAX_APP_USE_PLANNING_CB_NUM));    
}

void AAS_TestCase()
{
	TestUserRegister01();
	TestAppRegister01();
	TestAppSearch09();
	TestDelApp01();
	TestAppUsePlanning27();
}
