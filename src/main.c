#include "main.h"
#include "ohtable.h"

int file_read(STUDENT** file_mem,char* filename, __uint64* num);

int main()
{
    char* filename = "student_data.txt";
    int err=0;

    OHTBL htbl;
    STUDENT* member=NULL;
    __uint64 num;

    file_read(&member, filename, &num);

    // Create Open Addressing Hash Table test
    ohtbl_init(&htbl, num);
    for(__uint64 i=0; i<num; i++)
    {
        err = ohtbl_insert(&htbl,&member[i]);
        if(err == ERROR)
        {    
            printf("ERROR");
            return ERROR;
        }
    }
    print_table(&htbl);
    free(member);


    // Resizing test
    member = (STUDENT*)calloc(1,sizeof(STUDENT));
    member->name[1] = '\0';

    for(__uint64 i=0; i<70; i++)
    {
        member->id = 20171001+i;
        member->name[0] = 'A'+ (i%26);

        err = ohtbl_insert(&htbl,member);
        if(err == ERROR)
        {    
            printf("ERROR");
            return ERROR;
        }
        
    }
    print_table(&htbl);
    
    // Remove test from 1001 to 1020
    for(__uint64 i=0; i<20; i++)
    {
        member->id = 20171001+i;

        err = obtbl_remove(&htbl,member->id);
        if(err == ERROR)
        {    
            printf("ERROR");
            return ERROR;
        }
        
    }
    print_table(&htbl);

    free(member);
    free(htbl.table);
    

    return 0;
}

int file_read(STUDENT** file_mem,char* filename, __uint64* num)
{
    FILE* fp;
    STUDENT* tmp=NULL;

    if((fp = fopen(filename, "r")) == NULL)
        return ERROR;
    
    fscanf(fp,"%lld%*c",num);

    tmp = (STUDENT*)malloc(sizeof(STUDENT)*(*num));
     for(int i=0; i<(*num); i++)
    {
        fscanf(fp,"%lld%%*c",&tmp[i].id);
        fscanf(fp,"%[^|]%*c", tmp[i].name);
    
        for(int j=0; j<MAX_GRADE_NUM; j++)
        {
            fscanf(fp,"%f", &tmp[i].grade[j]);
        }
        fscanf(fp,"%f",&tmp[i].average);
    }

    *file_mem = tmp;

    fclose(fp);
    return NO_ERROR;
}


