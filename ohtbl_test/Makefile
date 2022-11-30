CC = gcc
CXXFLAGS = -Wall
OBJS = ohtable.o main.o 
EXE=oht_test

%.o: %.c
	$(CC) $(CXXFLAGS) -c $<

$(EXE) : $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(EXE)

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE)

-include $(OBJS:.o=.d)