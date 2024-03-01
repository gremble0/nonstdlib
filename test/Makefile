CC=clang
CFLAGS=-Wall -Wextra -g -O0
SRC=../src
OBJS=test_array.o test_hashtable.o test_hashtable_generic.o test_linked_list.o test_list.o test_sort.o

all: src $(OBJS)
	$(CC) $(CFLAGS) -o test_all $(OBJS) test_all.c -L$(SRC) -lnonstdlib

test_array.o:
	$(CC) $(CFLAGS) -I$(SRC) -c test_array.c -o test_array.o

test_hashtable.o:
	$(CC) $(CFLAGS) -I$(SRC) -c test_hashtable.c -o test_hashtable.o

test_hashtable_generic.o:
	$(CC) $(CFLAGS) -I$(SRC) -c test_hashtable_generic.c -o test_hashtable_generic.o

test_linked_list.o:
	$(CC) $(CFLAGS) -I$(SRC) -c test_linked_list.c -o test_linked_list.o

test_list.o:
	$(CC) $(CFLAGS) -I$(SRC) -c test_list.c -o test_list.o

test_sort.o:
	$(CC) $(CFLAGS) -I$(SRC) -c test_sort.c -o test_sort.o

src:
	$(MAKE) -C $(SRC) clean
	$(MAKE) -C $(SRC)

clean:
	rm test_all *.o -f
