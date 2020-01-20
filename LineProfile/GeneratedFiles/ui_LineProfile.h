/********************************************************************************
** Form generated from reading UI file 'LineProfile.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LINEPROFILE_H
#define UI_LINEPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LineProfileClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LineProfileClass)
    {
        if (LineProfileClass->objectName().isEmpty())
            LineProfileClass->setObjectName(QString::fromUtf8("LineProfileClass"));
        LineProfileClass->resize(600, 400);
        menuBar = new QMenuBar(LineProfileClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        LineProfileClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LineProfileClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LineProfileClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(LineProfileClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        LineProfileClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(LineProfileClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LineProfileClass->setStatusBar(statusBar);

        retranslateUi(LineProfileClass);

        QMetaObject::connectSlotsByName(LineProfileClass);
    } // setupUi

    void retranslateUi(QMainWindow *LineProfileClass)
    {
        LineProfileClass->setWindowTitle(QApplication::translate("LineProfileClass", "LineProfile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LineProfileClass: public Ui_LineProfileClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LINEPROFILE_H
