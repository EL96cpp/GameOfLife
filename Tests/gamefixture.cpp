#include "gamefixture.h"

GameFixture::GameFixture() {


}

void GameFixture::SetUp()
{
    qDebug() << "Start tests";

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

void GameFixture::TearDown()
{
    qDebug() << "End tests";
}

