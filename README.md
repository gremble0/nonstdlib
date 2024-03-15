# nonstdlib
This project consists of several modules containing various useful utilities for C such as stacks, hashtables, lists and arrays.

## Note on portability
Because this project is mostly for fun I have not put any significant effort into maintaining portability to other platforms or compilers. The only way i can guarantee the library to work is to run it on linux with the clang compiler.

## Usage
To use the library copy it into your project however you want (as a git submodule or cloning directly). Then go into nonstdlib/src and run make:
```sh
git clone git@github.com:gremble0/nonstdlib.git
cd nonstdlib/src
make
```
Now the static library `libnonstdlib.a` will be generated inside nonstdlib/src. Now you can link with the static library and include the headers in your project.

## Example
Consider this simple file structure:
```
.
├─nonstdlib/
│ ├─...
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
clang main.c -L../nonstdlib/src -I../nonstdlib/src -lnonstdlib
```

And then use it in main.c like this (this should print "nonstdlib" to stdout):
```c
#include <stdio.h>
#include "hashtable.h"

int main(void) {
    ht_t *table = ht_init(5);
    ht_put(table, "yo", "nonstdlib");

    printf("%s\n", (char*)ht_get(table, "yo"));
    
    return 0;
}
```

## Modules:
List of currently implemented modules:
- `hashtable.h` and `generic_hashtable.h`: Type and functions for the hashtable data structure.
- `error.h`: Contains some functions for handling typical errors and printing more useful debug information. Also has a custom assert macro that uses nonstdlib's error handling on error
- `linked_list.h`: Type and functions for the linked list data structure.
- `list.h` (WIP): Type and functions for the list data structure.
- `array.h`: Utilities for normal C arrays.
- `sort.h`: Some sorting algorithms for builtin C arrays.
