/********************************************************************************
** Form generated from reading UI file 'console.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONSOLE_H
#define UI_CONSOLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Console
{
public:
    QGridLayout *gridLayout;
    QPlainTextEdit *plainTextEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QRadioButton *radioButtonASCII;
    QRadioButton *radioButtonHex;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PbStop;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *PbClear;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *PbCloseTerm;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Console)
    {
        if (Console->objectName().isEmpty())
            Console->setObjectName(QStringLiteral("Console"));
        Console->resize(400, 300);
        gridLayout = new QGridLayout(Console);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        plainTextEdit = new QPlainTextEdit(Console);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        gridLayout->addWidget(plainTextEdit, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        radioButtonASCII = new QRadioButton(Console);
        radioButtonASCII->setObjectName(QStringLiteral("radioButtonASCII"));

        horizontalLayout_2->addWidget(radioButtonASCII);

        radioButtonHex = new QRadioButton(Console);
        radioButtonHex->setObjectName(QStringLiteral("radioButtonHex"));

        horizontalLayout_2->addWidget(radioButtonHex);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        PbStop = new QPushButton(Console);
        PbStop->setObjectName(QStringLiteral("PbStop"));

        horizontalLayout->addWidget(PbStop);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        PbClear = new QPushButton(Console);
        PbClear->setObjectName(QStringLiteral("PbClear"));

        horizontalLayout->addWidget(PbClear);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        PbCloseTerm = new QPushButton(Console);
        PbCloseTerm->setObjectName(QStringLiteral("PbCloseTerm"));

        horizontalLayout->addWidget(PbCloseTerm);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);


        retranslateUi(Console);

        QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QWidget *Console)
    {
        Console->setWindowTitle(QApplication::translate("Console", "Console", 0));
        radioButtonASCII->setText(QApplication::translate("Console", "ASCII", 0));
        radioButtonHex->setText(QApplication::translate("Console", "Hex", 0));
        PbStop->setText(QApplication::translate("Console", "Run", 0));
        PbClear->setText(QApplication::translate("Console", "Clear", 0));
        PbCloseTerm->setText(QApplication::translate("Console", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONSOLE_H
