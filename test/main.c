#include "ring.h"
#include <assert.h>
#include <stdio.h>

#define TEST_RING_SIZE 3
static bool test_ring_push_pop_32bit()
{
    ring_t ring;
    uint32_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    uint32_t test_value = 777777777;
    uint32_t pop_value;

    if (!ring_push(&ring, (uint8_t *)&test_value))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value))
    {
        return false;
    }

    return pop_value == test_value && ring_is_empty(&ring) == true;
}

static bool test_ring_push_pop_8bit()
{
    ring_t ring;
    uint8_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    uint8_t test_value = 77;
    uint8_t pop_value;

    if (!ring_push(&ring, (uint8_t *)&test_value))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value))
    {
        return false;
    }

    return pop_value == test_value && ring_is_empty(&ring) == true;
}

typedef struct
{
    int a;
    int b;
} test_ring_struct_t;
static bool test_ring_push_pop_struct()
{
    ring_t ring;
    test_ring_struct_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    test_ring_struct_t test_value = {77, 78};
    test_ring_struct_t pop_value;

    if (!ring_push(&ring, (uint8_t *)&test_value))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value))
    {
        return false;
    }

    return pop_value.a == test_value.a && pop_value.b == test_value.b && ring_is_empty(&ring) == true;
}

typedef void (*test_ring_func_fptr_t)(void);
static void test_ring_func()
{
    ;
}
static bool test_ring_push_pop_func()
{
    ring_t ring;
    test_ring_func_fptr_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    test_ring_func_fptr_t test_value = test_ring_func;
    test_ring_func_fptr_t pop_value;

    if (!ring_push(&ring, (uint8_t *)&test_value))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value))
    {
        return false;
    }

    return pop_value == test_value && ring_is_empty(&ring) == true;
}

static bool test_ring_push_push_pop_32bit()
{
    ring_t ring;
    uint32_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    uint32_t test_value = 777777777;
    uint32_t pop_value;

    if (!ring_push(&ring, (uint8_t *)&test_value))
    {
        return false;
    }

    if (!ring_push(&ring, (uint8_t *)&test_value))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value))
    {
        return false;
    }

    return pop_value == test_value && ring_is_empty(&ring) == false;
}

static bool test_ring_push_push_pop_pop_32bit()
{
    ring_t ring;
    uint32_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    uint32_t test_value_1 = 777777777;
    uint32_t test_value_2 = 777777778;
    uint32_t pop_value_1 = 0;
    uint32_t pop_value_2 = 0;

    if (!ring_push(&ring, (uint8_t *)&test_value_1))
    {
        return false;
    }

    if (!ring_push(&ring, (uint8_t *)&test_value_2))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value_1))
    {
        return false;
    }

    if (!ring_pop(&ring, (uint8_t *)&pop_value_2))
    {
        return false;
    }

    return pop_value_1 == test_value_1 && pop_value_2 == test_value_2 && ring_is_empty(&ring) == true;
}

static bool test_ring_empty_pop()
{
    ring_t ring;
    uint32_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    uint32_t pop_value;

    return ring_pop(&ring, (uint8_t *)&pop_value) == false && ring_is_empty(&ring) == true;
}

static bool test_ring_error_push_to_full()
{
    ring_t ring;
    uint32_t buf[TEST_RING_SIZE];
    ring_init(&ring, (uint8_t *)buf, TEST_RING_SIZE, sizeof(buf[0]));
    uint32_t test_value = 77;

    for (uint32_t i = 0; i < TEST_RING_SIZE; i++)
    {
        if (!ring_push(&ring, (uint8_t *)&i))
        {
            return false;
        }
    }

    return ring_push(&ring, (uint8_t *)&test_value) == false && ring_is_full(&ring) == true;
}

int main()
{
    assert(test_ring_empty_pop() == true);
    assert(test_ring_push_pop_8bit() == true);
    assert(test_ring_push_pop_32bit() == true);
    assert(test_ring_push_pop_struct() == true);
    assert(test_ring_push_push_pop_32bit() == true);
    assert(test_ring_push_push_pop_pop_32bit() == true);
    assert(test_ring_error_push_to_full() == true);
    assert(test_ring_push_pop_func() == true);

    printf("Tests passed\n");
}
