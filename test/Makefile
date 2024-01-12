CC=clang
CFLAGS=-Wall -Wextra
SRC=../src

all: src
	$(CC) $(CFLAGS) -I$(SRC) test_all.c -L$(SRC) -lnonstdlib -o test_all

src:
	cd $(SRC) && $(MAKE) clean && $(MAKE)

clean:
	rm test_all -f
