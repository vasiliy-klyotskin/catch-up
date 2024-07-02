#if !defined(GEOMETRY_H)
#define GEOMETRY_H

typedef struct {
    double x;
    double y;
} Vector;

typedef struct {
    Vector direction;
    double magnitude;
} NormalizedVector;

Vector vector_init(const double x, const double y);
Vector vector_difference(const Vector *const v1, const Vector *const v2);
Vector vector_rotated(const Vector *const v, double radian);
const NormalizedVector vector_normalized(const Vector *const v);
double vector_dot_product(const Vector *const v1, const Vector *const v2);
double vector_magnitude(const Vector *const v);
double vector_radian(const Vector *const v1, const Vector *const v2);

#endif // GEOMETRY_H