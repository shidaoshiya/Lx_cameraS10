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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lx_cameraS10Class
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lx_cameraS10Class)
    {
        if (Lx_cameraS10Class->objectName().isEmpty())
            Lx_cameraS10Class->setObjectName(QString::fromUtf8("Lx_cameraS10Class"));
        Lx_cameraS10Class->resize(600, 400);
        menuBar = new QMenuBar(Lx_cameraS10Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        Lx_cameraS10Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lx_cameraS10Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        Lx_cameraS10Class->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lx_cameraS10Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        Lx_cameraS10Class->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lx_cameraS10Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        Lx_cameraS10Class->setStatusBar(statusBar);

        retranslateUi(Lx_cameraS10Class);

        QMetaObject::connectSlotsByName(Lx_cameraS10Class);
    } // setupUi

    void retranslateUi(QMainWindow *Lx_cameraS10Class)
    {
        Lx_cameraS10Class->setWindowTitle(QCoreApplication::translate("Lx_cameraS10Class", "Lx_cameraS10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lx_cameraS10Class: public Ui_Lx_cameraS10Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LX_CAMERAS10_H
