.PHONY: all
.PHONY: clean

CC := gcc
CFLAGS := -O3 -Wall -Wextra -std=c99 -pedantic
LDFLAGS := --print-memory-usage
BIN = i8080
DEBUG_BIN = i8080_debug

# -fsanitize=address,undefined 

SRCDIR = $(wildcard *.c) 

# All .c files converted to .o 

OBJS = $(SRCDIR:.c=.o)

all: $(OBJS)
	$(CC) -o $(BIN) $(OBJS) 

%: %.c 
	$(CC) $(CFLAGS)  "$<" -c "$@"

clean: all
	rm -rvf $(OBJS) $(BIN) $(DEBUG_BIN) *.gch
