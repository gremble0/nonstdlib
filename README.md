# nonstdlib
This project consists of several modules containing various useful utilities for C such as stacks, hashtables, a nicer version of strings, lists/dynamic arrays and arrays.

## Note on portability
Because this project is mostly for fun I have not put any significant effort into maintaining portability to other platforms or compilers. Even though there shouldn't be anything major that is platform/compiler specific, the only way i can guarantee the library to work is to run it on linux with the clang compiler.

## Usage
**If you want to use this library I would not recommend regularly updating it as I regularly push breaking changes**. To use the library copy it into your project however you want (as a git submodule or cloning directly). Then go into nonstdlib/src and run make:
```sh
git clone git@github.com:gremble0/nonstdlib.git
cd nonstdlib/src
make # or `make debug` if you want to keep debug symbols
```
Now the static library `libnonstdlib.a` will be generated inside nonstdlib/src. You can link with the static library and include the headers in your project. All the modules in nonstdlib are prefixed with `n`, see [Modules](#modules) for a full list of modules in the library.

## Example
Consider this simple file structure:
```
.
├─nonstdlib/
│ ├─include/
│ │ └─...
│ └─src/
│   └─...
└─src/
  └─main.c
```

Now we can link with nonstdlib like this:
```sh
cd nonstdlib/src
make

cd ../../src
cc main.c -L../nonstdlib/src -I../nonstdlib/include -lnonstdlib
```

To test that the library works you can copy this and verify that it compiles and that the assertions pass:
```c
#include <stdio.h>
#include <string.h>

#include "nonstdlib/nerror.h"
#include "nonstdlib/nhashtable.h"
#include "nonstdlib/nlist.h"
#include "nonstdlib/nstring.h"

int main(void) {
  // Small hashtable demo
  ht_t *table = ht_init(8);
  ht_put(table, &string_of("key"), &string_of("value"));

  const string_t *result = ht_get(table, &string_of("key"));
  ASSERT(result != NULL);
  ASSERT(string_compare(&string_of("value"), result) == 0);

  // Small list demo
  typedef struct {
    int x;
    char *s;
  } list_element;

  list_t *list = list_init(8);
  list_push_back(list, &(list_element){.x = 10, .s = "my list element"});

  const list_element *popped = list_pop_front(list);
  ASSERT(popped != NULL);
  ASSERT(popped->x == 10);
  ASSERT(strcmp(popped->s, "my list element") == 0);

  ht_free(table);
  list_free(list);

  printf("All assertions passed, library is working as expected :)\n");
}
```

## Modules
List of currently implemented modules:
- `narena.h`: An implementation of an arena allocator that simplifies memory management by grouping allocations into larger blocks instead of multiple smaller allocations with a convenient free function for freeing the entire block at once.
- `nhashtable.h`: An implementation of the hashtable datastructure - associate a key with some given value with. O(1) insertion complexity, O(1) lookup complexity.
- `nerror.h`: Contains some functions for handling typical errors and printing more useful debug information. Also has a custom assert macro that uses nonstdlib's error handling on error
- `nlinked_list.h`: An implementation of the linked list datastructure - specifically a doubly ended linked list. O(1) insertion complexity, O(n) lookup complexity.
- `nlist.h`: An implementation of the dynamic array datastructure - something akin to ArrayLists in java or lists in python. O(1) insertion complexity, O(1) lookup complexity.
- `narray.h`: Some handy utilities for managing builtin C arrays.
- `nstring.h`: Simple string interface that saves the length of strings instead of relying on nullbytes, as well as some handy utilities for managing strings.
- `nsort.h`: Some sorting algorithms for builtin C arrays.
