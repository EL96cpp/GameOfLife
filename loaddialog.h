#ifndef LOADDIALOG_H
#define LOADDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QMessageBox>

namespace Ui {
class LoadDialog;
}

class LoadDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoadDialog(QWidget *parent = nullptr);
    ~LoadDialog();

signals:
    void FieldLoaded(QVector<QVector<bool>>& loaded_field);

private slots:
    void on_LoadButton_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void on_DeleteButton_clicked();

private:
    bool CheckTxtFile(QFile& file);
    void SetFont(QFont* font);

private:
    Ui::LoadDialog *ui;
    QFileSystemModel* file_model;
};

#endif // LOADDIALOG_H
