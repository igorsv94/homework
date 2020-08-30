CC = gcc
FLAGS = -std=c99
LIBINC = -L./binaryLib/bin
INC = -I ./binaryLib/include $(LIBINC)
LIB = -lbinary 

all: lib test

lib:
	cd binaryLib/ && make

test:
	$(CC) $(FLAGS) $(INC) test.c -o runTest $(LIB)

clean:
	cd binaryLib/ && make clean
	rm *.o runTest
