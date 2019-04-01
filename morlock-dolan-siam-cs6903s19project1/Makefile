CFLAGS=-Wall -g
# LIBS=-lpthread -lrt -lm
LIBS=-lm

all: build

build: clean client

client: clean morlock-dolan-siam-decrypt

# Common files

morlock-dolan-siam-decrypt:
	gcc -o morlock-dolan-siam-decrypt morlock-dolan-siam-source.c ${LIBS}

clean:
	rm -f morlock-dolan-siam-decrypt