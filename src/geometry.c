#include <geometry.h>
#include <math.h>

double dot_product(Vector *v1, Vector *v2) {
    return v1->x * v2->x + v1->y * v2->y;
}

NormalizedVector normalized(Vector *v) {
    double magnitude = sqrt(v->x * v->x + v->y * v->y);
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

Vector rotated(Vector *v, double radian) {
    Vector rotated_v;
    rotated_v.x = v->x * cos(radian) - v->y * sin(radian);
    rotated_v.y = v->x * sin(radian) + v->y * cos(radian);
    return rotated_v;
}