#include "gameparameterized.h"


void GameParameterized::TearDown() {

    for (int i = 0; i < start_field.size(); ++i) {

        start_field[i].clear();
        current_field[i].clear();
        next_field[i].clear();

    }

    start_field.clear();
    current_field.clear();
    next_field.clear();

    game_state = GameState::EDITING;

}
