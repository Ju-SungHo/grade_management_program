#ifndef __OHTABLE_H__
#define __OHTABLE_H__

#include "main.h"


__uint64 hash1(__uint64 key);
__uint64 hash2(__uint64 key);

typedef struct _ohtbl
{
    __uint64 positions;
    __uint64 size;
    float factor;
    
    STUDENT* table;
}   OHTBL;

int ohtbl_init(OHTBL* htbl, __uint64 positions);
int _ohtbl_resizing(OHTBL* htbl);
void print_table(OHTBL* htbl);

__uint64 ohtbl_insert(OHTBL* htbl, STUDENT* data);
__uint64 obtbl_remove(OHTBL* htbl, __uint64 remove_id);
__uint64 ohtbl_lookup(OHTBL* htbl, __uint64 search_id);



#define ohtbl_size ((htbl)->size)


#endif