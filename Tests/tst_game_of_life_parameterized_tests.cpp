
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <vector>
#include <map>
#include <QVector>

#include "gameparameterized.h"

using namespace testing;

QVector<QVector<bool>> GetField(const std::vector<std::vector<int>>& alive_indexes) {

    QVector<QVector<bool>> field;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {

        QVector<bool> line;

        for (int j = 0; j < FIELD_WIDTH; ++j) {

            line.push_back(false);

        }

        field.push_back(line);

    }

    //Set alive game cells
    for (int i = 0; i < alive_indexes.size(); ++i) {

        field[alive_indexes[i][0]][alive_indexes[i][1]] = true;

    }

    return field;

}

QVector<QVector<bool>> GetHomogeneousField(const bool& is_alive) {

    QVector<QVector<bool>> game_field;

    for (int i = 0; i < FIELD_HEIGHT; ++i) {

        QVector<bool> line;

        for (int j = 0; j < FIELD_WIDTH; ++j) {

            line.push_back(is_alive);

        }

        game_field.push_back(line);

    }


    return game_field;

}


TEST_P(GameParameterized, MakeGameStep_stop_tests) {

    ClearFields();

    QVector<QVector<bool>> field_parameter = GetParam();
    LoadField(field_parameter);
    current_field = start_field;
    game_state = GameState::RUNNING;

    MakeGameStep();
    MakeGameStep();

    EXPECT_EQ(game_state, GameState::STOPPED);

}

INSTANTIATE_TEST_CASE_P(
    MakeGameStep_stop_tests,
    GameParameterized,
    ::testing::Values(
            GetHomogeneousField(false),
            GetField({{1, 1}}),
            GetField({{1, 1}, {3, 3}}),
            GetField({{1, 1}, {1, 2}, {2, 1}, {2, 2}}),
            GetField({{47, 20}, {47, 21}, {48, 20}, {48, 21}}),
            GetField({{79, 10}, {79, 11}, {80, 10}, {80, 11}}),
            GetField({{3, 3}, {4, 2}, {4, 4}, {5, 2}, {5, 4}, {6, 3}}),
            GetField({{33, 53}, {34, 52}, {34, 54}, {35, 52}, {35, 54}, {36, 53}}),
            GetField({{73, 73}, {74, 72}, {74, 74}, {75, 72}, {75, 74}, {76, 73}}),
            GetField({{1, 0}, {0, 1}, {0, 2}, {1, 3}, {2, 1}, {2, 2}}),
            GetField({{71, 40}, {70, 41}, {70, 42}, {71, 43}, {72, 41}, {72, 42}}),
            GetField({{1, 73}, {0, 74}, {0, 75}, {1, 76}, {2, 74}, {2, 75}}),
            GetField({{FIELD_HEIGHT-1, FIELD_WIDTH-1}})));




