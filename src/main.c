#include "main.h"
#include "ohtable.h"

int file_read(STUDENT** file_mem,char* filename, __uint64* num);

int main()
{
    char* filename = "student_data.txt";
    int err=0;
    OHTBL htbl;
    STUDENT* file_mem=NULL;
    __uint64 num;

    file_read(&file_mem, filename, &num);
    ohtbl_init(&htbl, num);
    for(__uint64 i=0; i<num; i++)
    {
        err = ohtbl_insert(&htbl,&file_mem[i]);
        if(err == ERROR)
        {    
            printf("ERROR");
            return ERROR;
        }
    }
    printf("%lld\n",htbl.size);
    print_table(&htbl);

    free(htbl.table);
    free(file_mem);

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


