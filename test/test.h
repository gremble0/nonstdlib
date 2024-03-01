#define TEST_MODULE_START(module) printf("Testing module: " module "\n")

#define TEST_MODULE_END(module)                                                \
  if (tests_passed != tests_ran) {                                             \
    printf("\033[0;31m%d/%d tests successful for " module "\033[0;37m\n",      \
           tests_passed, tests_ran);                                           \
  } else {                                                                     \
    printf("\033[0;32m%d/%d tests successful for " module "\033[0;37m\n",      \
           tests_passed, tests_ran);                                           \
  }

#define ASSERT_TRUE(expr)                                                      \
  if (!(expr)) {                                                               \
    TEST_FUNCTION_FAILURE()                                                    \
  }

#define TEST_FUNCTION_SUCCESS(test)                                            \
  ++tests_passed;                                                              \
  ++tests_ran;                                                                 \
  printf("\033[0;32mTest successful for " test "\033[0;37m\n");

#define TEST_FUNCTION_FAILURE(test)                                            \
  printf("\033[0;31mTest failed for " test "\033[0;37m\n");                    \
  return

void test_arr(void);
void test_hashtable(void);
void test_hashtable_generic(void);
void test_linked_list(void);
void test_list(void);
void test_all_sorts(void);
