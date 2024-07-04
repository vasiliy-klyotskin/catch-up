#if !defined(PLAYERS_H)
#define PLAYERS_H

#include <unit.h>
#include <stdlib.h>

typedef struct {
    Unit *all_players;
} Players;

Players players_init(void);
void players_free(const Players *const players);
Unit *const players_get_catcher(const Players *const players);
void players_set_catcher(Players *const players, const Unit *const catcher);
Unit *const players_get_runner(const Players *const players, const size_t index);
void players_add_runner(Players *const players, const Vector position);
void players_set_runner(Players *const players, const Unit *const runner, const size_t index);
size_t players_runners_count(const Players *const players);

#endif // PLAYERS_H