#include <macroassert.h>
#include <players.h>

void test_players_get_catcher(void) {
    const Players players = players_init();
    const Unit *const catcher = players_get_catcher(&players);

    assert_fp_eq(catcher->position.x, 0);
    assert_fp_eq(catcher->position.y, 0);

    players_free(&players);
}

void test_players_get_runner(void) {
    Players players = players_init();
    assert_eq(players_runners_count(&players), 0);

    players_add_runner(&players, vector_init(1, 2));
    assert_eq(players_runners_count(&players), 1);
    const Unit *const player_0 = players_get_runner(&players, 0);
    assert_fp_eq(player_0->position.x, 1);
    assert_fp_eq(player_0->position.y, 2);

    players_add_runner(&players, vector_init(5, 6));
    assert_eq(players_runners_count(&players), 2);
    const Unit *const player_1 = players_get_runner(&players, 1);
    assert_fp_eq(player_1->position.x, 5);
    assert_fp_eq(player_1->position.y, 6);

    players_free(&players);
}

void tests_players(void) {
    test_players_get_catcher();
    test_players_get_runner();
}