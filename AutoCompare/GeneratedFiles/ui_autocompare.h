/********************************************************************************
** Form generated from reading UI file 'autocompare.ui'
**
** Created: Fri Oct 7 16:20:27 2016
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOCOMPARE_H
#define UI_AUTOCOMPARE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDockWidget>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoCompareClass
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *action;
    QAction *actionSort1;
    QAction *actionSort2;
    QAction *actionSav_as_img;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSort;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;

    void setupUi(QMainWindow *AutoCompareClass)
    {
        if (AutoCompareClass->objectName().isEmpty())
            AutoCompareClass->setObjectName(QString::fromUtf8("AutoCompareClass"));
        AutoCompareClass->resize(735, 401);
        actionOpen = new QAction(AutoCompareClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(AutoCompareClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        action = new QAction(AutoCompareClass);
        action->setObjectName(QString::fromUtf8("action"));
        actionSort1 = new QAction(AutoCompareClass);
        actionSort1->setObjectName(QString::fromUtf8("actionSort1"));
        actionSort2 = new QAction(AutoCompareClass);
        actionSort2->setObjectName(QString::fromUtf8("actionSort2"));
        actionSav_as_img = new QAction(AutoCompareClass);
        actionSav_as_img->setObjectName(QString::fromUtf8("actionSav_as_img"));
        centralWidget = new QWidget(AutoCompareClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        AutoCompareClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AutoCompareClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 735, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSort = new QMenu(menuBar);
        menuSort->setObjectName(QString::fromUtf8("menuSort"));
        AutoCompareClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(AutoCompareClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        AutoCompareClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(AutoCompareClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AutoCompareClass->setStatusBar(statusBar);
        dockWidget = new QDockWidget(AutoCompareClass);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidget->setWidget(dockWidgetContents);
        AutoCompareClass->addDockWidget(static_cast<Qt::DockWidgetArea>(1), dockWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSort->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuSort->addAction(actionSort1);
        menuSort->addAction(actionSort2);

        retranslateUi(AutoCompareClass);

        QMetaObject::connectSlotsByName(AutoCompareClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoCompareClass)
    {
        AutoCompareClass->setWindowTitle(QApplication::translate("AutoCompareClass", "AutoCompare", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("AutoCompareClass", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("AutoCompareClass", "Save", 0, QApplication::UnicodeUTF8));
        action->setText(QApplication::translate("AutoCompareClass", "xit", 0, QApplication::UnicodeUTF8));
        actionSort1->setText(QApplication::translate("AutoCompareClass", "Sort1", 0, QApplication::UnicodeUTF8));
        actionSort2->setText(QApplication::translate("AutoCompareClass", "Sort2", 0, QApplication::UnicodeUTF8));
        actionSav_as_img->setText(QApplication::translate("AutoCompareClass", "Sav as img", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("AutoCompareClass", "File", 0, QApplication::UnicodeUTF8));
        menuSort->setTitle(QApplication::translate("AutoCompareClass", "Sort", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AutoCompareClass: public Ui_AutoCompareClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOCOMPARE_H
