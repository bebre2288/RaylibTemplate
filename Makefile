CFLAGS=-Wall -Wextra -Werror -pedantic -O2 -ggdb
CLIBS=`pkg-config --libs raylib` -lm -lGL -lpthread -ldl -lrt -lX11 -lcurl
CC=clang

OUTNAME=run

all: build

build:
	$(CC) $(CFLAGS) main.c -o run $(CLIBS)

windows:
	x86_64-w64-mingw32-gcc -I/home/user/git/curl/include -I/home/user/git/raylib/build/raylib/include/ main.c -o run -L/home/user/git/curl/include -L/home/user/git/raylib/build/raylib/include/ -lcurl -lraylib -static -lm -lopengl32 -lwinmm

run: build
	./$(OUTNAME)

clean:
	rm ./$(OUTNAME)
