CC = gcc
CFLAGS = -Wall 
GLUTFLAGS = -lGL -lGLU -lglut -lm
EXEC = checkers
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)


all: $(EXEC)


checkers:	$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(GLUTFLAGS)


%.o: %.c 
	$(CC) -o $@ -c $^ $(CFLAGS)


clear:	
		rm *.o *~ core -rf $(EXEC)


zip:
	tar -zcvf checkers.tar.gz fonctions.c main.c display.c checkers.h makefile
