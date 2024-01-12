CC=clang
CFLAGS=-Wall -Wextra
OBJS=hashtable.o stack.o sort.o array.o
LIB=libnonstdlib.a

all: $(OBJS)
	ar rcs $(LIB) $(OBJS)

hashtable.o:
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o

stack.o:
	$(CC) $(CFLAGS) -c stack.c -o stack.o

quicksort.o:
	$(CC) $(CFLAGS) -c sort.c -o sort.o

array.o:
	$(CC) $(CFLAGS) -c array.c -o array.o

clean:
	rm -f *.o
	rm -f *.a
	rm -f test
