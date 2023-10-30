#include <QFontDatabase>

#include "savedialog.h"
#include "ui_savedialog.h"

SaveDialog::SaveDialog(QVector<QVector<bool>>& save_field, QWidget *parent) :
    QDialog(parent)
    , ui(new Ui::SaveDialog)
    , file_model(new QFileSystemModel)
    , save_field(save_field)
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
    ui->SaveButton->setFont(QFont(family));
    ui->label->setFont(QFont(family));
    ui->label_2->setFont(QFont(family));

}

SaveDialog::~SaveDialog()
{
    delete file_model;
    delete ui;
}

void SaveDialog::on_SaveButton_clicked()
{
    if (ui->filenameEdit->text().isEmpty()) {
        QMessageBox::critical(this, "Save file error", "Enter file name!");
    } else {
        QString file_path = QDir::currentPath() + "/Game saves/" + ui->filenameEdit->text() + ".txt";
        QFileInfo file_info(file_path);
        if (file_info.exists()) {
            int reply = QMessageBox::question(this, "Save file error",
                                          "File " + file_info.fileName() + " already exists." +
                                          "Do you want to owerride it?", QMessageBox::Yes, QMessageBox::No);
            if (reply == 0) {

                QFile save_file(file_info.absoluteFilePath());
                if (save_file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {

                    for (auto& line : save_field) {

                    }

                } else {

                    QMessageBox::critical(this, "Open file error!", "Can't open file!");

                }


            } else {

            }
        } else {
            SaveField();
        }
    }
}


void SaveDialog::on_treeView_doubleClicked(const QModelIndex &index)
{
    QFileInfo file_info = file_model->fileInfo(index);
    if (file_info.isFile()) {

        if (file_info.suffix() == "txt") {

            int reply = QMessageBox::question(this, "Save file",
                                          "Are you shure you whant to owerwrite " +
                                              file_info.fileName() + "?", QMessageBox::Yes, QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                QFile save_file(QDir::currentPath() + "/Game saves/" + file_info.fileName());
                save_file.open(QIODevice::WriteOnly);
                QTextStream stream(&save_file);
                for (auto& line : save_field) {
                    for (auto& value : line) {
                        stream << QString::number(value);
                    }
                    stream << "\n";
                }
                save_file.close();
            }

        } else {
            QMessageBox::critical(this, "Save file error", "File must be in txt format!");
        }
    }
}

void SaveDialog::SaveField()
{
    QFile save_file(QDir::currentPath() + "/Game saves/" + ui->filenameEdit->text() + ".txt");
    save_file.open(QIODevice::WriteOnly);
    QTextStream stream(&save_file);
    for (auto& line : save_field) {
        for (auto& value : line) {
            stream << QString::number(value);
        }
        stream << "\n";
    }
    save_file.close();
    close();
}

