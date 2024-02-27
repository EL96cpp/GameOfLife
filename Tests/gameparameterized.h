#ifndef GAMEPARAMETERIZED_H
#define GAMEPARAMETERIZED_H

#include <gtest/gtest.h>
#include <QVector>

#include "../game.h"

class GameParameterized : public ::testing::TestWithParam<QVector<QVector<bool>>>,
                          public Game {};

#endif // GAMEPARAMETERIZED_H
