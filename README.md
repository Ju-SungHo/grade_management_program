# 성적 관리 프로그램

1. [Start](#1-start)
    - [Clone](#clone)
    - [Build](#build)
2. [프로그램 실행 방법](#2-프로그램-실행-방법)
	- [grade_manage 프로그램 실행](#grade_manage-프로그램-실행)
	- [unit_test 프로그램 실행](#unit_test-프로그램-실행)	
3. [프로그램 구조](#3-프로그램-구조)
    - [프로그램 구조도](#프로그램-구조도)
    - [자료구조 및 알고리즘](#자료구조-및-알고리즘)

# 1. Start

### Clone

성적 관리 프로그램 repository를 `grade_management_program` 디렉토리에 clone.

```bash
~$ git clone https://github.com/Juwayne/grade_management_program.git grade_management_program
```

### Build

|개발 환경|언어|Compiler|
|:---:|:---:|:---:|
|<img src="https://img.shields.io/badge/UBUNTU18.04.5-E95420?style=for-the-badge&logo=UBUNTU&logoColor=white">|<img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=C&logoColor=white">|**gcc**|

Build는 `Makefile`을 이용하여 구성하였습니다.  
프로그램의 루트 디렉토리인 `grade_management_program` 디렉토리에서 `make` 를실행하여 Build할 수 있습니다.

```bash
~$ cd grade_management_program

# grade_manage program build
~/grade_management_program$ make

#unit_test program build
~/grade_management_program$ make test
```

만약, make후 생성 된 [`.o` , `.d` , `grade_manage` , 'unit_test']을 삭제하고 싶으면 make clean을 실행하여 제거할 수 있습니다.

```bash
~/grade_management_program$ make clean	# grade_manage
~/grade_management_program$ make tclean	# unit_test
```  

<details>
<summary>Makefile 내용</summary>
<div markdown="1">

    ```makefile
    CROSS=
    CC=$(CROSS)gcc 

    # C 컴파일러 옵션
    CFLAGS= -Wall

    # 링커 옵션
    LDFLAGS=

    # 헤더파일 경로
    INCLUDE=-Iinclude/

    # 소스 파일 디렉토리
    SRC_DIR=./src

    # 오브젝트 파일 디렉토리
    OBJ_DIR=./obj

    # 테스트 파일 디렉토리
    TEST_DIR=./test_code

    # 생성하고자 하는 실행 파일 이름
    TARGET=grade_manage

    # 테스트 파일 이름 
    TEST_TARGET=unit_test



    # Make 할 소스 파일들
    # wildcard 로 SRC_DIR 에서 *.cc 로 된 파일들 목록을 뽑아낸 뒤에
    # notdir 로 파일 이름만 뽑아낸다.
    # (e.g SRCS 는 foo.cc bar.cc main.cc 가 된다.)
    SRCS=$(notdir $(wildcard $(SRC_DIR)/*.c))
    OBJS=$(SRCS:.c=.o)

    # OBJS 안의 object 파일들 이름 앞에 $(OBJ_DIR)/ 을 붙인다. = $(OBJ_DIR)/$(OBJS)
    OBJECTS=$(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
    DEPS=$(OBJECTS:.o=.d)


    # unit test를 위한 SRC, OBJS, DEPS 파일들
    TEST_SRCS=manage.c ohtable.c quick.c unit_test.c
    TEST_OBJS=$(TEST_SRCS:.c=.o)

    # TEST_OBJS들 앞에 $(ONJ_SIR)/을 붙인다.
    TEST_OBJECTS=$(patsubst %.o,$(OBJ_DIR)/%.o,$(TEST_OBJS))
    TEST_DEPS=$(TEST_OBJECTS:.o=.d)


    all : $(TARGET)

        $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	    $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MD $(LDFLAGS)

    $(TARGET) : $(OBJECTS)
    	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)


    test : $(TEST_TARGET)

    $(OBJ_DIR)/%.o : $(TEST_DIR)/%.c 
	    $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MD $(LDFLAGS)

    $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c 
	    $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MD $(LDFLAGS)

    $(TEST_TARGET) : $(TEST_OBJECTS)
    	$(CC) $(CFLAGS) $(TEST_OBJECTS) -o $(TEST_TARGET) $(LDFLAGS)


    tclean :
	    rm -r $(TEST_OBJECTS) $(TEST_DEPS) $(TEST_TARGET) 

    clean :
	    rm -r $(OBJECTS) $(DEPS) $(TARGET) 


    -include $(DEPS)
    ```
</div>
</details>

    
    
- `grade_manage` Build 결과  

    <img src="https://user-images.githubusercontent.com/84081595/205446829-c14dadf1-6cb5-47d8-b48c-e525fcac3f3e.png"  width="550" height="200"/>  
    
- `unit_test' Build 결과  

    <img src="https://user-images.githubusercontent.com/84081595/205478051-54c3a7b0-337a-4414-bc1b-d3fc51fe4861.png"  width="550" height="160"/>
    

    
- **[필요 시 사용]** make, clean의 편의를 위한 alias
 
    해당 디렉토리로 이동하기 또는 이동하여 make ,clean하기를 편하게 할 수 있도록 해주는 `alias`  
    자신이 사용 가능한 편집기(ex. vi/vim, nano, etc)를 사용하여 `~/.bashrc`에 들어가 아래 내용을 붙여넣고  
    `source ~/.bashrc` 실행
    
    ```bash
    alias gmake='cd ~/grade_management_program; sudo make'
    alias gmclean='cd ~/grade_management_program; sudo make clean'
    alias gmcd='cd ~/grade_management_program'
    alias gmtest='cd ~/grade_management_program; sudo make test'
    alias gmtclean='cd ~/grade_management_program; sudo make tclean'
    
    # 만약 다른 디렉토리에 이 repository를 받았으면 "~/{directory}" 부분만 환경에 맞게 바꿔주면 된다.
    ```
    
    - `gcd` 사용 결과 
    
        <img src="https://user-images.githubusercontent.com/84081595/205446865-f61d89cc-5c7d-4ffc-98b8-b2f7368c26e4.png"  width="400" height="90"/>
    

    

# 2. 프로그램 실행 방법  

### grade_manage 프로그램 실행 

`grade_management_program` 디렉토리에 생성된 프로그램인 `grade_manage`을 실행시키면 아래 사진과 같이 사용할 수 있는 메뉴들이 터미널창에 출력되고 입력을 기다리게 됩니다.

```bash
~$ cd grade_management_program
~/grade_management_program$ ./grade_manage
```

- **실행 화면**
    
    사용할 기능에 대한 입력은 메뉴 앞에 나와있는 번호를 입력해 주면 됩니다.  
    [ 1 : 정보 출력, 2 : 정보 입력, 3 : 정보 삭제, 4 : 프로그램 종료 ]  
    <img src="https://user-images.githubusercontent.com/84081595/205446924-21c9ec8b-03a8-4000-962d-017a099c59b6.png"  width="500" height="250"/>
    
- **각 기능 별 설명**  
    1.  **학생 정보 출력**  

        [**학번순, 이름순, 평균순**] 3가지 정렬 기준이 있고, 원하는 정렬 기준에 대한 번호를 입력하면   
        그에 맞춰 정렬 후 출력해 준다.   
        <img src="https://user-images.githubusercontent.com/84081595/205446935-a1fa56af-4f5e-4107-af1a-dc594e9ed548.png"  width="270" height="160"/>
        
    2.  **학생 정보 입력**  

        [**입력할 학생의 수, 학생의 정보**]를 입력받아 학생 정보를 저장한다.  
        <img src="https://user-images.githubusercontent.com/84081595/205446945-2069c8b0-9676-48d3-9d3f-b2f5da3820af.png"  width="550" height="250"/>
    
    3.  **학생 정보 삭제**  

        [**삭제할 학생의 학번**]을 입력받아 학생 정보를 삭제한다.  
        <img src="https://user-images.githubusercontent.com/84081595/205446955-109cdf36-199c-4d7f-a6d9-258f22ea79b2.png"  width="550" height="150"/>
        
    4.  **프로그램 종료**  

        [**변경된 사항**]이 있으면 파일에 저장한 후 종료하고 없으면 바로 종료한다.  
        <img src="https://user-images.githubusercontent.com/84081595/205446960-a1001dde-90d4-4f7b-9a5c-cedca54d1930.png"  width="270" height="160"/>    
        

### unit_test 프로그램 실행  

`grade_management_program` 디렉토리에 생성된 `unit_test` 프로그램을 싱행시키기 위해서는 아래의 명령어를 실행하면 됩니다.
	
```bash
~$ cd grade_management_program
~/grade_management_program$ ./unit_test
```
	
   - **실행 화면**  
		<img src="https://user-images.githubusercontent.com/84081595/205478867-eef9c221-ed75-4888-a1be-66ccb7494765.png"  width="700" height="250"/> 


# 3. 프로그램 구조

### 프로그램 구조도

![Untitled 7](https://user-images.githubusercontent.com/84081595/205458474-10a57ff6-9b48-4633-9c4e-0849eba6a72c.png)



### **자료구조 및 알고리즘**

- 학생 정보 **삽입**, **삭제** (**insert, remove**) = **Hash Table**  
    - |사용한 Hash fuction| 이름 |
      |:---:|:---:|
      |**hash1()**|[Robert Jenkins' 32bit hash function](http://sweeper.egloos.com/925740#:~:text=%EB%8B%A4%ED%96%89%ED%9E%88%20%EC%9C%84%EC%9D%98%203%EA%B0%80%EC%A7%80%20%EC%A1%B0%EA%B1%B4%EC%9D%84%20%EB%A7%8C%EC%A1%B1%EC%8B%9C%ED%82%A4%EB%8A%94%20%EC%A2%8B%EC%9D%80%20%ED%95%B4%EC%89%AC%20%ED%95%A8%EC%88%98%EB%93%A4%EC%9D%B4%20%EB%82%98%EC%99%80%20%EC%9E%88%EC%9C%BC%EB%A9%B0%20Jenkins%EC%9D%98%20One%2Dat%2Da%2Dtime%20%ED%95%B4%EC%89%AC%20%ED%95%A8%EC%88%98%EA%B0%80%20%EB%8C%80%ED%91%9C%EC%A0%81%EC%9D%B8%20%EC%98%88%EB%9D%BC%20%ED%95%A0%20%EC%88%98%20%EC%9E%88%EB%8B%A4.%2032/64%EB%B9%84%ED%8A%B8%20int%ED%98%95%EC%9D%98%20%EA%B4%9C%EC%B0%AE%EC%9D%80%20%ED%95%B4%EC%89%AC%20%ED%95%A8%EC%88%98%EB%A5%BC%20%EC%B2%A8%EB%B6%80%ED%95%9C%EB%8B%A4.%C2%A0%2D%2D%2D%3E%20int_hash_func.txt)|
      |**hash2()**|[Thomas Wang's hash function](http://sweeper.egloos.com/925740#:~:text=%EB%8B%A4%ED%96%89%ED%9E%88%20%EC%9C%84%EC%9D%98%203%EA%B0%80%EC%A7%80%20%EC%A1%B0%EA%B1%B4%EC%9D%84%20%EB%A7%8C%EC%A1%B1%EC%8B%9C%ED%82%A4%EB%8A%94%20%EC%A2%8B%EC%9D%80%20%ED%95%B4%EC%89%AC%20%ED%95%A8%EC%88%98%EB%93%A4%EC%9D%B4%20%EB%82%98%EC%99%80%20%EC%9E%88%EC%9C%BC%EB%A9%B0%20Jenkins%EC%9D%98%20One%2Dat%2Da%2Dtime%20%ED%95%B4%EC%89%AC%20%ED%95%A8%EC%88%98%EA%B0%80%20%EB%8C%80%ED%91%9C%EC%A0%81%EC%9D%B8%20%EC%98%88%EB%9D%BC%20%ED%95%A0%20%EC%88%98%20%EC%9E%88%EB%8B%A4.%2032/64%EB%B9%84%ED%8A%B8%20int%ED%98%95%EC%9D%98%20%EA%B4%9C%EC%B0%AE%EC%9D%80%20%ED%95%B4%EC%89%AC%20%ED%95%A8%EC%88%98%EB%A5%BC%20%EC%B2%A8%EB%B6%80%ED%95%9C%EB%8B%A4.%C2%A0%2D%2D%2D%3E%20int_hash_func.txt)|  

    - **Open-addressing** : Double hashing probing  
    
        ~~~c
        position = ( _hash1(data->id) + (i * _hash2(data->id)) ) % htbl->positions;
        ~~~  
    
    - **Table Resizing** : load factor threshold를 70%로 설정하였고, 이를 넘길 시 load factor가 약 25%가 되도록 resizing을 진행한다.
        ~~~c
        // ohtbl_insert function
        if( ohtbl_load_factor(htbl) >= htbl->threshold )
        {
            err = _ohtbl_resizing(htbl);
            if(err == ERROR)
                return ERROR;
        }
        ~~~  
        
- 학생 정보 **정렬/출력** (**sorting**) = **Quick Sort**  

    - Hash table을 탐색하여 학생 정보가 저장되어 있는 slot들을 배열로 따로 저장하여 Quick sort 후 출력

# Reference
[Makefile](https://modoocode.com/311)  
[Hash Function](http://sweeper.egloos.com/925740)

