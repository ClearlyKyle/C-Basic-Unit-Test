#### Basic Example

```C
ADD_FUNCTION(TestEquals)
{
    TEST_ASSERT_TRUE("Testing equality", 1 == 1);
    TEST_ASSERT_FALSE("Testing equality", 1 == 2);
}

RUN_ALL_TESTS();
```

* `TestEquals` gives a name to the test code being run
* `RUN_ALL_TEST()` will run all functions created with `ADD_FUNCTION`

Test functions

* `TEST_ASSERT_TRUE`
* `TEST_ASSERT_FALSE`
* `TEST_EQUAL_INT`
* `TEST_EQUAL_FLOAT`
* `TEST_EQUAL_UINT`
* `TEST_EQUAL_CHAR`