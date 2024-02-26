
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include <chrono>
#include <thread>

#include "gamefixture.h"

using namespace testing;


TEST_F(GameFixture, initial_tests) {

    EXPECT_EQ(start_field, current_field);
    EXPECT_EQ(start_field, next_field);
    EXPECT_EQ(start_field.size(), FIELD_HEIGHT);
    EXPECT_EQ(start_field[0].size(), FIELD_WIDTH);
    EXPECT_EQ(game_state, GameState::EDITING);
    EXPECT_EQ(game_speed, 3);

    for (int i = 0; i <  FIELD_HEIGHT; ++i) {

        for (int j = 0; j < FIELD_WIDTH; ++j) {

            EXPECT_EQ(start_field[i][j], false);
            EXPECT_EQ(current_field[i][j], false);
            EXPECT_EQ(next_field[i][j], false);

        }

    }

}

TEST_F(GameFixture, change_game_speed_tests) {

    ChangeGameSpeed(1);
    EXPECT_EQ(game_speed, 1);
    EXPECT_EQ(game_timer.interval(), 1000/(game_speed*game_speed));
    ChangeGameSpeed(2);
    EXPECT_EQ(game_speed, 2);
    EXPECT_EQ(game_timer.interval(), 1000/(game_speed*game_speed));
    ChangeGameSpeed(3);
    EXPECT_EQ(game_speed, 3);
    EXPECT_EQ(game_timer.interval(), 1000/(game_speed*game_speed));
    ChangeGameSpeed(4);
    EXPECT_EQ(game_speed, 4);
    EXPECT_EQ(game_timer.interval(), 1000/(game_speed*game_speed));
    ChangeGameSpeed(5);
    EXPECT_EQ(game_speed, 5);
    EXPECT_EQ(game_timer.interval(), 1000/(game_speed*game_speed));

}

TEST_F(GameFixture, flip_corner_cells_tests) {

    //Upper left corner case

    FlipCellState(0, 0);
    EXPECT_EQ(start_field[0][0], true);
    EXPECT_EQ(start_field[0][1], false);
    EXPECT_EQ(start_field[1][0], false);
    EXPECT_EQ(start_field[1][1], false);

    FlipCellState(0, 0);
    EXPECT_EQ(start_field[0][0], false);
    EXPECT_EQ(start_field[0][1], false);
    EXPECT_EQ(start_field[1][0], false);
    EXPECT_EQ(start_field[1][1], false);


    //Lower left corner case

    FlipCellState(0, (FIELD_HEIGHT-1)*10);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][0], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][1], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][0], true);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][1], false);

    FlipCellState(0, (FIELD_HEIGHT-1)*10);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][0], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][1], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][0], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][1], false);


    //Upper right corner case

    FlipCellState((FIELD_WIDTH-1)*10, 0);
    EXPECT_EQ(start_field[0][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[0][FIELD_WIDTH-1], true);
    EXPECT_EQ(start_field[1][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[1][FIELD_WIDTH-1], false);

    FlipCellState((FIELD_WIDTH-1)*10, 0);
    EXPECT_EQ(start_field[0][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[0][FIELD_WIDTH-1], false);
    EXPECT_EQ(start_field[1][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[1][FIELD_WIDTH-1], false);


    //Lower right corner case

    FlipCellState((FIELD_WIDTH-1)*10, (FIELD_HEIGHT-1)*10);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][FIELD_WIDTH-1], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][FIELD_WIDTH-1], true);

    FlipCellState((FIELD_WIDTH-1)*10, (FIELD_HEIGHT-1)*10);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-2][FIELD_WIDTH-1], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][FIELD_WIDTH-2], false);
    EXPECT_EQ(start_field[FIELD_HEIGHT-1][FIELD_WIDTH-1], false);


}


TEST_F(GameFixture, inner_cells_flip_tests) {

    //Cells with 8 neighbours

    FlipCellState(10, 10);
    EXPECT_EQ(start_field[0][0], false);
    EXPECT_EQ(start_field[0][1], false);
    EXPECT_EQ(start_field[0][2], false);
    EXPECT_EQ(start_field[1][0], false);
    EXPECT_EQ(start_field[1][1], true);
    EXPECT_EQ(start_field[1][2], false);
    EXPECT_EQ(start_field[2][0], false);
    EXPECT_EQ(start_field[2][1], false);
    EXPECT_EQ(start_field[2][2], false);

    FlipCellState(10, 10);
    EXPECT_EQ(start_field[0][0], false);
    EXPECT_EQ(start_field[0][1], false);
    EXPECT_EQ(start_field[0][2], false);
    EXPECT_EQ(start_field[1][0], false);
    EXPECT_EQ(start_field[1][1], false);
    EXPECT_EQ(start_field[1][2], false);
    EXPECT_EQ(start_field[2][0], false);
    EXPECT_EQ(start_field[2][1], false);
    EXPECT_EQ(start_field[2][2], false);

    //Center cell

    FlipCellState(((FIELD_WIDTH-1)/2)*10, ((FIELD_HEIGHT-1)/2)*10);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2-1][(FIELD_WIDTH-1)/2-1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2-1][(FIELD_WIDTH-1)/2], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2-1][(FIELD_WIDTH-1)/2+1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2][(FIELD_WIDTH-1)/2-1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2][(FIELD_WIDTH-1)/2], true);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2][(FIELD_WIDTH-1)/2+1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2+1][(FIELD_WIDTH-1)/2-1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2+1][(FIELD_WIDTH-1)/2], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2+1][(FIELD_WIDTH-1)/2+1], false);

    FlipCellState(((FIELD_WIDTH-1)/2)*10, ((FIELD_HEIGHT-1)/2)*10);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2-1][(FIELD_WIDTH-1)/2-1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2-1][(FIELD_WIDTH-1)/2], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2-1][(FIELD_WIDTH-1)/2+1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2][(FIELD_WIDTH-1)/2-1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2][(FIELD_WIDTH-1)/2], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2][(FIELD_WIDTH-1)/2+1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2+1][(FIELD_WIDTH-1)/2-1], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2+1][(FIELD_WIDTH-1)/2], false);
    EXPECT_EQ(start_field[(FIELD_HEIGHT-1)/2+1][(FIELD_WIDTH-1)/2+1], false);

}


TEST_F(GameFixture, make_game_step_function_tests) {


    //Check if game stops, when game fields doesn't update

    game_state = GameState::EDITING;
    current_field = start_field;
    MakeGameStep();
    EXPECT_EQ(game_state, GameState::STOPPED);


    ClearFields();
    FlipCellState(10, 10);
    MakeGameStep();
    EXPECT_EQ(game_state, GameState::STOPPED);


    //Check if simple oscillator works correctly

    ClearFields();
    FlipCellState(10, 10);
    FlipCellState(10, 20);
    FlipCellState(10, 30);

    current_field = start_field;

    EXPECT_EQ(current_field[1][1], true);
    EXPECT_EQ(current_field[2][1], true);
    EXPECT_EQ(current_field[3][1], true);

    MakeGameStep();
    EXPECT_EQ(current_field[0][0], false);
    EXPECT_EQ(current_field[0][1], false);
    EXPECT_EQ(current_field[0][2], false);
    EXPECT_EQ(current_field[1][0], false);
    EXPECT_EQ(current_field[1][1], false);
    EXPECT_EQ(current_field[1][2], false);
    EXPECT_EQ(current_field[2][0], true);
    EXPECT_EQ(current_field[2][1], true);
    EXPECT_EQ(current_field[2][2], true);
    EXPECT_EQ(current_field[3][0], false);
    EXPECT_EQ(current_field[3][1], false);
    EXPECT_EQ(current_field[3][2], false);
    EXPECT_EQ(current_field[4][0], false);
    EXPECT_EQ(current_field[4][1], false);
    EXPECT_EQ(current_field[4][2], false);

    MakeGameStep();
    EXPECT_EQ(current_field[0][0], false);
    EXPECT_EQ(current_field[0][1], false);
    EXPECT_EQ(current_field[0][2], false);
    EXPECT_EQ(current_field[1][0], false);
    EXPECT_EQ(current_field[1][1], true);
    EXPECT_EQ(current_field[1][2], false);
    EXPECT_EQ(current_field[2][0], false);
    EXPECT_EQ(current_field[2][1], true);
    EXPECT_EQ(current_field[2][2], false);
    EXPECT_EQ(current_field[3][0], false);
    EXPECT_EQ(current_field[3][1], true);
    EXPECT_EQ(current_field[3][2], false);
    EXPECT_EQ(current_field[4][0], false);
    EXPECT_EQ(current_field[4][1], false);
    EXPECT_EQ(current_field[4][2], false);

}

