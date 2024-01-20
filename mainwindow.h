#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QBrush>
#include <QColor>
#include <QFont>
#include <QFontDatabase>

#include "gamecell.h"
#include "game.h"
#include "savedialog.h"
#include "loaddialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void UpdateGameScene(const QVector<QVector<bool>>& current_field);
    void FlipCellColor(const qreal& x, const qreal& y);
    void GameFinished();

signals:
    void StartGame();
    void StopGame();
    void RestartGame();

private slots:
    void on_ClearButton_clicked();

    void on_LoadButton_clicked();

    void on_SaveButton_clicked();

    void on_StartStopButton_clicked();

    void on_RestartButton_clicked();

private:
    void SetGameScene();
    void SetFont();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* game_scene;
    Game* game;
    QFont* font;
    QVector<QVector<GameCell*>> graphics_field;
    QColor alive_color;
    QColor dead_color;
    QBrush alive_brush;
    QBrush dead_brush;
};
#endif // MAINWINDOW_H
