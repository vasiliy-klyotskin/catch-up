#include <geometry.h>
#include <math.h>

Vector vector_init(double x, double y) {
    Vector v;
    v.x = x;
    v.y = y;
    return v;
}

Vector vector_rotated(const Vector *const v, double radian) {
    Vector rotated_v;
    rotated_v.x = v->x * cos(radian) - v->y * sin(radian);
    rotated_v.y = v->x * sin(radian) + v->y * cos(radian);
    return rotated_v;
}

double vector_magnitude(const Vector *const v) {
    return sqrt(v->x * v->x + v->y * v->y);
}

Vector vector_difference(const Vector *const v1, const Vector *const v2) {
    return vector_init(v2->x - v1->x, v2->y - v1->y);
}

NormalizedVector vector_normalized(const Vector *const v) {
    double magnitude = vector_magnitude(v);
    NormalizedVector norm_v;
    if (magnitude == 0) {
        norm_v.direction.x = 0;
        norm_v.direction.y = 0;
        norm_v.magnitude = 0;
        return norm_v;
    }
    norm_v.direction.x = v->x / magnitude;
    norm_v.direction.y = v->y / magnitude;
    norm_v.magnitude = magnitude;
    return norm_v;
}

double vector_dot_product(const Vector *const v1, const Vector *const v2) {
    return v1->x * v2->x + v1->y * v2->y;
}

double vector_radian(const Vector *const v1, const Vector *const v2) {
    double angle1 = atan2(v1->y, v1->x);
    double angle2 = atan2(v2->y, v2->x);
    double angle = angle2 - angle1;
    if (angle > M_PI) {
        angle -= 2 * M_PI;
    } else if (angle < -M_PI) {
        angle += 2 * M_PI;
    }
    return angle;
}