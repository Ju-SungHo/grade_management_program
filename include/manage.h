#ifndef __MANAGE_H__
#define __MANAGE_H__

#include "main.h"
#include "ohtable.h"

char* mystrcpy(char *str1, const char *str2);
char mystrcmp(const char* str1, const char* str2);
void swap(STUDENT* stu1, STUDENT* stu2);

//int init(OHTBL* htbl, __uint64** idx_table, char* pfilename);
int init(OHTBL* htbl, char* pfilename);
int exit_program(OHTBL* htbl, char* pfilename);

int insert_student(OHTBL* htbl);
int remove_student(OHTBL* htbl);



#endif