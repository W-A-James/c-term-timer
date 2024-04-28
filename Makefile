CC = gcc
CFLAGS = -g -Wpedantic -Wall -Werror
RELEASE_CFLAGS = -Wpedantic -Wall -Werror -O3
LIBS = -lm -lpthread
DEnINES = -DDEBUG

objs = ./build/debug/raw_term.o ./build/debug/clock.o ./build/debug/common.o ./build/debug/duration-parser.o

release_objs = ./build/release/raw_term.o ./build/release/clock.o ./build/release/common.o ./build/release/duration-parser.o

main = src/main.c

all: raw_term_debug raw_term_release

raw_term_debug: ./build/debug/raw_term

raw_term_release: ./build/release/raw_term

clean:
	rm -rf ./build

./build/debug/%.o: ./src/%.c ./build/debug/
	gcc -c $< $(LIBS) $(DEFINES) $(CFLAGS) -o $@

./build/debug/raw_term: $(objs) $(main)
	gcc $^ $(LIBS) $(DEFINES) $(CFLAGS) -o $@

./build/release/%.o: ./src/%.c ./build/release/
	gcc -c $< $(LIBS) $(RELEASE_CFLAGS) -o $@

./build/release/raw_term: $(release_objs) $(main)
	gcc $^ $(LIBS) $(RELEASE_CFLAGS) -o $@

build/debug/:
	mkdir -p ./build/debug

build/release/:
	mkdir -p ./build/release
