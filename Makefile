CC = gcc
CFLAGS = -g -Wpedantic
LIBS = -lm -lpthread
DEFINES = -DDEBUG

objs = ./build/debug/raw_term.o ./build/debug/clock.o ./build/debug/common.o
main = src/main.c

raw_term_debug: ./build/debug/raw_term

clean:
	rm -rf ./build/debug/*
	rm -rf ./build/release/*

./build/debug/%.o: ./src/%.c
	gcc -c $< $(LIBS) $(DEFINES) $(CFLAGS) -o $@

./build/debug/raw_term: $(objs) $(main)
	gcc $^ $(LIBS) $(DEFINES) $(CFLAGS) -o $@

