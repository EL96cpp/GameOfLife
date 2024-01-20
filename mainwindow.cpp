#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
    , alive_color(149, 208, 155), dead_color(43, 43, 43)
    , game_scene(new QGraphicsScene(this))
    , game(new Game) {

    ui->setupUi(this);
    setWindowTitle("Game of life");
    ui->graphicsView->setScene(game_scene);
    ui->spinBox->setRange(1, 5);
    ui->spinBox->setValue(3);

    alive_brush.setColor(alive_color);
    alive_brush.setStyle(Qt::SolidPattern);
    dead_brush.setColor(dead_color);
    dead_brush.setStyle(Qt::SolidPattern);
    SetGameScene();
    SetFont();

    connect(game, &Game::UpdateGameScene, this, &MainWindow::UpdateGameScene);
    connect(game, &Game::GameFinished, this, &MainWindow::GameFinished);
    connect(this, &MainWindow::StartGame, game, &Game::StartGame);
    connect(this, &MainWindow::StopGame, game, &Game::StopGame);
    connect(this, &MainWindow::RestartGame, game, &Game::RestartGame);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), game, &Game::ChangeGameSpeed);
    game->ChangeGameSpeed(ui->spinBox->value());

}

MainWindow::~MainWindow() {

    delete ui;

}

void MainWindow::UpdateGameScene(const QVector<QVector<bool>> &current_field) {

    for (int i = 0; i < FIELD_HEIGHT; ++i) {

        for (int j = 0; j < FIELD_WIDTH; ++j) {

            graphics_field[i][j]->UpdateCell(current_field[i][j], (current_field[i][j]) ? alive_brush : dead_brush);

        }

    }

}

void MainWindow::FlipCellColor(const qreal &x, const qreal &y) {

    graphics_field[y/10][x/10]->PaintCell((graphics_field[y/10][x/10]->GetState()) ? alive_brush : dead_brush);

}


void MainWindow::GameFinished() {

    ui->StartStopButton->setText("START");

}

void MainWindow::SetGameScene() {

    for (int i = 0; i < FIELD_HEIGHT; ++i) {

        QVector<GameCell*> line;

        for (int j = 0; j < FIELD_WIDTH; ++j) {

            line.push_back(new GameCell(0 + j*10, 0 + i*10, dead_brush));
            connect(*line.rbegin(), &GameCell::FlipCellState, game, &Game::FlipCellState);
            connect(*line.rbegin(), &GameCell::FlipCellState, this, &MainWindow::FlipCellColor);
            game_scene->addItem(*line.rbegin());

        }

        graphics_field.push_back(line);

    }

}

void MainWindow::SetFont() {

    int id = QFontDatabase::addApplicationFont(":/Font.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    font = new QFont(family);
    ui->LoadButton->setFont(*font);
    ui->SaveButton->setFont(*font);
    ui->StartStopButton->setFont(*font);
    ui->RestartButton->setFont(*font);
    ui->ClearButton->setFont(*font);
    ui->speed_label->setFont(*font);
    ui->spinBox->setFont(*font);

}

void MainWindow::on_ClearButton_clicked() {

    game->ClearFields();
    ui->StartStopButton->setText("START");

    for (auto& line : graphics_field) {

        for (auto& cell : line) {

            cell->UpdateCell(false, dead_brush);

        }

    }

}


void MainWindow::on_LoadButton_clicked() {

    if (game->GetGameState() == GameState::RUNNING) {

        ui->StartStopButton->setText("START");
        emit StopGame();

    }

    LoadDialog* load_dialog = new LoadDialog(this);
    connect(load_dialog, &LoadDialog::FieldLoaded, game, &Game::LoadField);
    load_dialog->show();

}


void MainWindow::on_SaveButton_clicked() {

    if (game->GetGameState() == GameState::RUNNING) {

        ui->StartStopButton->setText("START");
        emit StopGame();

    }

    QVector<QVector<bool>> save_field = game->GetStartField();
    SaveDialog* save_dialog = new SaveDialog(save_field, this);
    save_dialog->show();

}


void MainWindow::on_StartStopButton_clicked() {

    if (game->GetGameState() != GameState::RUNNING) {

        ui->StartStopButton->setText("STOP");
        emit StartGame();

    } else {

        ui->StartStopButton->setText("START ");
        emit StopGame();

    }

}


void MainWindow::on_RestartButton_clicked() {

    ui->StartStopButton->setText("START");
    emit RestartGame();

}

