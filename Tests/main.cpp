#include <QCoreApplication>
#include <QTimer>
#include <gtest/gtest.h>

#include "gamefixture.h"

int main(int argc, char **argv)
{

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
