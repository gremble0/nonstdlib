// TODO: make this a part of the libarary?

#define TEST_MODULE_START() printf("Testing module: %s\n", __FILE__)

#define TEST_MODULE_END()                                                      \
  if (tests_passed != tests_ran) {                                             \
    printf("\033[0;31m%d/%d tests successful for %s\033[0;37m\n",              \
           tests_passed, tests_ran, __FILE__);                                 \
  } else {                                                                     \
    printf("\033[0;32m%d/%d tests successful for %s\033[0;37m\n",              \
           tests_passed, tests_ran, __FILE__);                                 \
  }

#define ASSERT_TRUE(expr)                                                      \
  if (!(expr)) {                                                               \
    TEST_FUNCTION_FAILURE();                                                   \
  }

#define TEST_FUNCTION_SUCCESS()                                                \
  ++tests_passed;                                                              \
  ++tests_ran;                                                                 \
  printf("\033[0;32mTest successful for %s \033[0;37m\n", __func__);

#define TEST_FUNCTION_FAILURE()                                                \
  ++tests_ran;                                                                 \
  printf("\033[0;31mTest failed for %s \033[0;37m\n", __func__);               \
  goto defer

void test_arr(void);
void test_hashtable(void);
void test_hashtable_generic(void);
void test_linked_list(void);
void test_list(void);
void test_all_sorts(void);
