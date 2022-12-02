#include "ohtable.h"
#define COEFFICIENT 2

static STUDENT vacated_mem = {1};

// Robert Jenkins's hash function
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



// Thomas Wang's hash function
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



/* ---------------------------------------------------------------------------------
 * function name : _match
 * arguments
 *  - val1 : value 1 to compare
 *  - val2 : value 2 to compare
 * return value
 *  - the difference between two values
--------------------------------------------------------------------------------- */
static inline __uint64 _match(__uint64 val1, __uint64 val2)
{
    return val1 - val2;
}



/* ---------------------------------------------------------------------------------
 * function name : _ohtbl_resizing_insert
 * arguments
 *  - htbl : hash tale struct pointer for data insertion into new table
 *  - data : data before resizing to insert into new table
 * return value
 *  - ERROR : hash function misselection error
 *  - position : index where data is inserted
--------------------------------------------------------------------------------- */
__uint64 _ohtbl_resizing_insert(OHTBL* htbl, STUDENT* data)
{
    __uint64 position;

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



/* ---------------------------------------------------------------------------------
  * function name : _ohtbl_resizing
 * arguments
 *  - htbl : hash tale struct pointer for resizing
 * return value
 *  - ERROR : resizing error
 *  - NO_ERROR : NO ERROR
--------------------------------------------------------------------------------- */
int _ohtbl_resizing(OHTBL* htbl)
{
    STUDENT* old_table=htbl->table;
    __uint64 old_positions = htbl->positions;
    __uint64 pos=0;

    htbl->size=0;
    htbl->positions = (htbl->positions) * COEFFICIENT;

    htbl->table = (STUDENT*)calloc( htbl->positions ,sizeof(STUDENT));

    // rehashing
    for(__uint64 i=0; i<old_positions; i++)
    {
        if(old_table[i].id != 0 && old_table[i].id != vacated_mem.id)
        {    
            pos = _ohtbl_resizing_insert(htbl,&old_table[i]);
            if( pos == ERROR )
            {    
                printf("RESIZING ERROR");
                return ERROR;
            }
        }
    }
    free(old_table);
    return NO_ERROR;
}



/* ---------------------------------------------------------------------------------
 * function name : print_table
 * arguments
 *  - htbl : hash table struct pointer for slots print
--------------------------------------------------------------------------------- */
void print_table(OHTBL* htbl)
{
    printf("\ntable size = %lld\n", htbl->positions);
    printf("number of data = %lld\n", htbl->size);
    for(__uint64 i=0; i<(htbl->positions); i++)
    {
        if(htbl->table[i].id != 0 && htbl->table[i].id != vacated_mem.id)
            printf("slot[%lld] = ID : %lld \tname : %-30s\n", i, htbl->table[i].id, htbl->table[i].name);
        else
            printf("slot[%lld] = %lld vacated slot\n", i, htbl->table[i].id);
    }
    printf("\n");
}



/* ---------------------------------------------------------------------------------
 * function name : ohtbl_init
 * arguments
 *  - htbl : hash table struct pointer for initialization
 *  - positions : number of data in file, table size is determined
 * return value
 *  - ERROR : memory allocate fail
 *  - NO_ERROR : NO ERROR
--------------------------------------------------------------------------------- */
int ohtbl_init(OHTBL* htbl, __uint64 positions)
{
    htbl->threshold = 0.7;
    htbl->positions = positions*COEFFICIENT;
    
    if( (htbl->table = (STUDENT*)calloc(htbl->positions,sizeof(STUDENT)) ) == NULL)
        return ERROR;
    return NO_ERROR;
}



/* ---------------------------------------------------------------------------------
 * function name : ohtbl_insert
 * arguments
 *  - htbl : hash table struct pointer for data insertion
 *  - data : new data for insertion
 * return value
 *  - ERROR : resizing error || hash function misselection error
 *  - FOUND : Data already inserted
 *  - position : index where data is inserted
--------------------------------------------------------------------------------- */
__uint64 ohtbl_insert(OHTBL* htbl, STUDENT* data)
{
    __uint64 position;
    __uint64 err;

    if( ohtbl_load_factor(htbl) >= htbl->threshold )
    {
        err = _ohtbl_resizing(htbl);
        if(err == ERROR)
            return ERROR;
    }
        

    err = ohtbl_lookup(htbl,data->id);
    if(err != NO_DATA && err != NOT_FOUND)
    {
        return FOUND;
    }

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



/* ---------------------------------------------------------------------------------
 * function name : obtbl_remove
 * arguments
 *  - htbl : hash table struct pointer for data remove
 *  - remove_id : target idfor remove
 * return value
 *  - NO_DATA : there is no data 
 *  - ERROR : hash function misselection error
 *  - position : index where data is removed
--------------------------------------------------------------------------------- */
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



/* ---------------------------------------------------------------------------------
 * function name : ohtbl_lookup
 * arguments
 *  - htbl : hash table struct pointer for data look up
 *  - search_id : target id for look up
 * return value
 *  - NO_DATA : there is no data 
 *  - NOT_FOUND : there is no data 
 *  - position : index where data is located
--------------------------------------------------------------------------------- */
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
