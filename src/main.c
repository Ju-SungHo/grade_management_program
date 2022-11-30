#include "main.h"
#include "ohtable.h"

int file_read(STUDENT* file_mem,char* filename, __uint64* num);

int main()
{
    char* filename = "student_data.txt";

    OHTBL htbl;
    STUDENT* file_mem=NULL;
    __uint64 num;

    file_read(file_mem, filename, &num);
    ohtbl_init(&htbl, 100);


    return 0;
}

int file_read(STUDENT* file_mem,char* filename, __uint64* num)
{
    FILE* fp;

    if((fp = fopen(filename, "r")) == NULL)
        return ERROR;
    
    fscanf(fp,"%lld%*c",num);

    file_mem = (STUDENT*)malloc(sizeof(STUDENT)*(*num));
     for(int i=0; i<(*num); i++)
    {
        fscanf(fp,"%lld%%*c",&file_mem[i].id);
        fscanf(fp,"%[^|]%*c", file_mem[i].name);
    
        for(int j=0; j<MAX_GRADE_NUM; j++)
        {
            fscanf(fp,"%f", &file_mem[i].grade[j]);
        }
        fscanf(fp,"%f",&file_mem[i].average);
    }

    fclose(fp);
    return NO_ERROR;
}
