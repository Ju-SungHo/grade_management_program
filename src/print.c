#include "print.h"

/* ---------------------------------------------------------------------------------
 * function name : _print_all
 * arguments
 *  - member : struct pointer to print the data
 *  - num : Number of Members
--------------------------------------------------------------------------------- */
void _print_all(const STUDENT pmember[],long long num)
{
    if(num != NO_DATA)
    {
        printf("\nID\tNAME%26cKOR\tENG\tMATH\tAverage\n",' ');
        for(int i=0; i<num; i++)
        {
            printf("%d\t",pmember[i].ID);
            printf("%-29s",pmember[i].name);

            for(int j=0; j<MAX_GRADE_NUM; j++)
            {
                printf("%.2f\t", pmember[i].Grade[j]);
            }
            printf("%.2f\n", pmember[i].Average);
        }
        printf("\n");
    }
    else
        printf("이 파일에는 data가 없습니다.\n");

}

/* ---------------------------------------------------------------------------------
 * function name : print_menu
 * return value
 *  - menu : user select menu
--------------------------------------------------------------------------------- */
int print_menu()
{
    int menu;
    printf(" --원하는 메뉴를 입력하세요--\n");
    printf("|     1. 학생 정보 출력      |\n");
    printf("|     2. 학생 정보 입력      |\n");
    printf("|     3. 학생 정보 삭제      |\n");
    printf("|     4. 프로그램 종료       |\n");
    printf(" ----------------------------\n");
    printf(">> 입력 :");
    scanf("%d",&menu);  _IO_getc(stdin);

    return menu;
}

/* ---------------------------------------------------------------------------------
 * function name : print_student
 * arguments
 *  - pmember : STUDENT pointer to print
 *  - pnum : pointer a Number of Members
--------------------------------------------------------------------------------- */
void print_student(STUDENT pmember[], long long* pnum)
{
    unsigned char mode;

    printf(" *****출력 방식 선택****** \n");
    printf("|     1. 학번순 출력      |\n");
    printf("|     2. 이름순 출력      |\n");
    printf("|     3. 평균순 출력      |\n");
    printf("|     4. 그대로 출력      |\n");
    printf(" ************************\n");
    printf(">> 입력 :");
    scanf("%hhd",&mode);    _IO_getc(stdin);
    
    switch(mode)
    {
        case 1: 
        case 2:
        case 3:
            quick_sort(pmember, mode, 0, (*pnum)-1);
            _print_all(pmember, *pnum);
            update_flag = 1;
            break;
        case 4:
            _print_all(pmember, *pnum);
            break;
        default:
            printf("해당 메뉴는 없습니다.\n");
    }
        
}

