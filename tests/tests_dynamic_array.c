#include <macroassert.h>
#include <dynamic_array.h>

void test_array_has_correct_length_after_pushing_and_removing(void) {
    int *array = init_dyn_array(int);
    assert_eq(get_length_dyn_array(array), 0);
    
    push_rval_dyn_array(array, int, 5);
    assert_eq(get_length_dyn_array(array), 1);

    push_rval_dyn_array(array, int, 10);
    assert_eq(get_length_dyn_array(array), 2);

    remove_last_dyn_array(array);
    assert_eq(get_length_dyn_array(array), 1);

    remove_last_dyn_array(array);
    assert_eq(get_length_dyn_array(array), 0);

    remove_last_dyn_array(array);
    assert_eq(get_length_dyn_array(array), 0);

    free_dyn_array(array);
}

void test_array_pushes_correct_values(void) {
    int *array = init_dyn_array(int);
    push_rval_dyn_array(array, int, 5);
    push_rval_dyn_array(array, int, 10);
    push_rval_dyn_array(array, int, 8);

    assert_eq(array[0], 5);
    assert_eq(array[1], 10);
    assert_eq(array[2], 8);

    free_dyn_array(array);
}

void test_array_pushes_correct_values_big_input(void) {
    int *array = init_dyn_array(int);

    for (int i = 0; i < 100; i++) {
        push_rval_dyn_array(array, int, i);
    }

    assert_eq(array[99], 99);
}

void test_array_pops_correct_values(void) {
    int *array = init_dyn_array(int);
    push_rval_dyn_array(array, int, 3);
    push_rval_dyn_array(array, int, 1);
    push_rval_dyn_array(array, int, 9);

    int t1;
    pop_dyn_array(array, &t1);
    assert_eq(t1, 9);

    int t2;
    pop_dyn_array(array, &t2);
    assert_eq(t2, 1);

    int t3;
    pop_dyn_array(array, &t3);
    assert_eq(t3, 3);

    free_dyn_array(array);
}

void tests_dynamic_array(void) {
    test_array_has_correct_length_after_pushing_and_removing();
    test_array_pushes_correct_values();
    test_array_pushes_correct_values_big_input();
    test_array_pops_correct_values();
}