#ifndef __MAIN_H__
#define __MAIN_H__

#include <stdio.h>
#include <stdlib.h>

// Maximum Sizes
#define MAX_NAME_LEN 31
#define MAX_GRADE_NUM 3

// Return States
#define ERROR -1
#define NO_DATA 0
#define NO_ERROR 1

#define FOUND 2
#define NOT_FOUND -2


typedef unsigned long long __uint64;

typedef struct _student{
    __uint64 id;
    char name[MAX_NAME_LEN];
    float grade[3]; // 0:kor, 1:eng, 2:math
    float average;
} STUDENT;

char exit_flag;
char update_flag;


#endif