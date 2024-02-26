#ifndef GAMEFIXTURE_H
#define GAMEFIXTURE_H

#include <gtest/gtest.h>

#include "../game.h"

class GameFixture : public ::testing::Test, public Game
{
public:
    GameFixture();

    void SetUp() override;
    void TearDown() override;

protected:
    bool first_test = true;

};

#endif // GAMEFIXTURE_H
