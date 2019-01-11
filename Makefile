all: demo.c graphics/*.c graphics/*.h screen.c screen.h utils.c utils.h
	gcc -ansi -Wall demo.c screen.c utils.c graphics/*.c -o Dashboard
