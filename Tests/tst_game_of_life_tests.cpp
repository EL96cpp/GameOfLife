
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

TEST_F(GameFixture, start_and_stop_functions_tests) {

    //Check if game stops, when there is no field changes
    StartGame();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::STOPPED);

    FlipCellState(1, 1);
    StartGame();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::STOPPED);

    //Start and stop simple oscillator
    FlipCellState(1,1);
    FlipCellState(1, 2);
    FlipCellState(1, 3);
    StartGame();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::RUNNING);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::RUNNING);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::RUNNING);

    StopGame();
    EXPECT_EQ(game_state, GameState::STOPPED);

    StartGame();
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::RUNNING);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::RUNNING);
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(game_state, GameState::RUNNING);


}

