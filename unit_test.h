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

//#define TEST_ASSERT_EQUAL(message, expected, actual)                            \
//    do                                                                     \
//    {                                                                      \
//        if (!((expected) == (actual)))                                     \
//        {                                                                  \
//            fprintf(stderr, "\t[FAILED] %s\n%s\n", __FUNCTION__, message); \
//            print_generic("\t\texpected : ", expected);                    \
//            print_generic("\t\tactual   : ", actual);                      \
//            __global_message = message;                                    \
//        }                                                                  \
//    } while (0)

#endif // __UNIT_TEST_H__