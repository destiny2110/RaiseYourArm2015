#ifndef CONSOLE_H
#define CONSOLE_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QScrollBar>
#include <QtCore/QDebug>
QT_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui {
class Console;

}
QT_END_NAMESPACE

typedef enum{
    PAUSE,
    STOP,
    RUNNING
} ConsoleState;

class Console : public QDialog
{
    Q_OBJECT

public:
    explicit Console(QWidget *parent = 0);
    ~Console();
    void putData(const char* data,int size);

    void setLocalEchoEnabled(bool set);
signals:
    void getData(const QByteArray &data);
private slots:
    void on_radioButtonASCII_clicked();

    void on_radioButtonHex_clicked();

    void on_PbStop_clicked();

    void on_PbClear_clicked();

    void on_PbCloseTerm_clicked();

private:
    Ui::Console *ui;
    bool localEchoEnabled;
    bool isAscii;
    ConsoleState consoleState;
};

#endif // CONSOLE_H
