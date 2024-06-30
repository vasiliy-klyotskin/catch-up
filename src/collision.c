#include <collision.h>
#include <dynamic_array.h>
#include <geometry.h>

void detect_collisions(
    Unit *const units,
    Collision *collisions,
    const double radius
) {
    size_t units_length = get_length_dyn_array(units);
    for (size_t u1_index = 0; u1_index < units_length; u1_index++) {
        for (size_t u2_index = u1_index; u2_index < units_length; u2_index++) {
            if (u1_index == u2_index) { continue; }
            Unit *u1 = &units[u1_index];
            Unit *u2 = &units[u2_index];
            Vector difference = vector_difference(&u1->position, &u2->position);
            NormalizedVector offset = vector_normalized(&difference);
            if (offset.magnitude < radius * 2) {
                Collision collision;
                collision.u1 = u1;
                collision.u2 = u2;
                collision.offset = offset;
                push_dyn_array(collisions, collision);
            }
        }
    }
}

void resolve_positions(const Collision *const collision, const double radius) {
    double correction_coef = (2 * radius - collision->offset.magnitude) * 0.5;
    double correction_x = collision->offset.direction.x * correction_coef;
    double correction_y = collision->offset.direction.y * correction_coef;
    collision->u1->position.x -= correction_x;
    collision->u1->position.y -= correction_y;
    collision->u2->position.x += correction_x;
    collision->u2->position.y += correction_y;
}

void resolve_velocity(Collision *const collision) {
    Vector *norm = &collision->offset.direction;
    Vector tang = vector_init(-norm->y, norm->x);
    double u1_norm_dot_prod = vector_dot_product(&collision->u1->velocity, norm);
    double u2_norm_dot_prod = vector_dot_product(&collision->u2->velocity, norm);
    double u1_tang_dot_prod = vector_dot_product(&collision->u1->velocity, &tang);
    double u2_tang_dot_prod = vector_dot_product(&collision->u2->velocity, &tang);
    collision->u1->velocity.x = tang.x * u1_tang_dot_prod + norm->x * u2_norm_dot_prod;
    collision->u1->velocity.y = tang.y * u1_tang_dot_prod + norm->y * u2_norm_dot_prod;
    collision->u2->velocity.x = tang.x * u2_tang_dot_prod + norm->x * u1_norm_dot_prod;
    collision->u2->velocity.y = tang.y * u2_tang_dot_prod + norm->y * u1_norm_dot_prod;
}

void resolve_collisions(Collision *const collisions, const double radius) {
    size_t collisions_length = get_length_dyn_array(collisions);
    for (size_t i = 0; i < collisions_length; i++) {
        Collision *collision = &collisions[i];
        resolve_positions(collision, radius);
        resolve_velocity(collision);
    }
}