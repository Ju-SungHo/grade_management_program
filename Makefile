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
