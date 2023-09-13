#include "game.h"

Game::Game(QObject *parent)
    : QObject{parent}
    , game_state(GameState::EDITING)
{
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        QVector<bool> line;
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            line.push_back(false);
        }
        start_field.push_back(line);
    }
    current_field = start_field;
    next_field = start_field;
    connect(&game_timer, &QTimer::timeout, this, &Game::MakeGameStep);
}

void Game::ClearFields()
{
    if (game_state == GameState::RUNNING) {
        game_timer.stop();
    }
    game_state = GameState::EDITING;
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            start_field[i][j] = false;
            current_field[i][j] = false;
            next_field[i][j] = false;
        }
    }
}

GameState Game::GetGameState()
{
    return game_state;
}

QVector<QVector<bool>> Game::GetStartField()
{
    return start_field;
}

void Game::StartGame()
{
    if (game_state == GameState::EDITING) {
        current_field = start_field;
    }
    game_state = GameState::RUNNING;
    game_timer.start(1000/(game_speed*game_speed));
}

void Game::StopGame()
{
    game_state = GameState::STOPPED;
    game_timer.stop();
}

void Game::RestartGame()
{
    game_timer.stop();
    current_field = start_field;
    game_state = GameState::EDITING;
    emit UpdateGameScene(current_field);
}

void Game::FlipCellState(const qreal &x, const qreal &y)
{
    if (game_state == GameState::STOPPED) {
        current_field[y/10][x/10] = !current_field[y/10][x/10];
    } else {
        start_field[y/10][x/10] = !start_field[y/10][x/10];
    }
}

void Game::MakeGameStep()
{
    for (int i = 0; i < FIELD_HEIGHT; ++i) {
        for (int j = 0; j < FIELD_WIDTH; ++j) {
            next_field[i][j] = CalculateCell(i, j);
        }
    }
    if (current_field == next_field) {
        emit GameFinished();
        StopGame();
    }
    emit UpdateGameScene(next_field);
    current_field = next_field;
}

void Game::ChangeGameSpeed(int game_speed)
{
    this->game_speed = game_speed;
    game_timer.setInterval(1000/(game_speed*game_speed));
}

void Game::LoadField(QVector<QVector<bool> > &loaded_field)
{
    start_field = loaded_field;
    emit UpdateGameScene(start_field);
}

bool Game::CalculateCell(const int &i, const int &j)
{
    int alive_neighbours = 0;
    for (int k = i-1; k < i+2; ++k) {
        if(k < 0 || k == FIELD_HEIGHT) {
            continue;
        }
        for (int l = j-1; l < j+2; ++l) {
            if (l < 0 || l == FIELD_WIDTH || (k==i && l==j)) {
                continue;
            }
            if (current_field[k][l] == true) {
                ++alive_neighbours;
            }
        }
    }
    if (current_field[i][j] == true) {
        if (alive_neighbours == 2 || alive_neighbours == 3) {
            return true;
        } else {
            return false;
        }
    } else {
        if (alive_neighbours == 3) {
            return true;
        } else {
            return false;
        }
    }
}
