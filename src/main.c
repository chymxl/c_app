#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <regex.h>

#include <app.h>

#include <cfile.h>

#define __FILE_ID__ "main.c"

#pragma pack(push)
#pragma pack(1)
typedef struct
{
    double d;
    int age;
    char ch;
    double d1;
    short sh;
}Student;

typedef struct
{
    
    char ch;
    short sh;
    int age;
    double d;
    double d1;
}Student1;
#pragma pack(pop)

typedef struct
{
    int age;
    char description[0]
}Student2;


int main()
{
    AAS_TestCase();
    return 0;
}