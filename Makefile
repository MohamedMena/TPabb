CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror

HEADERS = testing.h abb.h
CFILES = abb.c main.c testing.c pruebas_alumno.c
OBJECTS = testing.o abb.o
ZIPFILES =  lista.c pruebas_alumno.c

EXEC = abb
FILENAME = $(EXEC)_$(shell date +%Y%m%d).zip

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2

build: $(HEADERS) $(CFILES)
	$(CC) $(CFLAGS) $(CFILES) -o $(EXEC) 

run: build
	./$(EXEC)

all: build
	valgrind $(VFLAGS) ./$(EXEC)

zipp: 
	zip $(FILENAME) $(ZIPFILES)
	
clean: 
	rm -f *.o $(EXEC) $(FILENAME)
