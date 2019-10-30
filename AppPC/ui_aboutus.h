/********************************************************************************
** Form generated from reading UI file 'aboutus.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTUS_H
#define UI_ABOUTUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_AboutUs
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_8;
    QLabel *label_2;
    QLabel *label_9;

    void setupUi(QDialog *AboutUs)
    {
        if (AboutUs->objectName().isEmpty())
            AboutUs->setObjectName(QStringLiteral("AboutUs"));
        AboutUs->resize(361, 167);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/png_leaf.png"), QSize(), QIcon::Normal, QIcon::Off);
        AboutUs->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(AboutUs);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(270, 100, 81, 51));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(AboutUs);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 47, 13));
        label_8 = new QLabel(AboutUs);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 80, 241, 81));
        label_8->setFrameShape(QFrame::Box);
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/image/piflogo.jpg")));
        label_8->setScaledContents(true);
        label_2 = new QLabel(AboutUs);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 0, 251, 81));
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setWordWrap(true);
        label_9 = new QLabel(AboutUs);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(270, 10, 81, 81));
        label_9->setFrameShape(QFrame::Box);
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/image/png_leaf.jpg")));
        label_9->setScaledContents(true);

        retranslateUi(AboutUs);
        QObject::connect(buttonBox, SIGNAL(accepted()), AboutUs, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AboutUs, SLOT(reject()));

        QMetaObject::connectSlotsByName(AboutUs);
    } // setupUi

    void retranslateUi(QDialog *AboutUs)
    {
        AboutUs->setWindowTitle(QApplication::translate("AboutUs", "About us", 0));
        label->setText(QString());
        label_8->setText(QString());
        label_2->setText(QApplication::translate("AboutUs", "This programs is design by Pay it forward club to support competitor in Raise Your ARM 2015 contest.", 0));
        label_9->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class AboutUs: public Ui_AboutUs {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTUS_H
