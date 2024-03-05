CC=clang
CFLAGS=-Wall -Wextra -g -O0
SRC=../src
OBJS=test_array.o test_hashtable.o test_hashtable_generic.o test_linked_list.o test_list.o test_sort.o

all: clean src $(OBJS)
	$(CC) $(CFLAGS) -o test_all $(OBJS) test_all.c -L$(SRC) -lnonstdlib

%.o: %.c
	$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

src:
	$(MAKE) -C $(SRC) debug

clean:
	rm test_all *.o -f
