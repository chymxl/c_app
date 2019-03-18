#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <app.h>

#define __FILE_ID__ "main.c"

int main()
{
    int hour, minute, seconds;
    int ret;

    ret = sscanf("15:20:30", "%d:%d:%d", &hour, &minute, &seconds);
    LOG("hour=%d, minute=%d, seconds=%d", hour, minute, seconds);
    
    LOG("test LOG %s", "c");
    LOG("test %u", isalnum('2'));
    return 0;
}