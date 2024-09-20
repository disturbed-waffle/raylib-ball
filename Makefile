CFLAGS = -Wall
LFLAGS = -l:libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11

all: main.c
	gcc $(CFLAGS) main.c $(LFLAGS) -o main


run: all
	./main
