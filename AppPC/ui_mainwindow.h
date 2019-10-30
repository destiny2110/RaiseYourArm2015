/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "imagedisplay.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfigure;
    QAction *actionConnect;
    QAction *actionDisconnect;
    QAction *actionTerminal;
    QAction *actionAbout;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionNew;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_8;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    ImageDisplay *imgDisplay;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QComboBox *cbbCamSelect;
    QPushButton *btnCapture;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnSend;
    QTextBrowser *txtReceive;
    QSlider *slider_blur;
    QLabel *label_11;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QSlider *slider_Hmax;
    QLabel *label_17;
    QLabel *label_15;
    QLabel *label_16;
    QSlider *slider_Smin;
    QLabel *label_12;
    QLabel *label_13;
    QSlider *slider_param1;
    QLabel *label_10;
    QSlider *slider_kernelSize;
    QSlider *slider_Smax;
    QLabel *label_30;
    QLabel *label_18;
    QSlider *slider_blockSize;
    QSlider *slider_Vmax;
    QSlider *slider_Vmin;
    QLabel *label_19;
    QSlider *slider_HHmin;
    QSlider *slider_HHmax;
    QLabel *label_31;
    QLabel *label_34;
    QSlider *slider_SHmin;
    QLabel *label_35;
    QLabel *label_33;
    QSlider *slider_SHmax;
    QSlider *slider_VHmin;
    QSlider *slider_VHmax;
    QLabel *label_32;
    QLabel *label_14;
    QSlider *slider_Hmin;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_3;
    QGridLayout *gridLayout_2;
    QLabel *label_7;
    QSlider *slider_robotMinSize;
    QLabel *label_9;
    QSlider *slider_robotMaxSize;
    QLabel *label_4;
    QSlider *slider_RobotNum;
    QLabel *label_38;
    QSlider *slider_HeadMinSize;
    QLabel *label_37;
    QSlider *slider_HeadMaxSize;
    QLabel *label_36;
    QSlider *slider_HeadNum;
    QLabel *label_6;
    QSlider *slider_giftminSize;
    QLabel *label_53;
    QSlider *slider_giftMaxSize;
    QLabel *label_54;
    QSlider *slider_giftNum;
    QLabel *label_39;
    QLabel *label_40;
    QLabel *R_angle;
    QLabel *R_x;
    QLabel *label_41;
    QLabel *label_42;
    QLabel *R_y;
    QLabel *G_y;
    QLabel *G_angle;
    QLabel *G_x;
    QLabel *label_43;
    QLabel *label_44;
    QLabel *label_45;
    QLabel *label_46;
    QLabel *label_47;
    QLabel *angle;
    QLabel *Blur_label;
    QGroupBox *groupBox;
    QLabel *R_angle2;
    QLabel *label_50;
    QLabel *label_49;
    QLabel *R_angle1;
    QPushButton *btnView;
    QPushButton *btn_resetCUT;
    QLabel *i_label;
    QGroupBox *groupBox_2;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_3;
    QPushButton *btn_pic1;
    QPushButton *btn_pic2;
    QPushButton *btn_pic3;
    QPushButton *btn_pic4;
    QPushButton *btn_pic5;
    QPushButton *btn_pic6;
    QPushButton *btn_pic7;
    QPushButton *btn_pic8;
    QPushButton *btn_pic9;
    QPushButton *btn_pic10;
    QPushButton *btn_debugPIC;
    QGroupBox *groupBox_3;
    QLabel *label_5;
    QSlider *slider_goal;
    QSlider *slider_gift_3;
    QLabel *label_20;
    QSlider *slider_gift_1;
    QSlider *slider_gift_2;
    QLabel *label_21;
    QLabel *label_22;
    QCheckBox *check_gift1;
    QCheckBox *check_gift2;
    QCheckBox *check_gift3;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuSerial_port;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1283, 699);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/png_leaf.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setTabShape(QTabWidget::Rounded);
        actionConfigure = new QAction(MainWindow);
        actionConfigure->setObjectName(QStringLiteral("actionConfigure"));
        actionConnect = new QAction(MainWindow);
        actionConnect->setObjectName(QStringLiteral("actionConnect"));
        actionDisconnect = new QAction(MainWindow);
        actionDisconnect->setObjectName(QStringLiteral("actionDisconnect"));
        actionTerminal = new QAction(MainWindow);
        actionTerminal->setObjectName(QStringLiteral("actionTerminal"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionSaveAs = new QAction(MainWindow);
        actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(9, 9, 16, 16));
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(680, 10, 211, 81));
        label_8->setFrameShape(QFrame::Box);
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/image/piflogo.jpg")));
        label_8->setScaledContents(true);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 10, 642, 582));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        imgDisplay = new ImageDisplay(layoutWidget);
        imgDisplay->setObjectName(QStringLiteral("imgDisplay"));
        imgDisplay->setMinimumSize(QSize(640, 480));
        imgDisplay->setFrameShape(QFrame::Box);

        verticalLayout->addWidget(imgDisplay);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);

        cbbCamSelect = new QComboBox(layoutWidget);
        cbbCamSelect->setObjectName(QStringLiteral("cbbCamSelect"));
        cbbCamSelect->setMinimumSize(QSize(300, 0));

        horizontalLayout_2->addWidget(cbbCamSelect);

        btnCapture = new QPushButton(layoutWidget);
        btnCapture->setObjectName(QStringLiteral("btnCapture"));

        horizontalLayout_2->addWidget(btnCapture);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_2);

        btnSend = new QPushButton(centralWidget);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setGeometry(QRect(1110, 30, 101, 51));
        txtReceive = new QTextBrowser(centralWidget);
        txtReceive->setObjectName(QStringLiteral("txtReceive"));
        txtReceive->setGeometry(QRect(20, 610, 721, 31));
        slider_blur = new QSlider(centralWidget);
        slider_blur->setObjectName(QStringLiteral("slider_blur"));
        slider_blur->setGeometry(QRect(740, 270, 160, 22));
        slider_blur->setMinimum(1);
        slider_blur->setMaximum(15);
        slider_blur->setOrientation(Qt::Horizontal);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(700, 270, 31, 21));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(950, 110, 251, 181));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 232, 432));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        slider_Hmax = new QSlider(scrollAreaWidgetContents);
        slider_Hmax->setObjectName(QStringLiteral("slider_Hmax"));
        slider_Hmax->setMaximum(255);
        slider_Hmax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_Hmax, 1, 1, 1, 3);

        label_17 = new QLabel(scrollAreaWidgetContents);
        label_17->setObjectName(QStringLiteral("label_17"));

        gridLayout->addWidget(label_17, 2, 0, 1, 1);

        label_15 = new QLabel(scrollAreaWidgetContents);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout->addWidget(label_15, 1, 0, 1, 1);

        label_16 = new QLabel(scrollAreaWidgetContents);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout->addWidget(label_16, 3, 0, 1, 1);

        slider_Smin = new QSlider(scrollAreaWidgetContents);
        slider_Smin->setObjectName(QStringLiteral("slider_Smin"));
        slider_Smin->setMaximum(255);
        slider_Smin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_Smin, 2, 1, 1, 3);

        label_12 = new QLabel(scrollAreaWidgetContents);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout->addWidget(label_12, 6, 0, 1, 2);

        label_13 = new QLabel(scrollAreaWidgetContents);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout->addWidget(label_13, 7, 0, 1, 2);

        slider_param1 = new QSlider(scrollAreaWidgetContents);
        slider_param1->setObjectName(QStringLiteral("slider_param1"));
        slider_param1->setMaximum(255);
        slider_param1->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_param1, 7, 3, 1, 1);

        label_10 = new QLabel(scrollAreaWidgetContents);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout->addWidget(label_10, 8, 0, 1, 3);

        slider_kernelSize = new QSlider(scrollAreaWidgetContents);
        slider_kernelSize->setObjectName(QStringLiteral("slider_kernelSize"));
        slider_kernelSize->setMaximum(255);
        slider_kernelSize->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_kernelSize, 8, 3, 1, 1);

        slider_Smax = new QSlider(scrollAreaWidgetContents);
        slider_Smax->setObjectName(QStringLiteral("slider_Smax"));
        slider_Smax->setMinimum(0);
        slider_Smax->setMaximum(255);
        slider_Smax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_Smax, 3, 1, 1, 3);

        label_30 = new QLabel(scrollAreaWidgetContents);
        label_30->setObjectName(QStringLiteral("label_30"));

        gridLayout->addWidget(label_30, 9, 0, 1, 2);

        label_18 = new QLabel(scrollAreaWidgetContents);
        label_18->setObjectName(QStringLiteral("label_18"));

        gridLayout->addWidget(label_18, 4, 0, 1, 1);

        slider_blockSize = new QSlider(scrollAreaWidgetContents);
        slider_blockSize->setObjectName(QStringLiteral("slider_blockSize"));
        slider_blockSize->setMaximum(255);
        slider_blockSize->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_blockSize, 6, 3, 1, 1);

        slider_Vmax = new QSlider(scrollAreaWidgetContents);
        slider_Vmax->setObjectName(QStringLiteral("slider_Vmax"));
        slider_Vmax->setMinimum(0);
        slider_Vmax->setMaximum(255);
        slider_Vmax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_Vmax, 5, 1, 1, 3);

        slider_Vmin = new QSlider(scrollAreaWidgetContents);
        slider_Vmin->setObjectName(QStringLiteral("slider_Vmin"));
        slider_Vmin->setMaximum(255);
        slider_Vmin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_Vmin, 4, 1, 1, 3);

        label_19 = new QLabel(scrollAreaWidgetContents);
        label_19->setObjectName(QStringLiteral("label_19"));

        gridLayout->addWidget(label_19, 5, 0, 1, 1);

        slider_HHmin = new QSlider(scrollAreaWidgetContents);
        slider_HHmin->setObjectName(QStringLiteral("slider_HHmin"));
        slider_HHmin->setMaximum(255);
        slider_HHmin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_HHmin, 9, 2, 1, 2);

        slider_HHmax = new QSlider(scrollAreaWidgetContents);
        slider_HHmax->setObjectName(QStringLiteral("slider_HHmax"));
        slider_HHmax->setMaximum(255);
        slider_HHmax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_HHmax, 10, 2, 1, 2);

        label_31 = new QLabel(scrollAreaWidgetContents);
        label_31->setObjectName(QStringLiteral("label_31"));

        gridLayout->addWidget(label_31, 12, 0, 1, 2);

        label_34 = new QLabel(scrollAreaWidgetContents);
        label_34->setObjectName(QStringLiteral("label_34"));

        gridLayout->addWidget(label_34, 13, 0, 1, 2);

        slider_SHmin = new QSlider(scrollAreaWidgetContents);
        slider_SHmin->setObjectName(QStringLiteral("slider_SHmin"));
        slider_SHmin->setMaximum(255);
        slider_SHmin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_SHmin, 11, 2, 1, 2);

        label_35 = new QLabel(scrollAreaWidgetContents);
        label_35->setObjectName(QStringLiteral("label_35"));

        gridLayout->addWidget(label_35, 10, 0, 1, 2);

        label_33 = new QLabel(scrollAreaWidgetContents);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout->addWidget(label_33, 11, 0, 1, 2);

        slider_SHmax = new QSlider(scrollAreaWidgetContents);
        slider_SHmax->setObjectName(QStringLiteral("slider_SHmax"));
        slider_SHmax->setMinimum(0);
        slider_SHmax->setMaximum(255);
        slider_SHmax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_SHmax, 12, 2, 1, 2);

        slider_VHmin = new QSlider(scrollAreaWidgetContents);
        slider_VHmin->setObjectName(QStringLiteral("slider_VHmin"));
        slider_VHmin->setMaximum(255);
        slider_VHmin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_VHmin, 13, 2, 1, 2);

        slider_VHmax = new QSlider(scrollAreaWidgetContents);
        slider_VHmax->setObjectName(QStringLiteral("slider_VHmax"));
        slider_VHmax->setMinimum(0);
        slider_VHmax->setMaximum(255);
        slider_VHmax->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_VHmax, 14, 2, 1, 2);

        label_32 = new QLabel(scrollAreaWidgetContents);
        label_32->setObjectName(QStringLiteral("label_32"));

        gridLayout->addWidget(label_32, 14, 0, 1, 2);

        label_14 = new QLabel(scrollAreaWidgetContents);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout->addWidget(label_14, 0, 0, 1, 1);

        slider_Hmin = new QSlider(scrollAreaWidgetContents);
        slider_Hmin->setObjectName(QStringLiteral("slider_Hmin"));
        slider_Hmin->setMaximum(255);
        slider_Hmin->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(slider_Hmin, 0, 1, 1, 3);

        scrollArea->setWidget(scrollAreaWidgetContents);
        slider_Hmax->raise();
        label_18->raise();
        slider_Smax->raise();
        label_17->raise();
        label_14->raise();
        label_19->raise();
        slider_Hmin->raise();
        slider_Vmax->raise();
        slider_Vmin->raise();
        label_16->raise();
        label_15->raise();
        slider_Smin->raise();
        slider_kernelSize->raise();
        slider_param1->raise();
        label_12->raise();
        label_13->raise();
        slider_blockSize->raise();
        label_10->raise();
        slider_HHmin->raise();
        slider_SHmin->raise();
        slider_VHmax->raise();
        slider_VHmin->raise();
        slider_HHmax->raise();
        slider_SHmax->raise();
        label_30->raise();
        label_31->raise();
        label_32->raise();
        label_33->raise();
        label_34->raise();
        label_35->raise();
        scrollArea_2 = new QScrollArea(centralWidget);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(700, 110, 221, 91));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 202, 264));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_7 = new QLabel(scrollAreaWidgetContents_3);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 0, 1, 1);

        slider_robotMinSize = new QSlider(scrollAreaWidgetContents_3);
        slider_robotMinSize->setObjectName(QStringLiteral("slider_robotMinSize"));
        slider_robotMinSize->setMaximum(3000);
        slider_robotMinSize->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_robotMinSize, 0, 1, 1, 1);

        label_9 = new QLabel(scrollAreaWidgetContents_3);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        slider_robotMaxSize = new QSlider(scrollAreaWidgetContents_3);
        slider_robotMaxSize->setObjectName(QStringLiteral("slider_robotMaxSize"));
        slider_robotMaxSize->setMaximum(4000);
        slider_robotMaxSize->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_robotMaxSize, 1, 1, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        slider_RobotNum = new QSlider(scrollAreaWidgetContents_3);
        slider_RobotNum->setObjectName(QStringLiteral("slider_RobotNum"));
        slider_RobotNum->setMaximum(100);
        slider_RobotNum->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_RobotNum, 2, 1, 1, 1);

        label_38 = new QLabel(scrollAreaWidgetContents_3);
        label_38->setObjectName(QStringLiteral("label_38"));

        gridLayout_2->addWidget(label_38, 3, 0, 1, 1);

        slider_HeadMinSize = new QSlider(scrollAreaWidgetContents_3);
        slider_HeadMinSize->setObjectName(QStringLiteral("slider_HeadMinSize"));
        slider_HeadMinSize->setMaximum(3000);
        slider_HeadMinSize->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_HeadMinSize, 3, 1, 1, 1);

        label_37 = new QLabel(scrollAreaWidgetContents_3);
        label_37->setObjectName(QStringLiteral("label_37"));

        gridLayout_2->addWidget(label_37, 4, 0, 1, 1);

        slider_HeadMaxSize = new QSlider(scrollAreaWidgetContents_3);
        slider_HeadMaxSize->setObjectName(QStringLiteral("slider_HeadMaxSize"));
        slider_HeadMaxSize->setMaximum(4000);
        slider_HeadMaxSize->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_HeadMaxSize, 4, 1, 1, 1);

        label_36 = new QLabel(scrollAreaWidgetContents_3);
        label_36->setObjectName(QStringLiteral("label_36"));

        gridLayout_2->addWidget(label_36, 5, 0, 1, 1);

        slider_HeadNum = new QSlider(scrollAreaWidgetContents_3);
        slider_HeadNum->setObjectName(QStringLiteral("slider_HeadNum"));
        slider_HeadNum->setMaximum(100);
        slider_HeadNum->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_HeadNum, 5, 1, 1, 1);

        label_6 = new QLabel(scrollAreaWidgetContents_3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 6, 0, 1, 1);

        slider_giftminSize = new QSlider(scrollAreaWidgetContents_3);
        slider_giftminSize->setObjectName(QStringLiteral("slider_giftminSize"));
        slider_giftminSize->setMaximum(7000);
        slider_giftminSize->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_giftminSize, 6, 1, 1, 1);

        label_53 = new QLabel(scrollAreaWidgetContents_3);
        label_53->setObjectName(QStringLiteral("label_53"));

        gridLayout_2->addWidget(label_53, 7, 0, 1, 1);

        slider_giftMaxSize = new QSlider(scrollAreaWidgetContents_3);
        slider_giftMaxSize->setObjectName(QStringLiteral("slider_giftMaxSize"));
        slider_giftMaxSize->setMaximum(8000);
        slider_giftMaxSize->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_giftMaxSize, 7, 1, 1, 1);

        label_54 = new QLabel(scrollAreaWidgetContents_3);
        label_54->setObjectName(QStringLiteral("label_54"));

        gridLayout_2->addWidget(label_54, 8, 0, 1, 1);

        slider_giftNum = new QSlider(scrollAreaWidgetContents_3);
        slider_giftNum->setObjectName(QStringLiteral("slider_giftNum"));
        slider_giftNum->setMaximum(100);
        slider_giftNum->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(slider_giftNum, 8, 1, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_3);
        label_39 = new QLabel(centralWidget);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(680, 350, 41, 21));
        label_40 = new QLabel(centralWidget);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(690, 320, 41, 31));
        label_40->setLineWidth(2);
        R_angle = new QLabel(centralWidget);
        R_angle->setObjectName(QStringLiteral("R_angle"));
        R_angle->setGeometry(QRect(720, 350, 41, 21));
        R_x = new QLabel(centralWidget);
        R_x->setObjectName(QStringLiteral("R_x"));
        R_x->setGeometry(QRect(800, 350, 21, 21));
        label_41 = new QLabel(centralWidget);
        label_41->setObjectName(QStringLiteral("label_41"));
        label_41->setGeometry(QRect(780, 350, 16, 21));
        label_42 = new QLabel(centralWidget);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(840, 350, 16, 21));
        R_y = new QLabel(centralWidget);
        R_y->setObjectName(QStringLiteral("R_y"));
        R_y->setGeometry(QRect(860, 350, 21, 21));
        G_y = new QLabel(centralWidget);
        G_y->setObjectName(QStringLiteral("G_y"));
        G_y->setGeometry(QRect(860, 400, 21, 21));
        G_angle = new QLabel(centralWidget);
        G_angle->setObjectName(QStringLiteral("G_angle"));
        G_angle->setGeometry(QRect(720, 400, 41, 21));
        G_x = new QLabel(centralWidget);
        G_x->setObjectName(QStringLiteral("G_x"));
        G_x->setGeometry(QRect(800, 400, 21, 21));
        label_43 = new QLabel(centralWidget);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(690, 370, 41, 31));
        label_43->setLineWidth(2);
        label_44 = new QLabel(centralWidget);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(680, 400, 41, 21));
        label_45 = new QLabel(centralWidget);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(840, 400, 16, 21));
        label_46 = new QLabel(centralWidget);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(780, 400, 16, 21));
        label_47 = new QLabel(centralWidget);
        label_47->setObjectName(QStringLiteral("label_47"));
        label_47->setGeometry(QRect(700, 450, 51, 31));
        label_47->setLineWidth(2);
        angle = new QLabel(centralWidget);
        angle->setObjectName(QStringLiteral("angle"));
        angle->setGeometry(QRect(760, 450, 41, 31));
        Blur_label = new QLabel(centralWidget);
        Blur_label->setObjectName(QStringLiteral("Blur_label"));
        Blur_label->setGeometry(QRect(790, 260, 47, 13));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(910, 320, 151, 81));
        R_angle2 = new QLabel(groupBox);
        R_angle2->setObjectName(QStringLiteral("R_angle2"));
        R_angle2->setGeometry(QRect(90, 50, 51, 21));
        label_50 = new QLabel(groupBox);
        label_50->setObjectName(QStringLiteral("label_50"));
        label_50->setGeometry(QRect(100, 20, 31, 31));
        label_50->setLineWidth(2);
        label_49 = new QLabel(groupBox);
        label_49->setObjectName(QStringLiteral("label_49"));
        label_49->setGeometry(QRect(30, 20, 21, 31));
        label_49->setLineWidth(2);
        R_angle1 = new QLabel(groupBox);
        R_angle1->setObjectName(QStringLiteral("R_angle1"));
        R_angle1->setGeometry(QRect(20, 50, 51, 21));
        btnView = new QPushButton(centralWidget);
        btnView->setObjectName(QStringLiteral("btnView"));
        btnView->setGeometry(QRect(950, 20, 131, 61));
        btn_resetCUT = new QPushButton(centralWidget);
        btn_resetCUT->setObjectName(QStringLiteral("btn_resetCUT"));
        btn_resetCUT->setGeometry(QRect(690, 510, 91, 41));
        i_label = new QLabel(centralWidget);
        i_label->setObjectName(QStringLiteral("i_label"));
        i_label->setGeometry(QRect(790, 520, 31, 16));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(1100, 320, 161, 181));
        scrollArea_3 = new QScrollArea(groupBox_2);
        scrollArea_3->setObjectName(QStringLiteral("scrollArea_3"));
        scrollArea_3->setGeometry(QRect(20, 70, 121, 101));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 102, 302));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        btn_pic1 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic1->setObjectName(QStringLiteral("btn_pic1"));

        gridLayout_3->addWidget(btn_pic1, 0, 0, 1, 1);

        btn_pic2 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic2->setObjectName(QStringLiteral("btn_pic2"));

        gridLayout_3->addWidget(btn_pic2, 1, 0, 1, 1);

        btn_pic3 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic3->setObjectName(QStringLiteral("btn_pic3"));

        gridLayout_3->addWidget(btn_pic3, 2, 0, 1, 1);

        btn_pic4 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic4->setObjectName(QStringLiteral("btn_pic4"));

        gridLayout_3->addWidget(btn_pic4, 3, 0, 1, 1);

        btn_pic5 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic5->setObjectName(QStringLiteral("btn_pic5"));

        gridLayout_3->addWidget(btn_pic5, 4, 0, 1, 1);

        btn_pic6 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic6->setObjectName(QStringLiteral("btn_pic6"));

        gridLayout_3->addWidget(btn_pic6, 5, 0, 1, 1);

        btn_pic7 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic7->setObjectName(QStringLiteral("btn_pic7"));

        gridLayout_3->addWidget(btn_pic7, 6, 0, 1, 1);

        btn_pic8 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic8->setObjectName(QStringLiteral("btn_pic8"));

        gridLayout_3->addWidget(btn_pic8, 7, 0, 1, 1);

        btn_pic9 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic9->setObjectName(QStringLiteral("btn_pic9"));

        gridLayout_3->addWidget(btn_pic9, 8, 0, 1, 1);

        btn_pic10 = new QPushButton(scrollAreaWidgetContents_2);
        btn_pic10->setObjectName(QStringLiteral("btn_pic10"));

        gridLayout_3->addWidget(btn_pic10, 9, 0, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_2);
        btn_debugPIC = new QPushButton(groupBox_2);
        btn_debugPIC->setObjectName(QStringLiteral("btn_debugPIC"));
        btn_debugPIC->setGeometry(QRect(20, 20, 121, 31));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(830, 450, 231, 171));
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 30, 31, 16));
        slider_goal = new QSlider(groupBox_3);
        slider_goal->setObjectName(QStringLiteral("slider_goal"));
        slider_goal->setGeometry(QRect(40, 30, 91, 22));
        slider_goal->setMaximum(500);
        slider_goal->setOrientation(Qt::Horizontal);
        slider_gift_3 = new QSlider(groupBox_3);
        slider_gift_3->setObjectName(QStringLiteral("slider_gift_3"));
        slider_gift_3->setGeometry(QRect(110, 61, 22, 84));
        slider_gift_3->setMaximum(500);
        slider_gift_3->setOrientation(Qt::Vertical);
        label_20 = new QLabel(groupBox_3);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(10, 151, 23, 16));
        slider_gift_1 = new QSlider(groupBox_3);
        slider_gift_1->setObjectName(QStringLiteral("slider_gift_1"));
        slider_gift_1->setGeometry(QRect(10, 61, 22, 84));
        slider_gift_1->setMaximum(500);
        slider_gift_1->setOrientation(Qt::Vertical);
        slider_gift_2 = new QSlider(groupBox_3);
        slider_gift_2->setObjectName(QStringLiteral("slider_gift_2"));
        slider_gift_2->setGeometry(QRect(60, 61, 22, 84));
        slider_gift_2->setMaximum(500);
        slider_gift_2->setOrientation(Qt::Vertical);
        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(60, 151, 23, 16));
        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(110, 151, 23, 16));
        check_gift1 = new QCheckBox(groupBox_3);
        check_gift1->setObjectName(QStringLiteral("check_gift1"));
        check_gift1->setGeometry(QRect(150, 60, 51, 17));
        check_gift2 = new QCheckBox(groupBox_3);
        check_gift2->setObjectName(QStringLiteral("check_gift2"));
        check_gift2->setGeometry(QRect(150, 90, 51, 17));
        check_gift3 = new QCheckBox(groupBox_3);
        check_gift3->setObjectName(QStringLiteral("check_gift3"));
        check_gift3->setGeometry(QRect(150, 120, 51, 17));
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1283, 21));
        menuSerial_port = new QMenu(menuBar);
        menuSerial_port->setObjectName(QStringLiteral("menuSerial_port"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuSerial_port->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuSerial_port->addAction(actionConfigure);
        menuSerial_port->addSeparator();
        menuSerial_port->addAction(actionConnect);
        menuSerial_port->addAction(actionDisconnect);
        menuSerial_port->addSeparator();
        menuSerial_port->addAction(actionTerminal);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "RYA 2015", 0));
        actionConfigure->setText(QApplication::translate("MainWindow", "Configure", 0));
        actionConnect->setText(QApplication::translate("MainWindow", "Connect", 0));
        actionDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0));
        actionTerminal->setText(QApplication::translate("MainWindow", "Console", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionSaveAs->setText(QApplication::translate("MainWindow", "Save As", 0));
        actionNew->setText(QApplication::translate("MainWindow", "New", 0));
        label->setText(QString());
        label_8->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Frame:", 0));
        imgDisplay->setText(QApplication::translate("MainWindow", "Display image here", 0));
        label_3->setText(QApplication::translate("MainWindow", "Input devices:", 0));
        btnCapture->setText(QApplication::translate("MainWindow", "Capture", 0));
        btnSend->setText(QApplication::translate("MainWindow", "START SEND", 0));
        label_11->setText(QApplication::translate("MainWindow", "Blur", 0));
        label_17->setText(QApplication::translate("MainWindow", "Smin", 0));
        label_15->setText(QApplication::translate("MainWindow", "Hmax", 0));
        label_16->setText(QApplication::translate("MainWindow", "Smax", 0));
        label_12->setText(QApplication::translate("MainWindow", "Block_Size", 0));
        label_13->setText(QApplication::translate("MainWindow", "Param_1", 0));
        label_10->setText(QApplication::translate("MainWindow", "Kernel_Size", 0));
        label_30->setText(QApplication::translate("MainWindow", "H_Hmin", 0));
        label_18->setText(QApplication::translate("MainWindow", "Vmin", 0));
        label_19->setText(QApplication::translate("MainWindow", "Vmax", 0));
        label_31->setText(QApplication::translate("MainWindow", "S_Hmax", 0));
        label_34->setText(QApplication::translate("MainWindow", "V_Hmin", 0));
        label_35->setText(QApplication::translate("MainWindow", "H_Hmax", 0));
        label_33->setText(QApplication::translate("MainWindow", "S_Hmin", 0));
        label_32->setText(QApplication::translate("MainWindow", "V_Hmax", 0));
        label_14->setText(QApplication::translate("MainWindow", "Hmin", 0));
        label_7->setText(QApplication::translate("MainWindow", "Robot_MinSize", 0));
        label_9->setText(QApplication::translate("MainWindow", "Robot_MaxSize", 0));
        label_4->setText(QApplication::translate("MainWindow", "Robot_Num", 0));
        label_38->setText(QApplication::translate("MainWindow", "Head_MinSize", 0));
        label_37->setText(QApplication::translate("MainWindow", "Head_MaxSize", 0));
        label_36->setText(QApplication::translate("MainWindow", "Head_Num", 0));
        label_6->setText(QApplication::translate("MainWindow", "Gift_MinSize", 0));
        label_53->setText(QApplication::translate("MainWindow", "Gift_MaxSize", 0));
        label_54->setText(QApplication::translate("MainWindow", "Gift_Num", 0));
        label_39->setText(QApplication::translate("MainWindow", "Angle::", 0));
        label_40->setText(QApplication::translate("MainWindow", "ROBOT", 0));
        R_angle->setText(QApplication::translate("MainWindow", "R_Angle", 0));
        R_x->setText(QApplication::translate("MainWindow", "R_x", 0));
        label_41->setText(QApplication::translate("MainWindow", "X::", 0));
        label_42->setText(QApplication::translate("MainWindow", "Y::", 0));
        R_y->setText(QApplication::translate("MainWindow", "R_y", 0));
        G_y->setText(QApplication::translate("MainWindow", "G_y", 0));
        G_angle->setText(QApplication::translate("MainWindow", "G_Angle", 0));
        G_x->setText(QApplication::translate("MainWindow", "G_x", 0));
        label_43->setText(QApplication::translate("MainWindow", "GIFT", 0));
        label_44->setText(QApplication::translate("MainWindow", "Angle::", 0));
        label_45->setText(QApplication::translate("MainWindow", "Y::", 0));
        label_46->setText(QApplication::translate("MainWindow", "X::", 0));
        label_47->setText(QApplication::translate("MainWindow", "*ANGLE*", 0));
        angle->setText(QApplication::translate("MainWindow", "angle", 0));
        Blur_label->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "ROBOT_think::", 0));
        R_angle2->setText(QApplication::translate("MainWindow", "R_Angle2", 0));
        label_50->setText(QApplication::translate("MainWindow", "Right", 0));
        label_49->setText(QApplication::translate("MainWindow", "Left", 0));
        R_angle1->setText(QApplication::translate("MainWindow", "R_Angle1", 0));
        btnView->setText(QApplication::translate("MainWindow", "START VIEW", 0));
        btn_resetCUT->setText(QApplication::translate("MainWindow", "Reset FrameCUT", 0));
        i_label->setText(QApplication::translate("MainWindow", "0", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "DebugPIC::", 0));
        btn_pic1->setText(QApplication::translate("MainWindow", "PIC_1", 0));
        btn_pic2->setText(QApplication::translate("MainWindow", "PIC_2", 0));
        btn_pic3->setText(QApplication::translate("MainWindow", "PIC_3", 0));
        btn_pic4->setText(QApplication::translate("MainWindow", "PIC_4", 0));
        btn_pic5->setText(QApplication::translate("MainWindow", "PIC_5", 0));
        btn_pic6->setText(QApplication::translate("MainWindow", "PIC_6", 0));
        btn_pic7->setText(QApplication::translate("MainWindow", "PIC_7", 0));
        btn_pic8->setText(QApplication::translate("MainWindow", "PIC_8", 0));
        btn_pic9->setText(QApplication::translate("MainWindow", "PIC_9", 0));
        btn_pic10->setText(QApplication::translate("MainWindow", "PIC_10", 0));
        btn_debugPIC->setText(QApplication::translate("MainWindow", "DebugPIC", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "TARGET_SCALE::", 0));
        label_5->setText(QApplication::translate("MainWindow", "Goal", 0));
        label_20->setText(QApplication::translate("MainWindow", "Gift1", 0));
        label_21->setText(QApplication::translate("MainWindow", "Gift2", 0));
        label_22->setText(QApplication::translate("MainWindow", "Gift3", 0));
        check_gift1->setText(QApplication::translate("MainWindow", "Gift1", 0));
        check_gift2->setText(QApplication::translate("MainWindow", "Gift2", 0));
        check_gift3->setText(QApplication::translate("MainWindow", "Gift3", 0));
        menuSerial_port->setTitle(QApplication::translate("MainWindow", "Serial port", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
