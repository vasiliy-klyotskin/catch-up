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

double dot_product(Vector *v1, Vector *v2);
NormalizedVector normalized(Vector *v);
Vector rotated(Vector *v, double radian);

#endif // GEOMETRY_H