CC=clang
CFLAGS=-Wall -Wextra
DEBUG_FLAGS=$(CFLAGS) -g -O0
OBJS=hashtable.o linked_list.o sort.o array.o list.o error.o
DEBUG_OBJS=$(OBJS:.o=_debug.o)
LIB=libnonstdlib.a

all: $(OBJS)
	ar rcs $(LIB) $(OBJS)

debug: clean $(DEBUG_OBJS)
	ar rcs $(LIB) $(DEBUG_OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%_debug.o: %.c
	$(CC) $(DEBUG_FLAGS) -c $< -o $@

clean:
	rm -f *.o
	rm -f *.a
	rm -f test
