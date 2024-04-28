#include <stdio.h>

#include "test.h"

int main(void) {
  printf("------------------------------------------\n");
  test_all_sorts();
  printf("------------------------------------------\n");
  test_arr();
  printf("------------------------------------------\n");
  test_hashtable();
  printf("------------------------------------------\n");
  test_linked_list();
  printf("------------------------------------------\n");
  test_list();
  printf("------------------------------------------\n");
  test_string();
  printf("------------------------------------------\n");

  printf("\033[0;32mAll tests passed :)\033[0;37m\n");
}
