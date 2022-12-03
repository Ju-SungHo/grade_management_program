#include "print.h"

/* ---------------------------------------------------------------------------------
 * function name : _print_all
 * arguments
 *  - member : struct pointer to print the data
 *  - num : Number of Members
--------------------------------------------------------------------------------- */
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



/* ---------------------------------------------------------------------------------
 * function name : _search_member
 * arguments
 *  - htbl : hash table struct pointer for inserted data searching
 *  - sorting_mem : array to sort
 * return value
 *  - NO_DATA : no data in table
 *  - NO_ERROR : NO ERROR
--------------------------------------------------------------------------------- */
int _search_member(OHTBL* htbl, STUDENT** sorting_mem)
{
    __uint64 pos=0;

    if(ohtbl_size(htbl) != 0)
    {
        *sorting_mem = (STUDENT*)calloc(ohtbl_size(htbl),sizeof(STUDENT));

        for(__uint64 htbl_i=0, sort_i=0; htbl_i<htbl->positions; htbl_i++)
        {
            pos = ohtbl_lookup(htbl,htbl->table[htbl_i].id);
            if(pos != NOT_FOUND && pos != NO_DATA)
            {
                (*sorting_mem)[sort_i] = htbl->table[htbl_i];
                sort_i++;
            }
            if(sort_i == ohtbl_size(htbl))
                break;
        }
    }
    else
        return NO_DATA;


    return NO_ERROR;
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
    printf(">> 입력 : ");
    scanf("%d",&menu);  _IO_getc(stdin);

    return menu;
}


/* ---------------------------------------------------------------------------------
 * function name : print_student
 * arguments
 *  - htbl : hash table struct pointer for sorted data print
--------------------------------------------------------------------------------- */
void print_student(OHTBL* htbl)
{
    unsigned char mode,
                  mode_err = 0;
    int err;

    STUDENT* sorting_mem=NULL;

    while(!mode_err)
    {
        printf("\n *****출력 방식 선택****** \n");
        printf("|     1. 학번순 출력      |\n");
        printf("|     2. 이름순 출력      |\n");
        printf("|     3. 평균순 출력      |\n");
        printf(" *************************\n");
        printf(">> 입력 : ");
        scanf("%hhd",&mode);    _IO_getc(stdin);

        
        switch(mode)
        {
            case 1: 
            case 2:
            case 3:
                err = _search_member(htbl, &sorting_mem);
                if(err == NO_DATA)
                {
                    printf("table에 데이터가 없습니다.\n\n");
                    mode_err = 1;
                    break;
                }
                quick_sort(sorting_mem, mode, 0, ohtbl_size(htbl)-1, ohtbl_size(htbl));
                _print_all(sorting_mem,ohtbl_size(htbl));
                free(sorting_mem);
                mode_err = 1;
                break;
            /*
            case 4:
                // print the table
                print_table(htbl);
                mode_err = 1;
                break;
            */
            default:
                printf("해당 메뉴는 없습니다. 다시 선택하세요.\n\n");
        }
    }   
}
