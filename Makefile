CFLAGS = -Wall
LFLAGS = -l:libm.so -lGL -lpthread -ldl -lrt -lX11
LIBS = -l:libraylib.a

all: main.c
	# Linking object file before static libraries
	clang $(CFLAGS) main.c $(LIBS) $(LFLAGS) -o main

run: all
	./main
