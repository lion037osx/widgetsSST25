/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton_exit;
    QPushButton *pushButton_folder;
    QPushButton *pushButton_write;
    QLabel *label_debug;
    QPushButton *pushButton_uart;
    QProgressBar *progressBar;
    QPlainTextEdit *plainTextEdit_uart;
    QLabel *label;
    QPushButton *pushButton_clearScreen;
    QPushButton *pushButton_RTS;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(990, 460);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton_exit = new QPushButton(centralWidget);
        pushButton_exit->setObjectName(QStringLiteral("pushButton_exit"));
        pushButton_exit->setGeometry(QRect(870, 310, 101, 61));
        pushButton_folder = new QPushButton(centralWidget);
        pushButton_folder->setObjectName(QStringLiteral("pushButton_folder"));
        pushButton_folder->setGeometry(QRect(10, 30, 101, 61));
        pushButton_write = new QPushButton(centralWidget);
        pushButton_write->setObjectName(QStringLiteral("pushButton_write"));
        pushButton_write->setGeometry(QRect(870, 110, 101, 61));
        label_debug = new QLabel(centralWidget);
        label_debug->setObjectName(QStringLiteral("label_debug"));
        label_debug->setGeometry(QRect(10, 0, 811, 21));
        pushButton_uart = new QPushButton(centralWidget);
        pushButton_uart->setObjectName(QStringLiteral("pushButton_uart"));
        pushButton_uart->setGeometry(QRect(870, 30, 101, 61));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(250, 330, 331, 31));
        progressBar->setValue(24);
        plainTextEdit_uart = new QPlainTextEdit(centralWidget);
        plainTextEdit_uart->setObjectName(QStringLiteral("plainTextEdit_uart"));
        plainTextEdit_uart->setGeometry(QRect(120, 30, 731, 261));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 240, 57, 14));
        pushButton_clearScreen = new QPushButton(centralWidget);
        pushButton_clearScreen->setObjectName(QStringLiteral("pushButton_clearScreen"));
        pushButton_clearScreen->setGeometry(QRect(870, 190, 101, 61));
        pushButton_RTS = new QPushButton(centralWidget);
        pushButton_RTS->setObjectName(QStringLiteral("pushButton_RTS"));
        pushButton_RTS->setGeometry(QRect(10, 320, 101, 61));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 990, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pushButton_exit->setText(QApplication::translate("MainWindow", "exit", 0));
        pushButton_folder->setText(QApplication::translate("MainWindow", "Folder", 0));
        pushButton_write->setText(QApplication::translate("MainWindow", "Write", 0));
        label_debug->setText(QString());
        pushButton_uart->setText(QApplication::translate("MainWindow", "Uart", 0));
        label->setText(QApplication::translate("MainWindow", "state", 0));
        pushButton_clearScreen->setText(QApplication::translate("MainWindow", "Clear Screen", 0));
        pushButton_RTS->setText(QApplication::translate("MainWindow", "RTS HW", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
