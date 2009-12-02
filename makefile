

OPTS=-DDEBUG
APPNAME=mm

.phony: all

all: main

main: main.c 
	gcc -o $(APPNAME) main.c obj/memory_manager.o obj/bstree.o


%o: %c %h
	gcc $(OPTS) -c -o obj/$@ $<