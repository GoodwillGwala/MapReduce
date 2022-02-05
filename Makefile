CC = g++
CFLAGS =  -std=c++17 -static-libstdc++
THREAD_LIB = -lpthread




INC_DIR = include
SRC_DIR = src



PROGS =  main


all: $(PROGS)


main: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) $^ -o $@.out $(THREAD_LIB) -I$(INC_DIR)

clean:
	rm  -f *.o *.out $(PROGS)
