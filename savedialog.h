#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QMessageBox>
#include <QVector>
#include <QTextStream>
#include <QDebug>

namespace Ui {
class SaveDialog;
}

class SaveDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveDialog(QVector<QVector<bool>>& save_field, QWidget *parent = nullptr);
    ~SaveDialog();

private slots:
    void on_SaveButton_clicked();

    void on_treeView_doubleClicked(const QModelIndex &index);

    void SaveField();

private:
    Ui::SaveDialog *ui;
    QFileSystemModel* file_model;
    QVector<QVector<bool>> save_field;
};

#endif // SAVEDIALOG_H
