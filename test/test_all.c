#include <stdio.h>

#include "test.h"

int main(void) {
  static int total_tests_passed = 0;
  static int total_tests_ran = 0;

  printf("------------------------------------------\n");
  test_arr(&total_tests_ran, &total_tests_passed);
  printf("------------------------------------------\n");
  test_hashtable(&total_tests_ran, &total_tests_passed);
  printf("------------------------------------------\n");
  test_list(&total_tests_ran, &total_tests_passed);
  printf("------------------------------------------\n");
  test_all_sorts(&total_tests_ran, &total_tests_passed);
  printf("------------------------------------------\n");
  test_linked_list(&total_tests_ran, &total_tests_passed);
  printf("------------------------------------------\n");

  // DEPRECATED:
  // test_hashtable_generic(&total_tests_ran, &total_tests_passed);
  // printf("------------------------------------------\n");

  if (total_tests_passed == total_tests_ran) {
    printf("\033[0;32m%d/%d tests successful\033[0;37m\n", total_tests_passed,
           total_tests_ran);
  } else {
    printf("\033[0;31m%d/%d tests successful\033[0;37m\n", total_tests_passed,
           total_tests_ran);
  }
}
