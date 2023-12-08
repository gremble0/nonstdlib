CC=clang
CFLAGS=-Wall -Wextra
OBJS=hashmap.o

all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) test.c -o test 

hashmap.o:
	$(CC) $(CFLAGS) -c hashmap.c -o hashmap.o

clean:
	rm -f *.o
	rm -f test
