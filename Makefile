CC=clang
CFLAGS=-Wall -Wextra
OBJS=hashtable.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) test.c -o test 

hashtable.o:
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o

clean:
	rm -f *.o
	rm -f test
