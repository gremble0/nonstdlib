SRC := ../src
INCLUDEDIR := ../include

CC := clang
CFLAGS := -Wall -Wextra -g -O0 -I../include/nonstdlib

OBJS := test_array.o test_hashtable.o test_linked_list.o test_list.o test_sort.o test_string.o
DEBUG_OBJS := $(OBJS:.o=_debug.o)

all: clean src_release $(OBJS)
	$(CC) $(CFLAGS) -o test_all $(OBJS) test_all.c -L$(SRC) -lnonstdlib

debug: clean src_debug $(DEBUG_OBJS)
	$(CC) $(CFLAGS) -o test_all $(DEBUG_OBJS) test_all.c -L$(SRC) -lnonstdlib

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDEDIR) -c $< -o $@

%_debug.o: %.c
	$(CC) $(DEBUG_FLAGS) -I$(INCLUDEDIR) -c $< -o $@

src_debug:
	$(MAKE) -C $(SRC) debug

src_release:
	$(MAKE) -C $(SRC) 

clean:
	rm test_all *.o -f
