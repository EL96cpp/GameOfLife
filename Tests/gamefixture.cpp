#include "gamefixture.h"

GameFixture::GameFixture() {


}

void GameFixture::SetUp() {

    if (first_test) {

        return;

    }

    for (int i = 0; i < FIELD_HEIGHT; ++i) {

        QVector<bool> line;

        for (int j = 0; j < FIELD_WIDTH; ++j) {

            line.push_back(false);

        }

        start_field.push_back(line);

    }

    current_field = start_field;
    next_field = start_field;
    game_state = GameState::EDITING;

}

void GameFixture::TearDown() {

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

