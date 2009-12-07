CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -g
LDFLAGS=
EXEC=mm
OBJDIR=obj
SRCDIR=src
LIBDIR=lib

LIBNAME=libmm

ifdef DEBUG
CFLAGS+= -g
endif

ifdef DYNAMIC
CFLAGS+= -fPIC
endif

INCLUDES=-I./include
SOURCES=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SOURCES))

all: before $(EXEC) lib

before:
	@echo Objects: $(OBJ)
	
ifdef DYNAMIC
lib: dynlib
else
lib: staticlib
endif
	
after:
	
staticlib: $(OBJ)
	@echo '###### Making Static library ######'
	ar rcs $(LIBDIR)/$(LIBNAME).a $(OBJ)
	
dynlib:
	@echo '###### Making Dynamic library ######'
	$(CC) -shared -Wl,-soname,$(LIBNAME).so.1 -o $(LIBDIR)/$(LIBNAME).so.1.0.1  $(OBJ)
	
	
clean:
	rm -f obj/*.o
	rm -f $(EXEC).exe
	rm -f $(LIBDIR)/*

# no tuning after that

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) main.c $(OBJ) $(INCLUDES)

.PHONY: before $(EXEC) after staticlib dynlib lib

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES)