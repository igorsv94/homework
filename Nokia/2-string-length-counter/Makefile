LIBINC = -L/usr/local/lib -L/usr/lib -L $(HOME)/lib
INC = -I/usr/include/ $(LIBINC)
LIB = -lgtest

all:
	g++ -std=c++17 -pthread $(INC) stringcounter.cpp main.cpp -o lenghtCounter $(LIB)
