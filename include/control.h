#ifndef __CONTROL_H__
#define __CONTROL_H__

#include "main.h"
#include "arrayList.h"

char* mystrcpy(char *str1, const char *str2);
char mystrcmp(const char* str1, const char* str2);
void swap(STUDENT* stu1, STUDENT* stu2);

char exit_program(STUDENT* pmember, char* pfilename,long long* pnum);
void insert_student(STUDENT* pmember, long long* pnum);
void delete_student(STUDENT* pmember, long long* pnum);

#endif