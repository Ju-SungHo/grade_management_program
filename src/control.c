#include "control.h"

/* ---------------------------------------------------------------------------------
 * function name : _input_grade
 * return value
 *  - num : input number in range
--------------------------------------------------------------------------------- */
float _input_grade()
{
    float num;

    while(1)
    {
        scanf("%f",&num);
        _IO_getc(stdin);

        if(num>=0.0 && num<=100.0)
            return num;
        else
            printf("범위를 벗어난 숫자 입니다. 다시 입력하세요 :");
    }

}

/* ---------------------------------------------------------------------------------
 * function name : swap
 * arguments
 *  - stu1 : STUDENT member to swap stu2
 *  - stu2 : STUDENT member to swap stu1
--------------------------------------------------------------------------------- */
void swap(STUDENT* stu1, STUDENT* stu2)
{
    STUDENT tmp = *stu2;
    *stu2 = *stu1;
    *stu1 = tmp;
}

/* ---------------------------------------------------------------------------------
 * function name : mystrcpy
 * arguments
 *  - str1 : string 1 to paste
 *  - str2 : string 2 to copy
 * retrun vale
 *  str1 : copied string address
--------------------------------------------------------------------------------- */
char* mystrcpy(char *str1, const char *str2)
{
	char* tmp = str1;

    while(*str2)
    {
        *tmp++ = *str2++;
    }

    *tmp = '\0';
    return str1;
}

/* ---------------------------------------------------------------------------------
 * function name : mystrcmp
 * arguments
 *  - str1 : string 1 to compare
 *  - str2 : string 2 to comppare
 * retrun vale
 *  - str1 > str2  => +
 *  - str1 == str2 => 0
 *  - str1 < str2  => -
--------------------------------------------------------------------------------- */
char mystrcmp(const char* str1, const char* str2)
{
    while(*str1 && (*str1 == *str2))
    {
        str1++; 
        str2++;
    }
    
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}


/* ---------------------------------------------------------------------------------
 * function name : exit_program
 * arguments
 *  - pmember : struct pointer to save in file
 *  - pfilename : file name to write
 *  - pnum : pointer a Number of Members
 * retrun vale
 *  - Error state[NO_ERROR=0, ERROR=-1]
--------------------------------------------------------------------------------- */
char exit_program(STUDENT* pmember, char* pfilename,long long* pnum)
{
    if(update_flag)
    {
        FILE* fp;
    
        if ((fp = fopen(pfilename, "w")) == NULL)
            return ERROR;  

        fprintf(fp,"%lld",*pnum);
        fprintf(fp,"\n");

        for(int i=0; i<*pnum; i++)
        {
            fprintf(fp,"%02d",pmember[i].ID);
            fprintf(fp," %-30s|",pmember[i].name);
            
            for(int j=0; j<MAX_GRADE_NUM; j++)
            {
                fprintf(fp,"%.2f ", pmember[i].Grade[j]);
            }
            fprintf(fp,"%.2f ", pmember[i].Average);
            fprintf(fp,"\n");
        }

        fclose(fp);
    }
    
    free(pmember);
    return NO_ERROR;
}

/* ---------------------------------------------------------------------------------
 * function name : insert_student
 * arguments
 *  - pmember : struct pointer to insert new data 
 *  - plist : list to reallocate
 *  - pnum : pointer a Number of Members
--------------------------------------------------------------------------------- */
void insert_student(STUDENT* pmember, long long* pnum)
{
    STUDENT mem_tmp;

    printf("\n-----------------------------학생 정보 입력------------------------------------\n");
    printf("[예시. 학번 : 54 | 이름 : Hong gil dong | 국어 : 100 | 수학 : 100 | 영어 : 100]\n");
    printf("-------------------------------------------------------------------------------\n");

    printf("> 학번 : ");
    scanf("%d",&mem_tmp.ID);    _IO_getc(stdin);

    printf("> 이름 : ");  
    scanf("%[^\n]%*c",mem_tmp.name); 

    printf("\n과목별 성적\n");
    printf("> 국어 : ");
    mem_tmp.Grade[0] = _input_grade();       

    printf("> 수학 : ");
    mem_tmp.Grade[1] = _input_grade();      

    printf("> 영어 : ");
    mem_tmp.Grade[2] = _input_grade();       

    // Calculate Avergage
    mem_tmp.Average = (( mem_tmp.Grade[0] + mem_tmp.Grade[1] + mem_tmp.Grade[2] ) / (float)MAX_GRADE_NUM );
    (*pnum)++;

    insert(pmember, pnum, &mem_tmp);

}


/* ---------------------------------------------------------------------------------
 * function name : delete_student
 * arguments
 *  - pmember : struct pointer to insert new data 
 *  - pnum : pointer a Number of Members
--------------------------------------------------------------------------------- */
void delete_student(STUDENT* pmember, long long* pnum)
{
    if((*pnum))
    {
        int del_id;

        printf("\n-----------------------------학생 정보 삭제------------------------------------\n");
        printf("삭제할 학생의 학번을 입력하세요.\n");
        printf("> 학번 : ");
        scanf("%d",&del_id); _IO_getc(stdin);

        delete(pmember, pnum, del_id);
    }
    else
        printf("파일에 정보가 없습니다.\n");
    
}

