CC=clang++
CFLAGS=-std=c++20 -Wall -Wextra -Wpedantic -O3 $(shell pkg-config --cflags libnotifymm-1.0)
LDFLAGS=$(shell pkg-config --libs libnotifymm-1.0)
FILES=main.cpp
OUT=batgirl

all: build strip

build:
	$(CC) -o $(OUT) $(CFLAGS) $(LDFLAGS) $(FILES)

strip:
	strip --strip-all $(OUT)

install:
	cp $(OUT) /usr/local/bin -v

uninstall:
	rm /usr/local/bin/$(OUT) -v

clean:
	rm $(OUT)
