CC = gcc
FLAGS = -std=c99
INC = -I ./include
BINDIR = ./bin

all:
	$(CC) $(FLAGS) $(INC) -c datatransfer.c -o $(BINDIR)/libbinary.a
#	$(CC) $(INC) -shared datatransfer.c -o $(BINDIR)/libbinary.so

clean:
	rm $(BINDIR)/*
