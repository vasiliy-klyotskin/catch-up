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

double vector_dot_product(const Vector *const v1, const Vector *const v2);
double vector_magnitude(const Vector *const v);
double normalized_vectors_radian(const NormalizedVector *const v1, const NormalizedVector *const v2);
Vector vector_init(double x, double y);
Vector vector_rotated(const Vector *const v, double radian);
NormalizedVector vector_normalized(const Vector *const v);

#endif // GEOMETRY_H