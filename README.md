# nonstdlib
This project consists of several modules containing various useful utilities for C such as stacks, hashtables, lists and arrays.

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
- `hashtable.h` and `generic_hashtable.h`
- `array.h`
- `sort.h`
- `linked_list.h`
- `list.h` (WIP)
