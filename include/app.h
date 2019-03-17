#ifndef __APP_H__
#define __APP_H__

#undef LOG
#define LOG(format, arg...) \
    printf("[%s] %u:" format"\n", __FUNCTION__, __LINE__, ##arg)

#endif