#ifndef NEWMAZEDIALOG_H
#define NEWMAZEDIALOG_H

#include <QDialog>
#include <QIntValidator>
namespace Ui {
class NewMazeDialog;
}

class NewMazeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewMazeDialog(QWidget *parent = 0);
    ~NewMazeDialog();
    int getRow();
    int getCol();

private slots:
    void on_lineEditRow_textEdited(const QString &arg1);

    void on_lineEditCol_textEdited(const QString &arg1);

private:
    Ui::NewMazeDialog *ui;
    QIntValidator *intValidator;
    int row;
    int col;
};

#endif // NEWMAZEDIALOG_H
