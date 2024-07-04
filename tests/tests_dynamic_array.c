#include <macroassert.h>
#include <dynamic_array.h>

void test_array_has_correct_length_after_pushing_and_removing(void) {
    int *array = dyn_array_init(int);
    assert_eq(dyn_array_get_length(array), 0);
    
    dyn_array_push_rval(array, int, 5);
    assert_eq(dyn_array_get_length(array), 1);

    dyn_array_push_rval(array, int, 10);
    assert_eq(dyn_array_get_length(array), 2);

    dyn_array_remove_last(array);
    assert_eq(dyn_array_get_length(array), 1);

    dyn_array_remove_last(array);
    assert_eq(dyn_array_get_length(array), 0);

    dyn_array_remove_last(array);
    assert_eq(dyn_array_get_length(array), 0);

    dyn_array_free(array);
}

void test_array_pushes_correct_values(void) {
    int *array = dyn_array_init(int);
    dyn_array_push_rval(array, int, 5);
    dyn_array_push_rval(array, int, 10);
    dyn_array_push_rval(array, int, 8);

    assert_eq(array[0], 5);
    assert_eq(array[1], 10);
    assert_eq(array[2], 8);

    dyn_array_free(array);
}

void test_array_pushes_correct_values_big_input(void) {
    int *array = dyn_array_init(int);

    for (int i = 0; i < 100; i++) {
        dyn_array_push_rval(array, int, i);
    }

    assert_eq(array[99], 99);
}

void test_array_pops_correct_values(void) {
    int *array = dyn_array_init(int);
    dyn_array_push_rval(array, int, 3);
    dyn_array_push_rval(array, int, 1);
    dyn_array_push_rval(array, int, 9);

    int t1;
    dyn_array_pop(array, &t1);
    assert_eq(t1, 9);

    int t2;
    dyn_array_pop(array, &t2);
    assert_eq(t2, 1);

    int t3;
    dyn_array_pop(array, &t3);
    assert_eq(t3, 3);

    dyn_array_free(array);
}

void test_array_clear(void) {
    int *array = dyn_array_init(int);
    dyn_array_push_rval(array, int, 3);

    dyn_array_clear(array);
    assert_eq(dyn_array_get_length(array), 0);

    dyn_array_push_rval(array, int, 3);
    assert_eq(dyn_array_get_length(array), 1);
    assert_eq(array[0], 3);
}

void tests_dynamic_array(void) {
    test_array_has_correct_length_after_pushing_and_removing();
    test_array_pushes_correct_values();
    test_array_pushes_correct_values_big_input();
    test_array_pops_correct_values();
    test_array_clear();
}