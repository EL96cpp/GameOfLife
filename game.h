#ifndef GAME_H
#define GAME_H

#include <QDebug>

#include <QObject>
#include <QVector>
#include <QTimer>

#define FIELD_WIDTH 220
#define FIELD_HEIGHT 170

enum class GameState {
    RUNNING,
    STOPPED,
    EDITING
};

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);
    void ClearFields();
    GameState GetGameState();
    QVector<QVector<bool>> GetStartField();

protected slots:
    void StartGame();
    void StopGame();
    void RestartGame();
    void FlipCellState(const qreal& x, const qreal& y);
    void MakeGameStep();
    void ChangeGameSpeed(int game_speed);
    void LoadField(QVector<QVector<bool>>& loaded_field);

signals:
    void GameFinished();
    void CalculateNextStep();
    void UpdateGameScene(const QVector<QVector<bool>>& current_field);

protected:
    bool CalculateCell(const int& i, const int& j);

protected:
    QVector<QVector<bool>> start_field;
    QVector<QVector<bool>> current_field;
    QVector<QVector<bool>> next_field;
    GameState game_state;
    int game_speed;
    QTimer game_timer;
};

#endif // GAME_H
