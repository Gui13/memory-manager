CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -g
LDFLAGS=
EXEC=mm
OBJDIR=obj
SRCDIR=src

ifdef DEBUG
CFLAGS+= -g
endif

INCLUDES=-I./include
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: before $(EXEC)

before:
	@echo Objects: $(OBJ)
	
clean:
	rm -f obj/*.o
	rm -f $(EXEC).exe

# no tuning after that

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) main.c $(OBJ) $(INCLUDES)

.PHONY: before $(EXEC) 

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)