#include <QFontDatabase>

#include "loaddialog.h"
#include "ui_loaddialog.h"
#include "game.h"

LoadDialog::LoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadDialog)
    , file_model(new QFileSystemModel)
{
    ui->setupUi(this);
    file_model->setRootPath(QDir::currentPath());
    ui->treeView->setModel(file_model);
    if (!QDir("Game saves").exists()) {
        QDir().mkdir("Game saves");
    }
    ui->treeView->setRootIndex(file_model->index(QDir::currentPath()+"/Game saves/"));

    int id = QFontDatabase::addApplicationFont(":/Font.ttf");
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    ui->LoadButton->setFont(QFont(family));

}

LoadDialog::~LoadDialog()
{
    delete file_model;
    delete ui;
}

void LoadDialog::on_LoadButton_clicked()
{
    QModelIndex index = ui->treeView->currentIndex();
    QFileInfo file_info = file_model->fileInfo(index);
    if (file_info.isFile() && file_info.completeSuffix() == "txt") {
        QFile file(file_info.absoluteFilePath());
        if (CheckTxtFile(file)) {
            QFile loaded_file(file_info.absoluteFilePath());

            if (loaded_file.open(QIODevice::ReadOnly)) {
                QVector<QVector<bool>> loaded_field;
                QTextStream input_stream(&loaded_file);
                while (!input_stream.atEnd()) {
                    QString line = input_stream.readLine();
                    QVector<bool> field_line;
                    for (int i = 0; i < line.length(); ++i) {
                        if (line[i] == QChar('0')) {

                            field_line.push_back(false);

                        } else if (line[i] == QChar('1')) {

                            field_line.push_back(true);

                        }
                    }
                    loaded_field.push_back(field_line);
                    field_line.clear();
                }
                emit FieldLoaded(loaded_field);
                close();
            } else {
                QMessageBox::critical(this, "Open file error!", "Can't open txt file!");
            }

        } else {
            return;
        }
    } else {
        QMessageBox::critical(this, "Read file error", "File must be in txt format!");
    }
}




void LoadDialog::on_treeView_doubleClicked(const QModelIndex &index)
{
    QFileInfo file_info = file_model->fileInfo(index);
    if (file_info.isFile()) {
        if (file_info.suffix() == "txt") {
            QFile file(file_info.absoluteFilePath());
            if (CheckTxtFile(file)) {

                QFile loaded_file(file_info.absoluteFilePath());

                if (loaded_file.open(QIODevice::ReadOnly)) {
                    QVector<QVector<bool>> loaded_field;
                    QTextStream input_stream(&loaded_file);
                    while (!input_stream.atEnd()) {
                        QString line = input_stream.readLine();
                        QVector<bool> field_line;
                        for (int i = 0; i < line.length(); ++i) {
                            if (line[i] == QChar('0')) {

                                field_line.push_back(false);

                            } else if (line[i] == QChar('1')) {

                                field_line.push_back(true);

                            }
                        }
                        loaded_field.push_back(field_line);
                        field_line.clear();
                    }
                    emit FieldLoaded(loaded_field);
                    close();
                } else {
                    QMessageBox::critical(this, "Open file error!", "Can't open txt file!");
                }
            }

        } else {
            QMessageBox::critical(this, "Read file error", "File must be in txt format!");
        }
    }
}

bool LoadDialog::CheckTxtFile(QFile& file)
{
    if (file.open(QIODevice::ReadOnly)) {

        QTextStream input_stream(&file);
        int line_counter = 0;

        while (!input_stream.atEnd()) {
            QString line = input_stream.readLine();
            if(line.length() != FIELD_WIDTH) {
                QMessageBox::critical(this, "File error", "Incorrect number of columns in txt file!");
                return false;
            }
            for (int i = 0; i < line.length(); ++i) {
                if (line[i] != QChar('0') && line[i] != QChar('1')) {
                    QMessageBox::critical(this, "File error", "Incorrect symbols in txt file!");
                    return false;
                }
            }
            ++line_counter;
        }

        if (line_counter != FIELD_HEIGHT) {
            QMessageBox::critical(this, "File error", "Incorrect number of rows in txt file!");
            return false;
        }

        file.close();
        return true;

    } else {
        QMessageBox::critical(this, "Read file error", "Can't read txt file!");
        return false;
    }
}

void LoadDialog::SetFont(QFont* font)
{
    ui->LoadButton->setFont(*font);
    ui->treeView->setFont(*font);
}

