#include "ohtable.h"

__uint64 _hash1(__uint64 key)
{
	key += (key<<12);
	key ^= (key>>22);
	key += (key<<4);
	key ^= (key>>9);
	key += (key<<10);
	key ^= (key>>2);
	key += (key<<7);
	key ^= (key>>12);

	return key;
}

__uint64 _hash2(__uint64 key)
{
	key = ~key + (key << 21);	// key = (key << 21) - key - 1
	key ^= (key >> 24);
	key += (key << 3) + (key << 8);	// key = key * 265
	key ^= (key >> 14);
	key += (key << 2) + (key << 4);	// key = key * 21
	key ^= (key >> 28);
	key += (key << 31);

	return key;
}

__uint64 _match(__uint64 val1, __uint64 val2)
{
    return val1 - val2;
}

static STUDENT vacated_mem = {1};

int ohtbl_init(OHTBL* htbl, __uint64 positions)
{
    htbl->factor = 0.7;
    htbl->positions = positions*4;
    
    if( (htbl->table = (STUDENT*)calloc(htbl->positions,sizeof(STUDENT)) ) == NULL)
        return ERROR;
    return NO_ERROR;
}

__uint64 ohtbl_insert(OHTBL* htbl, STUDENT* data)
{
    STUDENT* tmp = data;
    __uint64 position;
    __uint64 err;

    if(htbl->size == htbl->positions)
        ohtbl_resizing(htbl);
    
    
    for(__uint64 i=0; i<htbl->positions; i++)
    {
        position = ( _hash1(data->id) + (i * _hash2(data->id)) ) % htbl->positions;

        if(htbl->table[position].id == 0 || htbl->table[position].id == vacated_mem.id)
        {
            htbl->table[position] = *data;
            htbl->size++;
            return position;    //넣은 위치
        }
    }
    return ERROR;
}

__uint64 obtbl_remove(OHTBL* htbl, __uint64 remove_id)
{
    __uint64 position;

    for(__uint64 i=0; i<htbl->positions; i++)
    {
        position = ( _hash1(remove_id) + (i * _hash2(remove_id)) ) % htbl->positions;

        if(htbl->table[position].id == 0)
        {
            return NO_DATA;
        }
        else if(htbl->table[position].id == vacated_mem.id)
        {
            continue;
        }
        else if(!_match(htbl->table[position].id, remove_id))
        {
            htbl->table[position].id = vacated_mem.id;
            htbl->size--;
            return position;
        }
    }
    return ERROR;
}

__uint64 ohtbl_lookup(OHTBL* htbl, __uint64 search_id)
{
    __uint64 position;

    for(__uint64 i=0; i<htbl->positions; i++)
    {
        position = ( _hash1(search_id) + (i * _hash2(search_id)) ) % htbl->positions;

        if(htbl->table[position].id == 0)
        {
            return NO_DATA;
        }
        else if(!_match(htbl->table[position].id, search_id))
        {
            return position;
        }
    }
    return NOT_FOUND;
}

int ohtbl_resizing(OHTBL* htbl)
{
    __uint64 count=0;
    __uint64 i=0;

    htbl->positions = (htbl->positions) * 4;
    if( (realloc(htbl->table, (htbl->positions) * sizeof(STUDENT))) == NULL)
        return ERROR;
    
    // rehashing
    while(count <= htbl->size)
    {
        if(htbl->table[i].id != 0 && htbl->table[i].id != vacated_mem.id)
        {    
            ohtbl_insert(htbl,&htbl->table[i]);
            count++;
        }
        i++;
    }
    return NO_ERROR;
}

void print_table(OHTBL* htbl)
{
    __uint64 count=0;
    __uint64 i=0;

    while(count < htbl->size)
    {
        if(htbl->table[i].id != 0 && htbl->table[i].id != vacated_mem.id)
        {
            printf("slot[%lld] = %lld\n", i,htbl->table[i].id);
            count++;
        }
        i++;
    }
}