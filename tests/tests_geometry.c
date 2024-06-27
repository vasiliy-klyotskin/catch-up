#include <geometry.h>
#include <math.h>
#include <macroassert.h>

void test_vector_dot_product() {
    Vector v3 = vector_init(2.25, -2);
    Vector v4 = vector_init(3, -0.7);

    double dp2 = vector_dot_product(&v3, &v4);

    assert_fp_eq(dp2, 8.15);
}

void test_vector_normalized_when_vector_is_zero() {
    Vector v = vector_init(0, 0);

    NormalizedVector norm_v = vector_normalized(&v);

    assert_eq(norm_v.direction.x, 0);
    assert_eq(norm_v.direction.y, 0);
    assert_eq(norm_v.magnitude, 0);
}

void test_vector_normalized() {
    Vector v = vector_init(3, 4);

    NormalizedVector norm_v = vector_normalized(&v);

    assert_fp_eq(norm_v.direction.x, 0.6);
    assert_fp_eq(norm_v.direction.y, 0.8);
    assert_fp_eq(norm_v.magnitude, 5);
}

void test_vector_rotation() {
    Vector v = vector_init(1, 0);

    Vector rotated_v1 = vector_rotated(&v, M_PI / 2);
    assert_fp_eq(rotated_v1.x, 0);
    assert_fp_eq(rotated_v1.y, 1);

    Vector rotated_v2 = vector_rotated(&v, M_PI);
    assert_fp_eq(rotated_v2.x, -1);
    assert_fp_eq(rotated_v2.y, 0);

    Vector rotated_v3 = vector_rotated(&v, M_PI / 6);
    assert_fp_eq(rotated_v3.x, 0.86602540378);
    assert_fp_eq(rotated_v3.y, 0.5);
}

void test_normalized_vectors_radian() {
    NormalizedVector nv1;
    NormalizedVector nv2;
    nv1.direction = vector_init(1, 0);
    nv2.direction = vector_init(0, 1);

    assert_fp_eq(normalized_vectors_radian(&nv1, &nv2), M_PI / 2);

    nv1.direction = vector_init(0, 1);
    nv2.direction = vector_init(1, 0);

    assert_fp_eq(normalized_vectors_radian(&nv1, &nv2), -M_PI / 2);

    nv1.direction = vector_init(1, 0);
    nv2.direction = vector_init(0.86602540378, 0.5);

    assert_fp_eq(normalized_vectors_radian(&nv1, &nv2), M_PI / 6);
}

void test_vector_magnitude() {
    Vector v = vector_init(3, 4);

    assert_fp_eq(vector_magnitude(&v), 5);
}

void test_vector_difference() {
    Vector v1 = vector_init(5, 5);
    Vector v2 = vector_init(8, 7);

    Vector difference = vector_difference(&v1, &v2);

    assert_fp_eq(difference.x, 3);
    assert_fp_eq(difference.y, 2);
}

void tests_geometry() {
    test_vector_dot_product();
    test_vector_normalized_when_vector_is_zero();
    test_vector_normalized();
    test_vector_rotation();
    test_vector_magnitude();
    test_vector_difference();
    test_normalized_vectors_radian();
}