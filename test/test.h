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

#define TEST_MODULE_START(module)                                              \
  printf("\033[1mTesting module '%s'\033[0;37m\n", module)
#define TEST_MODULE_END(module)                                                \
  printf("\033[0;32mTest successful for module '%s' \033[0;37m\n", module)

void test_all_sorts();
void test_arr();
void test_hashtable();
void test_hashtable_generic();
void test_linked_list();
void test_list();
void test_string();
