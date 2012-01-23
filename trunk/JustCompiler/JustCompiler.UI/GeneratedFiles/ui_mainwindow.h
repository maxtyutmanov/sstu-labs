/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 22. Jan 23:45:06 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *translateAction;
    QAction *action_3;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QTextEdit *sourceTxt;
    QTextBrowser *outputTxt;
    QTreeWidget *parseTreeView;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(749, 400);
        translateAction = new QAction(MainWindowClass);
        translateAction->setObjectName(QString::fromUtf8("translateAction"));
        action_3 = new QAction(MainWindowClass);
        action_3->setObjectName(QString::fromUtf8("action_3"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        sourceTxt = new QTextEdit(centralWidget);
        sourceTxt->setObjectName(QString::fromUtf8("sourceTxt"));
        QFont font;
        font.setPointSize(10);
        sourceTxt->setFont(font);

        gridLayout_2->addWidget(sourceTxt, 0, 0, 1, 1);

        outputTxt = new QTextBrowser(centralWidget);
        outputTxt->setObjectName(QString::fromUtf8("outputTxt"));
        outputTxt->setFont(font);

        gridLayout_2->addWidget(outputTxt, 1, 0, 1, 1);

        parseTreeView = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        parseTreeView->setHeaderItem(__qtreewidgetitem);
        parseTreeView->setObjectName(QString::fromUtf8("parseTreeView"));
        parseTreeView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        parseTreeView->header()->setVisible(true);

        gridLayout_2->addWidget(parseTreeView, 0, 1, 2, 1);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 749, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(translateAction);
        menu->addSeparator();
        menu->addAction(action_3);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "\320\242\321\200\320\260\320\275\321\201\320\273\321\217\321\202\320\276\321\200", 0, QApplication::UnicodeUTF8));
        translateAction->setText(QApplication::translate("MainWindowClass", "\320\242\321\200\320\260\320\275\321\201\320\273\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0, QApplication::UnicodeUTF8));
        action_3->setText(QApplication::translate("MainWindowClass", "\320\222\321\213\321\205\320\276\320\264", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindowClass", "\320\244\320\260\320\271\320\273", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
