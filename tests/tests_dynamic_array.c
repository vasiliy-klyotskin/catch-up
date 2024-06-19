#include <macroassert.h>
#include <dynamic_array.h>

void test_array_has_correct_length_after_pushing_and_removing() {
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

void tests_dynamic_array() {
    test_array_has_correct_length_after_pushing_and_removing();
}