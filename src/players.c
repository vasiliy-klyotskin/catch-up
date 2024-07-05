#include <players.h>
#include <dynamic_array.h>

enum UnitsLayout {
    CATCHER,
    RUNNERS
};

Players players_init(void) {
    Players players;
    Unit catcher = unit_init(0, 0);
    players.all_players = dyn_array_init(Unit);
    dyn_array_push(players.all_players, catcher);
    return players;
}

void players_free(const Players *const players) {
    dyn_array_free(players->all_players);
}

Unit *const players_get_catcher(const Players *const players) {
    return &players->all_players[CATCHER];
}

Unit *const players_get_runner(const Players *const players, const size_t index) {
    return &players->all_players[RUNNERS + index];
}

void players_add_runner(Players *const players, const Vector position) {
    dyn_array_push_rval(players->all_players, Unit, unit_init(position.x, position.y));
}

void players_set_runner(Players *const players, const Unit *const runner, const size_t index) {
    players->all_players[RUNNERS + index] = *runner;
}

size_t players_runners_count(const Players *const players) {
    return dyn_array_get_length(players->all_players) - RUNNERS;
}