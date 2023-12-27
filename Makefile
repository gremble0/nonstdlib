CC=clang
CFLAGS=-Wall -Wextra
OBJS=hashtable.o stack.o sort.o

all: clean $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) test.c -o test 

hashtable.o:
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o

stack.o:
	$(CC) $(CFLAGS) -c stack.c -o stack.o

quicksort.o:
	$(CC) $(CFLAGS) -c sort.c -o sort.o

clean:
	rm -f *.o
	rm -f test
