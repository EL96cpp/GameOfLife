#ifndef GAMEPARAMETERIZED_H
#define GAMEPARAMETERIZED_H

#include <gtest/gtest.h>
#include <QVector>

#include "../game.h"

class GameParameterized : public ::testing::TestWithParam<QVector<QVector<bool>>>,
                          public Game {

public:
    void TearDown() override;

protected:
    bool first_test = true;

};

#endif // GAMEPARAMETERIZED_H
