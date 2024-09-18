
#include <stdint.h>
#include "unit_test.h"

int8_t AverageThreeBytes(int8_t a, int8_t b, int8_t c)
{
    return (int8_t)(((int16_t)a + (int16_t)b + (int16_t)c) / 3);
}

ADD_FUNCTION(TestEquals)
{
    TEST_ASSERT_TRUE("Testing equality", 1 == 1);
    TEST_ASSERT_FALSE("Testing equality", 1 == 2);
}

ADD_FUNCTION(TestGreaterThan)
{
    TEST_ASSERT_TRUE("Testing equality", 5 > 4);
    TEST_ASSERT_TRUE("Testing equality", 7.8 > 6.3);
}

ADD_FUNCTION(TestLessThan)
{
    TEST_ASSERT_FALSE("Testing equality", 5 < 4);
    TEST_ASSERT_TRUE("Testing equality", 6.3 < 7.8);
}

ADD_FUNCTION(NotEqaulTo)
{
    TEST_ASSERT_TRUE("3 should not be equal to 3.0f", 3 == 3.0f);
    TEST_ASSERT_TRUE("5 should not be eqaul to 6", 5 != 6);
}

ADD_FUNCTION(test_AverageThreeBytes_should_AverageMidRangeValues)
{
    TEST_ASSERT_TRUE("Average should be 40", 40 == AverageThreeBytes(30, 40, 50));
    TEST_ASSERT_TRUE("Average should be 40", 40 == AverageThreeBytes(10, 70, 40));
    TEST_ASSERT_TRUE("Average should be 33", 33 == AverageThreeBytes(33, 33, 33));
}

ADD_FUNCTION(test_AverageThreeBytes_should_AverageHighValues)
{
    TEST_ASSERT_TRUE("Average should be 80", 81 == AverageThreeBytes(70, 80, 90));
    TEST_ASSERT_TRUE("Average should be 127", 127 == AverageThreeBytes(127, 127, 127));
    TEST_ASSERT_TRUE("Average should be 84", 85 == AverageThreeBytes(0, 126, 126));
}

ADD_FUNCTION(test_EqualityMacro)
{
    TEST_EQUAL_INT(10, 10, "This should be true");
    TEST_EQUAL_FLOAT(10.0f, 10.0, "This should be true");
    TEST_EQUAL_CHAR('c', 'c', "This should be true");
}

ADD_FUNCTION(test_EqualityHexValues)
{
    TEST_EQUAL_HEX(0x34, 52, "This should be true");
    TEST_EQUAL_HEX(0x34, 0x34, "This should be true");

    const uint16_t number1 = 0x563;

    TEST_EQUAL_HEX8(0x56, number1, "This should be true");
}

RUN_ALL_TESTS();