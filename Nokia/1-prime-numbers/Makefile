LIBINC = -L/usr/local/lib -L/usr/lib -L $(HOME)/lib
INC = -I/usr/include/ $(LIBINC)
LIB = -lgtest

all:
	g++ -pthread $(INC) primeNumbers.cpp main.cpp -o primeNumbers $(LIB)
