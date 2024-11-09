/********************************************************************************
** Form generated from reading UI file 'Lx_cameraS10.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LX_CAMERAS10_H
#define UI_LX_CAMERAS10_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lx_cameraS10Class
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpinBox *spinBox;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lx_cameraS10Class)
    {
        if (Lx_cameraS10Class->objectName().isEmpty())
            Lx_cameraS10Class->setObjectName(QString::fromUtf8("Lx_cameraS10Class"));
        Lx_cameraS10Class->resize(339, 184);
        centralWidget = new QWidget(Lx_cameraS10Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBox = new QSpinBox(centralWidget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        gridLayout->addWidget(spinBox, 1, 3, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 1, 1, 1);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 2, 1, 1, 3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 3, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 3, 1, 1);

        Lx_cameraS10Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Lx_cameraS10Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 339, 26));
        Lx_cameraS10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lx_cameraS10Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lx_cameraS10Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Lx_cameraS10Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lx_cameraS10Class->setStatusBar(statusBar);

        retranslateUi(Lx_cameraS10Class);

        QMetaObject::connectSlotsByName(Lx_cameraS10Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lx_cameraS10Class)
    {
        Lx_cameraS10Class->setWindowTitle(QCoreApplication::translate("Lx_cameraS10Class", "Lx_cameraS10", nullptr));
        label->setText(QCoreApplication::translate("Lx_cameraS10Class", "\345\255\230\345\233\276\345\274\240\346\225\260\357\274\232", nullptr));
        pushButton->setText(QCoreApplication::translate("Lx_cameraS10Class", "\347\202\271\345\207\273\345\274\200\345\247\213\351\207\207\351\233\206\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lx_cameraS10Class: public Ui_Lx_cameraS10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LX_CAMERAS10_H
