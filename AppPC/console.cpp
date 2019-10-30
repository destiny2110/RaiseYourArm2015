#include "console.h"
#include "ui_console.h"
#include <QScrollBar>
#include <QtCore/QDebug>

QT_USE_NAMESPACE

Console::Console(QWidget *parent) :
    QDialog(parent),
    localEchoEnabled(false),
    ui(new Ui::Console)
{
    ui->setupUi(this);
    ui->plainTextEdit->document()->setMaximumBlockCount(100);
    QPalette p = palette();
    p.setColor(QPalette::Base,Qt::black);
    p.setColor(QPalette::Text,Qt::white);
    ui->plainTextEdit->setPalette(p);

    consoleState = STOP;
    ui->radioButtonASCII->setChecked(true);
    ui->radioButtonHex->setChecked(false);
}

Console::~Console()
{
    delete ui;
}
void Console::putData(const char* data,int size)
{
    if (consoleState == RUNNING)
    {
        if (isAscii)
            ui->plainTextEdit->insertPlainText(QString(data));
        else
        {
            QByteArray array = QByteArray::fromRawData(data,size);
            ui->plainTextEdit->insertPlainText(QString(array.toHex()));
        }
        QScrollBar *bar = ui->plainTextEdit->verticalScrollBar();
        bar->setValue(bar->maximum());
    }
}
void Console::setLocalEchoEnabled(bool set)
{
    localEchoEnabled = set;
}
//void Console::keyPressEvent(QKeyEvent *e)
//{
//    switch (e->key()) {
//    case Qt::Key_Backspace:
//    case Qt::Key_Left:
//    case Qt::Key_Right:
//    case Qt::Key_Up:
//    case Qt::Key_Down:
//        break;
//    default:
//        if (localEchoEnabled)
//            QPlainTextEdit::keyPressEvent(e);
//        emit getData(e->text().toLocal8Bit());
//    }
//}
//void Console::mousePressEvent(QMouseEvent *e)
//{
//    Q_UNUSED(e)
//    setFocus();
//}

void Console::on_radioButtonASCII_clicked()
{
    if (ui->radioButtonASCII->isChecked())
        isAscii = true;
}

void Console::on_radioButtonHex_clicked()
{
    if (ui->radioButtonHex->isChecked())
        isAscii = false;
}

//void Console::on_PbPause_clicked()
//{
//    switch (consoleState)
//    {
//    case RUNNING:
//    {
//        consoleState = PAUSE;
//        break;
//    }
//    case PAUSE:
//    {
//        if (consoleState == PAUSE)
//            consoleState = RUNNING;
//        break;
//    }
//    }
//}

void Console::on_PbStop_clicked()
{
    switch (consoleState)
    {
    case RUNNING:
    case PAUSE:
    {
        consoleState = STOP;
        ui->PbStop->setText("Run");
        break;
    }
    case STOP:
    {
        consoleState = RUNNING;
        ui->PbStop->setText("Stop");
        break;
    }
    }
}

void Console::on_PbClear_clicked()
{
    ui->plainTextEdit->setPlainText("");
}

void Console::on_PbCloseTerm_clicked()
{
    this->close();
}
