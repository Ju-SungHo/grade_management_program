#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "main.h"
#include "control.h"

char init(STUDENT** pmember, const char* pfilename, long long* pnum);

void insert(STUDENT* pmember, long long* pnum, STUDENT* pmem_tmp);
char delete(STUDENT* pmember, long long* pnum, int del_tmp);

#endif