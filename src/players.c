#include <players.h>
#include <dynamic_array.h>

enum UnitsLayout {
    CATCHER,
    RUNNERS
};

Players players_init(void) {
    Players players;
    Unit catcher = unit_init(0, 0);
    players.all_players = init_dyn_array(Unit);
    push_dyn_array(players.all_players, catcher);
    return players;
}

void players_free(const Players *const players) {
    free_dyn_array(players->all_players);
}

Unit *const players_get_catcher(const Players *const players) {
    return &players->all_players[CATCHER];
}

void players_set_catcher(Players *const players, const Unit *const catcher) {
    players->all_players[CATCHER] = *catcher;
}

Unit *const players_get_runner(const Players *const players, const size_t index) {
    return &players->all_players[RUNNERS + index];
}

void players_add_runner(Players *const players, const Vector position) {
    push_rval_dyn_array(players->all_players, Unit, unit_init(position.x, position.y));
}

void players_set_runner(Players *const players, const Unit *const runner, const size_t index) {
    players->all_players[RUNNERS + index] = *runner;
}

size_t players_runners_count(const Players *const players) {
    return get_length_dyn_array(players->all_players) - RUNNERS;
}