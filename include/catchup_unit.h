#if !defined(CATCHUP_UNIT_H)
#define CATCHUP_UNIT_H

#include <geometry.h>
#include <stdbool.h>

typedef struct {
    Point position;
    bool is_tagger;
} CatchupUnit;


#endif // CATCHUP_UNIT_H