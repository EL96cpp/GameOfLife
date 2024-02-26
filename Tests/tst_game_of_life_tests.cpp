
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>

#include "gamefixture.h"

using namespace testing;

TEST_F(GameFixture, initial_tests) {

    EXPECT_EQ(start_field, current_field);
    EXPECT_EQ(start_field, next_field);
    EXPECT_EQ(start_field.size(), FIELD_HEIGHT);
    EXPECT_EQ(start_field[0].size(), FIELD_WIDTH);
    EXPECT_EQ(game_state, GameState::EDITING);

}

TEST_F(GameFixture, flip_cell_tests) {

    FlipCellState(0, 0);
    EXPECT_EQ(start_field[0][0], true);
    EXPECT_EQ(start_field[0][1], false);
    EXPECT_EQ(start_field[1][0], false);
    EXPECT_EQ(start_field[1][1], false);


    FlipCellState(0, 0);
    EXPECT_EQ(start_field[0][0], false);


    FlipCellState(1, 1);
    EXPECT_EQ(start_field[1][1], true);
    EXPECT_EQ(start_field[0][0], false);

    FlipCellState(0, 0);
    EXPECT_EQ(start_field[0][0], false);

}
