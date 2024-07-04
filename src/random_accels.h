#if !defined(RANDOM_ACCELS)
#define RANDOM_ACCELS

#include <geometry.h>
#include <stdlib.h>

typedef struct {
    double (*_rand_minus1_1)(void);
    Vector *_elements;
    double _coef;
    int _updates_count_before_reset;
    int _updates_count_since_last_reset;
} RandomAccels;

RandomAccels random_accels_init(double (*const rand_minus1_1)(void), const int update_delay, const double coef);
const Vector *const random_accels_get(const RandomAccels *const accels, const size_t index);
void random_accels_update(RandomAccels *const accels);
void random_accels_add(RandomAccels *const accels);
void random_accels_free(const RandomAccels *const accels);

#endif // RANDOM_ACCELS
