#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <stdio.h>
#include <stdlib.h>

void globals_list_add(void (*f)(void), char *func_name, int line);
void global_run_all_tests(void);
void set_fail_message(char *msg, const char *func_name, int line);

#define ADD_FUNCTION(f)                                            \
    static void f(void);                                           \
    static void __attribute__((constructor)) __construct_##f(void) \
    {                                                              \
        globals_list_add(f, #f, __LINE__);                         \
    }                                                              \
    static void f(void)

#define RUN_ALL_TESTS()                    \
    int main(int argc, char const *argv[]) \
    {                                      \
        global_run_all_tests();            \
        return 0;                          \
    }

#define TEST_ASSERT_TRUE(message, test)                        \
    do                                                         \
    {                                                          \
        if (!(test))                                           \
        {                                                      \
            set_fail_message(message, __FUNCTION__, __LINE__); \
        }                                                      \
    } while (0)

#define TEST_ASSERT_FALSE(message, test)                       \
    do                                                         \
    {                                                          \
        if ((test))                                            \
        {                                                      \
            set_fail_message(message, __FUNCTION__, __LINE__); \
        }                                                      \
    } while (0)

#define __TEST_EQUALITY(message, op, expected, actual, func, line)                                                       \
    do                                                                                                                   \
    {                                                                                                                    \
        if ((expected) != (actual))                                                                                      \
        {                                                                                                                \
            set_fail_message(message, func, line);                                                                       \
            fprintf(stderr, "\t\texpected %s = " op "\n\t\tactual %s = " op "\n", #expected, expected, #actual, actual); \
        }                                                                                                                \
    } while (0)

#define TEST_EQUAL_INT(expected, actual, message) __TEST_EQUALITY(message, "%d", expected, actual, __FUNCTION__, __LINE__)
#define TEST_EQUAL_FLOAT(expected, actual, message) __TEST_EQUALITY(message, "%f", expected, actual, __FUNCTION__, __LINE__)
#define TEST_EQUAL_UINT(expected, actual, message) __TEST_EQUALITY(message, "%d", expected, actual, __FUNCTION__, __LINE__)
#define TEST_EQUAL_CHAR(expected, actual, message) __TEST_EQUALITY(message, "%c", expected, actual, __FUNCTION__, __LINE__)

#endif // __UNIT_TEST_H__