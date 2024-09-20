CFLAGS = -Wall
LFLAGS = -l:libraylib.a -lm -lGL -lpthread -ldl -lrt -lX11

all: main.c
	gcc $(CFLAGS) main.c $(LIBS) $(LFLAGS) -o main

run: all
	./main
