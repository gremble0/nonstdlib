# nonstdlib
This project consists of several modules containing various useful utilities for C such as stacks, hashtables, lists and arrays.

## Note on portability
Because this project is mostly for fun I have not put any significant effort into maintaining portability to other platforms or compilers. Even though there shouldn't be anything major that is platform/compiler specific, the only way i can guarantee the library to work is to run it on linux with the clang compiler.

## Usage
To use the library copy it into your project however you want (as a git submodule or cloning directly). Then go into nonstdlib/src and run make:
```sh
git clone git@github.com:gremble0/nonstdlib.git
cd nonstdlib/src
make
```
Now the static library `libnonstdlib.a` will be generated inside nonstdlib/src. You can link with the static library and include the headers in your project. All the modules in nonstdlib are prefixed with `n`, see [Modules](#modules) for more details about all the library's features.

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
#include "nhashtable.h"

int main(void) {
    ht_t *table = ht_init(5);
    ht_put(table, "yo", "nonstdlib");

    printf("%s\n", (char*)ht_get(table, "yo"));
    
    return 0;
}
```

## Modules
List of currently implemented modules:
- `nhashtable.h` and `ngeneric_hashtable.h`: Type and functions for the hashtable data structure.
- `nerror.h`: Contains some functions for handling typical errors and printing more useful debug information. Also has a custom assert macro that uses nonstdlib's error handling on error
- `nlinked_list.h`: Type and functions for the linked list data structure.
- `nlist.h` (WIP): Type and functions for the list data structure.
- `narray.h`: Utilities for normal C arrays.
- `nsort.h`: Some sorting algorithms for builtin C arrays.
