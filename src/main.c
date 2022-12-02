#include "main.h"
#include "ohtable.h"
#include "manage.h"
#include "quick.h"
#include "print.h"

int main()
{
    char* filename = "student_data.txt";
    int menu;
    int err;
    
    OHTBL htbl;
    
    printf("==========================================\n");
    printf("*         학생 성적 관리 프로그램        *\n");
    printf("==========================================\n\n");

    if(init(&htbl, filename) == ERROR)
        return ERROR;

    while(!exit_flag)
    {
        menu = print_menu();


        switch(menu)
        {
            case 1:
                print_student(&htbl);
                break;
            case 2:
                err = insert_student(&htbl);
                if(err == ERROR)
                    return ERROR;
                update_flag = 1;
                break;
            case 3:
                err = remove_student(&htbl);
                if(err == ERROR)
                    return ERROR;
                update_flag = 1;
                break;
            case 4:
                err = exit_program(&htbl,filename);
                if(err == ERROR)
                {
                    printf("%s 파일은 열 수 없습니다.",filename);
                    return ERROR;
                }
                exit_flag = 1;
                break;
            default:
                printf("해당 메뉴는 없습니다. 다시 입력하세요.\n\n");
                break;
        }
    }


    return 0;
}
