IDIR=./include
TARGET=bin/main

CC=gcc
CFLAGS=-I./include `sdl2-config --cflags` -g
LDFLAGS=`sdl2-config --libs`

DEPS=$(wildcard $(IDIR)/*.h)
SRCS=$(wildcard src/*.c)
OBJS=$(patsubst src/%.c, build/%.o, $(SRCS))


.PHONY: all clean

all: $(TARGET)

build/%.o: src/%.c $(DEPS)
	mkdir -p build
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	mkdir -p bin
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -rf build bin

