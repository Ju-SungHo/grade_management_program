CROSS=
CC=$(CROSS)gcc 

# C Compiler options
CFLAGS= -Wall

# Linker Options
LDFLAGS=

# Include Files Path
INCLUDE=-Iinclude/

# Source Files Directory
SRC_DIR=./src

# Object Files Directory
OBJ_DIR=./obj

# Executeable File name
TARGET=main

# Source and Object files to make
SRCS=$(notdir $(wildcard $(SRC_DIR)/*.c))
OBJS=$(SRCS:.c=.o)

# $(OBJ_DIR)/$(OBJS)
OBJECTS=$(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))
DEPS=$(OBJECTS:.o=.d)

all : $(TARGET)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -MD $(LDFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)


clean :
	rm -r $(OBJECTS) $(DEPS) $(TARGET)

-include $(DEPS)
