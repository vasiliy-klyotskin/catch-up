#include <macroassert.h>
#include <geometry.h>
#include <math.h>

static Vector rotated_by(double radian) {
    return vector_init(cos(radian), sin(radian));
}

static void test_vector_dot_product(void) {
    const Vector v3 = vector_init(2.25, -2);
    const Vector v4 = vector_init(3, -0.7);

    const double dp2 = vector_dot_product(&v3, &v4);

    assert_fp_eq(dp2, 8.15);
}

static void test_vector_normalized_when_vector_is_zero(void) {
    const Vector v = vector_init(0, 0);

    const NormalizedVector norm_v = vector_normalized(&v);

    assert_eq(norm_v.direction.x, 0);
    assert_eq(norm_v.direction.y, 0);
    assert_eq(norm_v.magnitude, 0);
}

static void test_vector_normalized(void) {
    const Vector v = vector_init(3, 4);

    const NormalizedVector norm_v = vector_normalized(&v);

    assert_fp_eq(norm_v.direction.x, 0.6);
    assert_fp_eq(norm_v.direction.y, 0.8);
    assert_fp_eq(norm_v.magnitude, 5);
}

static void test_vector_rotation(void) {
    const Vector v = vector_init(1, 0);

    const Vector rotated_v1 = vector_rotated(&v, M_PI / 2);
    assert_fp_eq(rotated_v1.x, 0);
    assert_fp_eq(rotated_v1.y, 1);

    const Vector rotated_v2 = vector_rotated(&v, M_PI);
    assert_fp_eq(rotated_v2.x, -1);
    assert_fp_eq(rotated_v2.y, 0);

    const Vector rotated_v3 = vector_rotated(&v, M_PI / 6);
    assert_fp_eq(rotated_v3.x, 0.86602540378);
    assert_fp_eq(rotated_v3.y, 0.5);
}

static void test_vector_radian(void) {
    Vector v1;
    Vector v2;

    v1 = vector_init(1, 0);
    v2 = vector_init(1, 0);

    assert_fp_eq(vector_radian(&v1, &v2), 0);

    v1 = vector_init(1, 0);
    v2 = vector_init(-1, 0);

    assert_fp_eq(fabs(vector_radian(&v1, &v2)), M_PI);

    v1 = vector_init(-0.6, 0.8);
    v2 = vector_init(0.6, -0.8);

    assert_fp_eq(fabs(vector_radian(&v1, &v2)), M_PI);

    v1 = vector_init(1, 0);
    v2 = vector_init(0, 1);

    assert_fp_eq(vector_radian(&v1, &v2), M_PI / 2);

    v1 = vector_init(0, 1);
    v2 = vector_init(1, 0);

    assert_fp_eq(vector_radian(&v1, &v2), -M_PI / 2);

    v1 = rotated_by(M_PI * 4 / 6);
    v2 = rotated_by(-M_PI / 6);

    assert_fp_eq(vector_radian(&v1, &v2), -M_PI * 5 / 6);

    v1 = rotated_by(-M_PI / 6);
    v2 = rotated_by(M_PI * 4 / 6);
    
    assert_fp_eq(vector_radian(&v1, &v2), M_PI * 5 / 6);

    v1 = rotated_by(M_PI * 5 / 6);
    v2 = rotated_by(-M_PI * 5 / 6);

    assert_fp_eq(vector_radian(&v1, &v2), M_PI / 3);

    v1 = rotated_by(-M_PI * 5 / 6);
    v2 = rotated_by(M_PI * 5 / 6);
    
    assert_fp_eq(vector_radian(&v1, &v2), -M_PI / 3);
}

static void test_vector_magnitude(void) {
    const Vector v = vector_init(3, 4);

    assert_fp_eq(vector_magnitude(&v), 5);
}

static void test_vector_difference(void) {
    const Vector v1 = vector_init(5, 5);
    const Vector v2 = vector_init(8, 7);

    const Vector difference = vector_difference(&v1, &v2);

    assert_fp_eq(difference.x, 3);
    assert_fp_eq(difference.y, 2);
}

static void test_vector_sum(void) {
    const Vector v1 = vector_init(-5, 5);
    const Vector v2 = vector_init(8, -7);

    const Vector sum = vector_sum(&v1, &v2);

    assert_fp_eq(sum.x, 3);
    assert_fp_eq(sum.y, -2);
}

static void test_vector_scale(void) {
    const Vector v = vector_init(-5, 10);
    const double factor = 1.5;

    const Vector scaled = vector_scaled(&v, factor);

    assert_fp_eq(scaled.x, -7.5);
    assert_fp_eq(scaled.y, 15);
}

void tests_geometry(void) {
    test_vector_dot_product();
    test_vector_normalized_when_vector_is_zero();
    test_vector_normalized();
    test_vector_rotation();
    test_vector_magnitude();
    test_vector_difference();
    test_vector_radian();
    test_vector_sum();
    test_vector_scale();
}