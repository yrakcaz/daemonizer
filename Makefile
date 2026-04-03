BIN=daemonizer
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c99 -pedantic -Iinclude/
SRC=src/helper.c src/manage.c src/daemonize.c src/main.c
OBJ=$(SRC:.c=.o)
TAR=yrakcaz-$(BIN)
PREFIX=/usr/local

-include makefile.rules

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	$(RM) $(OBJ) $(BIN) $(TAR).tar.bz2

distclean: clean
	$(RM) makefile.rules

export:
	git archive HEAD --prefix=$(TAR)/ | bzip2 > $(TAR).tar.bz2

install:
	cp $(BIN) $(PREFIX)/bin

uninstall:
	$(RM) $(PREFIX)/bin/$(BIN)


.PHONY: all clean distclean export install uninstall
