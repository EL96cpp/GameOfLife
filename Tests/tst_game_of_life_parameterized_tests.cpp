
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

TEST_P(GameParameterized, load_function_tests) {

    QVector<QVector<bool>> field_parameter = GetParam();
    LoadField(field_parameter);
    EXPECT_EQ(start_field, field_parameter);

}

INSTANTIATE_TEST_CASE_P(
    load_function_tests,
    GameParameterized,
    ::testing::Values(
        GetField({{1, 1}, {1, 2}, {1, 3}}),
        GetField({{1, 1}, {2, 2}, {3, 2}, {3, 1}}),
        GetField({{4, 4}}),
        GetHomogeneousField(true),
        GetHomogeneousField(false)
        ));
