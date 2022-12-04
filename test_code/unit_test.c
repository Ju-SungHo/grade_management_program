#include "main.h"
#include "ohtable.h"
#include "manage.h"
#include "quick.h"
#include "printf.h"

int debug;

int file_read(STUDENT** file_mem,char* filename, __uint64* num);
void _print_all(const STUDENT pmember[], __uint64 num);

int main()
{
    char* filename = "student_data.txt";
    __uint64 err=0;
    STUDENT* member=NULL;
    __uint64 num;

    /******************************************************
     *
     * file read test
     * 
     *******************************************************/

    err = (__uint64)file_read(&member, filename, &num);
    if(err == ERROR)
    {
        printf("int file_read() = ERROR, %lld\n",err);
        return ERROR;
    }
    else
    {
        printf("int file_read() = OK\n");
    }



    /******************************************************
     *
     * quick sort test
     * 
     *******************************************************/

    printf("\nvoid quick_sort() & void _print_all() test");
    quick_sort(member,1,0,num-1,num);
    _print_all(member,num);
    printf("\n");

    /******************************************************
     * 
     * ohtbl function test
     * 
     *******************************************************/
    
    OHTBL htbl;
    
    err = (__uint64)ohtbl_init(&htbl, num);
    if(err == ERROR)
    {
        printf("int ohtbl_init() = ERROR, %lld\n",err);
        return ERROR;
    }
    else
    {
        printf("int ohtbl_init() = OK\n");
    }
        
    
    for(__uint64 i=0; i<num; i++)
    {
        err = ohtbl_insert(&htbl,&member[i]);
        if( err == ERROR )
        {    
            printf("__uint64 ohtbl_insert() = ERROR, %lld\n",err);
            return ERROR;
        }
    }
    if(debug)
        print_table(&htbl);

    // Already inserted data check test
    free(member);
    member = (STUDENT*)calloc(1,sizeof(STUDENT));
    member->name[1] = '\0';
    member->id = 20161094;

    err = ohtbl_insert(&htbl,member);
    if( err == ERROR )
    {    
        printf("__uint64 ohtbl_insert() = ERROR, %lld\n",err);
        return ERROR;
    }
    else if(err == FOUND)
    {
        if(debug)
            printf("ID = %lld is Already inserted data\n",member->id);
    }
    

    // Resizing test
    for(__uint64 i=0; i<300; i++)
    {
        member->id = 20171001+i;
        member->name[0] = 'A'+ (i%26);

        err = ohtbl_insert(&htbl,member);
        if( err == ERROR )
        {    
            printf("int _ohtbl_resizing() = ERROR, %lld\n",err);
            printf("int _ohtbl_resizing_insert() = ERROR, %lld\n",err);
            return ERROR;
        }
        else if(err == FOUND)
        {
            if(debug)
                printf("ID = %lld is Already inserted data\n",member->id);
        }
    }
    if(debug)
        print_table(&htbl);
    printf("int _ohtbl_resizing() = OK\n");
    printf("__uint64 _ohtbl_resizing_insert() = OK\n");
    printf("__uint64 ohtbl_insert() = OK\n");


    // lookup test
    printf("__uint64 ohtbl_lookup() test : ");
    err = ohtbl_lookup(&htbl,20171001);
    if(err == NO_DATA)
        printf("NO DATA = OK\n");
    else if(err == NOT_FOUND)
        printf("NOT FOUND = OK\n");
    else
        printf("FOUND = OK\n");


    // Remove test 2017[from 1001 to 1020]
    for(__uint64 i=0; i<20; i++)
    {
        member->id = 20171001+i;

        err = obtbl_remove(&htbl,member->id);
        if(err == ERROR)
        {    
            printf("__uint64 ohtbl_remove() = ERROR, %lld\n",err);
            return ERROR;
        }
        else if(err == NO_DATA)
        {
            if(debug)
                printf("ID = %lld is not exist in table\n",member->id);
        }
        else
        {   
            if(debug)
                printf("remove ID = %lld\n", member->id);
        }
    }



    // Not exist data check test
    member->id = 20171100;

    err = obtbl_remove(&htbl,member->id);
    if(err == ERROR)
    {    
        printf("__uint64 ohtbl_remove() = ERROR, %lld\n",err);
        return ERROR;
    }
    else if(err == NO_DATA)
    {
        if(debug)
            printf("ID = %lld is not exist in table\n",member->id);
    }
    else
    {
        if(debug)
            printf("remove ID = %lld\n", member->id);
    }
    printf("__uint64 ohtbl_remove() = OK\n");
    printf("\n");
    
    free(member);
    free(htbl.table);


    /******************************************************
     *
     * swap & string function test
     * 
     *******************************************************/

    STUDENT member2[2];
    int res;

    member2[0].id = 20;
    member2[1].id = 30;
    
    printf("void swap() test\n");
    printf("member[0]id. = %lld member[1].id = %lld\n",member2[0].id ,member2[1].id);
    swap(&member2[0], &member2[1]);
    printf("member[0].id = %lld member[1].id = %lld\n",member2[0].id ,member2[1].id);


    printf("\nchar mystrcmp() test\n");
    for(int i = 0; i<5; i++)
    {
        member2[0].name[i] = 'A'+i;
        member2[1].name[i] = 'A'+i;    
    }
    res = (int)mystrcmp(member2[0].name,member2[1].name);
    printf("same string result = %d\n",res);

    for(int i = 0; i<5; i++)
    {
        member2[0].name[i] = 'A'+i;
        member2[1].name[i] = 'B'+i;    
    }
    res = (int)mystrcmp(member2[0].name,member2[1].name);
    printf("diff string(str1 < str2) result = %d\n",res);
    
    res = (int)mystrcmp(member2[1].name,member2[0].name);
    printf("diff string(str1 > str2) result = %d\n",res);


    printf("\nchar* mystrcpy() test\n");
    mystrcpy(member2[0].name,member2[1].name);
    printf("member[0].name =%s member[1].name =%s\n",member2[0].name,member2[1].name);


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


void _print_all(const STUDENT pmember[], __uint64 num)
{
    if(num != NO_DATA)
    {
        printf("\n학생 수 = %lld\n",num);
        printf("ID%8c\tNAME%26cKOR\tENG\tMATH\tAverage\n",' ',' ');
        for(int i=0; i<num; i++)
        {
            printf("%-8lld\t",pmember[i].id);
            printf("%-30s",pmember[i].name);

            for(int j=0; j<MAX_GRADE_NUM; j++)
            {
                printf("%.2f\t", pmember[i].grade[j]);
            }
            printf("%.2f\n", pmember[i].average);
        }
        printf("\n");
    }
    else
        printf("이 파일에는 data가 없습니다.\n");

}