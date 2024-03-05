CC=clang
CFLAGS=-Wall -Wextra
DEBUG_FLAGS=$(CFLAGS) -g -O0
OBJS=hashtable.o linked_list.o sort.o array.o list.o error.o
DEBUG_OBJS=hashtable_debug.o linked_list_debug.o sort_debug.o array_debug.o list_debug.o error_debug.o
LIB=libnonstdlib.a

all: $(OBJS)
	ar rcs $(LIB) $(OBJS)

debug: clean $(DEBUG_OBJS)
	ar rcs $(LIB) $(DEBUG_OBJS)

hashtable.o:
	$(CC) $(CFLAGS) -c hashtable.c -o hashtable.o

linked_list.o:
	$(CC) $(CFLAGS) -c linked_list.c -o linked_list.o

sort.o:
	$(CC) $(CFLAGS) -c sort.c -o sort.o

array.o:
	$(CC) $(CFLAGS) -c array.c -o array.o

list.o:
	$(CC) $(CFLAGS) -c list.c -o list.o

error.o:
	$(CC) $(CFLAGS) -c error.c -o error.o

hashtable_debug.o:
	$(CC) $(DEBUG_FLAGS) -c hashtable.c -o hashtable_debug.o

linked_list_debug.o:
	$(CC) $(DEBUG_FLAGS) -c linked_list.c -o linked_list_debug.o

sort_debug.o:
	$(CC) $(DEBUG_FLAGS) -c sort.c -o sort_debug.o

array_debug.o:
	$(CC) $(DEBUG_FLAGS) -c array.c -o array_debug.o

list_debug.o:
	$(CC) $(DEBUG_FLAGS) -c list.c -o list_debug.o

error_debug.o:
	$(CC) $(DEBUG_FLAGS) -c error.c -o error_debug.o

clean:
	rm -f *.o
	rm -f *.a
	rm -f test
