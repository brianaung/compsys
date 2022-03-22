# define C compilers and flags
CC = gcc
CFLAGS = -Wall -g

# resource files
OBJ = detect.o

detect: $(OBJ) Makefile
	$(CC) $(CFLAGS) -o detect $(OBJ)

clean: 
	rm -f $(OBJ) detect *.o
