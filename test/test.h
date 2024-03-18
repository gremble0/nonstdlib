// TODO: make this a part of the libarary?

// Assert something is true, if it's not print error message without crashing
#define ASSERT_TRUE(expr)                                                      \
  do {                                                                         \
    if (!(expr)) {                                                             \
      printf("\033[0;31mAssertion failed: %s, file %s, line "                  \
             "%d.\033[0;37m\n",                                                \
             #expr, __FILE__, __LINE__);                                       \
      TEST_FUNCTION_FAILURE();                                                 \
    }                                                                          \
  } while (0)

#define TEST_MODULE_START() printf("Testing module: %s\n", __FILE__)

// Print debug info about results for this test
#define TEST_MODULE_END()                                                      \
  do {                                                                         \
    if (tests_passed != tests_ran) {                                           \
      printf("\033[0;31m%d/%d tests successful for %s\033[0;37m\n",            \
             tests_passed, tests_ran, __FILE__);                               \
    } else {                                                                   \
      printf("\033[0;32m%d/%d tests successful for %s\033[0;37m\n",            \
             tests_passed, tests_ran, __FILE__);                               \
    }                                                                          \
  } while (0)

#define TEST_FUNCTION_SUCCESS(args...)                                         \
  ++tests_passed;                                                              \
  ++tests_ran;                                                                 \
  printf("\033[0;32mTest successful for %s \033[0;37m\n", __func__)

#define TEST_FUNCTION_FAILURE()                                                \
  ++tests_ran;                                                                 \
  printf("\033[0;31mTest failed for %s \033[0;37m\n", __func__);               \
  goto defer

void test_arr(int *total_tests_ran, int *total_tests_passed);
void test_hashtable(int *total_tests_ran, int *total_tests_passed);
void test_hashtable_generic(int *total_tests_ran, int *total_tests_passed);
void test_linked_list(int *total_tests_ran, int *total_tests_passed);
void test_list(int *total_tests_ran, int *total_tests_passed);
void test_all_sorts(int *total_tests_ran, int *total_tests_passed);
