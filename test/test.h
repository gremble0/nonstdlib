#define TEST_MODULE_START(module) printf("Testing module: " module "\n")

#define TEST_MODULE_SUCCESS(module)                                            \
  printf("\033[0;32mAll tests under module " module                            \
         " were successful\033[0;37m\n")

#define ASSERT_TRUE(expr)                                                      \
  if (!(expr)) {                                                               \
    TEST_FUNCTION_FAILURE()                                                    \
  }

#define TEST_FUNCTION_SUCCESS(test)                                            \
  printf("\033[0;32mTest successful for " test "\033[0;37m\n");

#define TEST_FUNCTION_FAILURE(test)                                            \
  printf("\033[0;31mTest failed for " test "\033[0;37m\n");                    \
  return

// void test_function_success(char *test) {
//   printf("\033[0;32mTest successful for %s\033[0;37m\n", test);
// }
