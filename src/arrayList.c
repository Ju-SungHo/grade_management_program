#include "arrayList.h"


/* ---------------------------------------------------------------------------------
 * function name : Init
 * arguments
 *  - pmember : struct pointer to be dynamically allocated the data of file
 *  - pfilename : file name to read
 *  - pnum : pointer a Number of Members
 * retrun vale
 *  - Error state[NO_ERROR=0, ERROR=-1]
--------------------------------------------------------------------------------- */
char init(STUDENT** pmember,const char* pfilename, long long* pnum)
{
    FILE* fp;
    STUDENT* mem_tmp=NULL;
    
    if ((fp = fopen(pfilename, "r")) == NULL)
        return ERROR;

    // Get Number of data
    fscanf(fp,"%lld%*c",pnum);

    if(*pnum == NO_DATA)
    {
        *pmember = (STUDENT*)malloc(sizeof(STUDENT)*(1));
        fclose(fp);
        return NO_DATA;
    }

    // Data Reading 
    mem_tmp = (STUDENT*)malloc(sizeof(STUDENT)*(*pnum));
    for(int i=0; i<(*pnum); i++)
    {
        fscanf(fp,"%d%%*c",&mem_tmp[i].ID);
        fscanf(fp,"%[^|]%*c", mem_tmp[i].name);
    
        for(int j=0; j<MAX_GRADE_NUM; j++)
        {
            fscanf(fp,"%f", &mem_tmp[i].Grade[j]);
        }
        fscanf(fp,"%f",&mem_tmp[i].Average);
    }
    
    *pmember = mem_tmp;
    

    fclose(fp);
    return NO_ERROR;
}

/* ---------------------------------------------------------------------------------
 * function name : insert
 * arguments
 *  - pmember : struct pointer to reallocate
 *  - pnum : pointer a Number of Members
 *  - pmem_tmp : New STUDENT data
--------------------------------------------------------------------------------- */
void insert(STUDENT* pmember, long long* pnum, STUDENT* pmem_tmp)
{
    // resizing
    long long size = sizeof(STUDENT) * (*pnum);
    STUDENT* err = realloc(pmember,size);

    if(err == NULL)
    {
        free(pmember);
        printf("용량 초과");
    }
    
    // insert new data at end element in STUDENT array 
    pmember[(*pnum)-1].ID = pmem_tmp->ID;
    pmember[(*pnum)-1].Average = pmem_tmp->Average;

    for(int i = 0; i<MAX_GRADE_NUM; i++)
    {
        pmember[(*pnum)-1].Grade[i] = (pmem_tmp->Grade[i]);
    }

    mystrcpy(pmember[(*pnum)-1].name,pmem_tmp->name);
        
    
}

/* ---------------------------------------------------------------------------------
 * function name : delete
 * arguments
 *  - pmember : struct pointer to delete a student
 *  - pnum : pointer a Number of Members
 *  - del_id : students ID to delete
--------------------------------------------------------------------------------- */
char delete(STUDENT* pmember, long long* pnum, int del_id)
{
    long long idx=0;

    while(1)
    {
        // Search target ID
        if(del_id != pmember->ID)
        {
            idx++;
            pmember++;
        }
        else
        {   
            // Delete tartget STUDENT data by overiding next STUDENT data
            for(long long i=0; i<((*pnum)-idx-1);i++)
                pmember[i] = pmember[i+1];
            (*pnum)--;
            printf("삭제되었습니다.\n\n");
            return NO_ERROR;
        }

        // Target ID is not exist
        if(idx == (*pnum))
        {
            printf("해당 학번의 학생은 없습니다.\n");
            return NO_DATA;
        }
    }
}

