#include "main.h"
#include "arrayList.h"
#include "control.h"
#include "quick.h"
#include "print.h"

int main()
{
    char* filename = "student_data.txt";
    char err;
    int menu;
    long long num;

    STUDENT* member=NULL;
    
    if((err = init(&member, filename, &num)) == ERROR)
    {
        fprintf(stderr,"Can't Open \"%s\" file \n", filename);
        return ERROR;
    }

    printf("=====학생 성적 관리 프로그램=====\n\n");
    while(!exit_flag)
    {
        menu = print_menu();
        
        switch(menu)
        {   
            case 1:
                print_student(member,&num);
                break;
            case 2:
                insert_student(member, &num);
                update_flag = 1;
                break;
            case 3:
                delete_student(member,&num);
                update_flag = 1;
                break;
            case 4:
                exit_program(member, filename, &num);                
                exit_flag = 1;
                break;
            default :
                printf("해당 번호는 없는 기능입니다.\n");
                break;
        }
    }
    return 0;
}
