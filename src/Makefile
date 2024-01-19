CC=clang
CFLAGS=-Wall -Wextra
OBJS=hashtable.o linked_list.o sort.o array.o list.o
LIB=libnonstdlib.a

all: $(OBJS)
	ar rcs $(LIB) $(OBJS)

hashtable.o:
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o

linked_list.o:
	$(CC) $(CFLAGS) -c linked_list.c -o linked_list.o

quicksort.o:
	$(CC) $(CFLAGS) -c sort.c -o sort.o

array.o:
	$(CC) $(CFLAGS) -c array.c -o array.o

list.o:
	$(CC) $(CFLAGS) -c list.c -o list.o

clean:
	rm -f *.o
	rm -f *.a
	rm -f test
