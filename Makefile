CFLAGS = -Wall
LFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: main.c
	gcc $(CFLAGS) main.c $(LFLAGS) -o main


run: all
	./main

