CC=clang
CFLAGS=-Wall -Wextra
SRC=../src

all: src
	$(CC) $(CFLAGS) -I$(SRC) test.c -L$(SRC) -l:nonstdlib.a -o test 

src:
	cd $(SRC) && $(MAKE)
