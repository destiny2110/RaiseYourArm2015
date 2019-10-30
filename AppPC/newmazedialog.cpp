#include "newmazedialog.h"
#include "ui_newmazedialog.h"

NewMazeDialog::NewMazeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewMazeDialog)
{
    ui->setupUi(this);
    intValidator = new QIntValidator(1,15,this);
}

NewMazeDialog::~NewMazeDialog()
{
    delete ui;
}

void NewMazeDialog::on_lineEditRow_textEdited(const QString &arg1)
{
    ui->lineEditRow->setValidator(intValidator);
}

void NewMazeDialog::on_lineEditCol_textEdited(const QString &arg1)
{
    ui->lineEditCol->setValidator(intValidator);
}
int NewMazeDialog::getCol()
{
    return ui->lineEditCol->text().toInt();
}
int NewMazeDialog::getRow()
{
    return ui->lineEditRow->text().toInt();
}
