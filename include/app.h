#ifndef __APP_H__
#define __APP_H__

#undef LOG
#define LOG(format, arg...) \
    printf("%s %s %s [%s] %u:" format"\n", __DATE__, __TIME__, __FILE__,  __FUNCTION__, __LINE__, ##arg)

#endif