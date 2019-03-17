#ifndef __APP_H__
#define __APP_H__

#undef LOG
#define LOG(format, arg...) \
    printf("%s [%s] %u:" format"\n", __FILE_ID__,  __FUNCTION__, __LINE__, ##arg)

#endif