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

double dot_product(const Vector *const v1, const Vector *const v2);
double radian_between_normalized_vectors(const NormalizedVector *const v1, const NormalizedVector *const v2);
NormalizedVector normalized(const Vector *const v);
Vector rotated(const Vector *const v, double radian);

#endif // GEOMETRY_H