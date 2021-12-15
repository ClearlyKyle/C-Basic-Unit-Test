#include "unit_test.h"

#define RED "\e[31m"
#define GREEN "\e[32m"
#define YELLOW "\e[33m"
#define WHITE "\e[1m"
#define END_COL "\e[m"

static struct __function_list
{
    int _line;
    char *__function_name;
    struct __function_list *_next;
    void (*f)(void);
} *__list_head = NULL;

static char *__global_message = NULL;
static int __global_test_count = 0;
static int __global_pass_test_count = 0;
static int __global_fail_test_count = 0;

/* add f to the linked list... */
void globals_list_add(void (*f)(void), char *func_name, int line)
{
    struct __function_list *link = (struct __function_list *)malloc(sizeof(struct __function_list));
    link->_line = line;
    link->__function_name = func_name;
    link->f = f;
    link->_next = __list_head;
    __list_head = link;
    __global_test_count++;
}

void global_run_all_tests(void)
{
    fprintf(stderr, YELLOW "[TESTING] Testing %d function%s\n" END_COL, __global_test_count, __global_test_count > 1 ? "s" : " ");
    struct __function_list *cur;
    for (cur = __list_head; cur; cur = cur->_next)
    {
        __global_message = NULL;
        cur->f();
        if (__global_message != 0)
        {
            // fprintf(stderr, RED "----- FAIL" END_COL ": %s(%d)\n", cur->__function_name, cur->_line);
            // fprintf(stderr, "\t%s\n", __global_message);
        }
        else
        {
            __global_pass_test_count++;
            fprintf(stderr, GREEN "PASS -----" END_COL ": %s(%d)\n", cur->__function_name, cur->_line);
        }
    }

    fprintf(stderr, "----------:\n%d " GREEN "PASSED" END_COL ", %d " RED "FAILED\n" END_COL, __global_pass_test_count, __global_fail_test_count);
}

void set_fail_message(char *msg, const char *func_name, int line)
{
    if (__global_message == NULL)
    {
        __global_message = msg;
        __global_fail_test_count++;
        fprintf(stderr, RED "----- FAIL" END_COL ": %s(%d)\n", func_name, line);
    }
    fprintf(stderr, "\t(%d) -> %s\n", line, msg);
}

#define print_generic(message, X) _Generic((X), float      \
                                           : print_double, \
                                             double        \
                                           : print_double, \
                                             default       \
                                           : print_int)(message, X)

void print_int(const char *msg, int x);
void print_double(const char *msg, double x);

void print_int(const char *msg, int x)
{
    fprintf(stderr, "%s : %d\n", msg, x);
}

void print_double(const char *msg, double x)
{
    fprintf(stderr, "%s : %f\n", msg, x);
}