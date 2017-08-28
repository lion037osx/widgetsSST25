#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QSplashScreen>
#include <QTimer>
#include <QLabel>
#include <QStatusBar>
#include <QDebug>
#include <QIcon>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   //MainWindow w;
   //w.show();
   QSplashScreen *splash=new QSplashScreen;

   #ifdef Q_OS_LINUX
   qDebug()<<"LINUX OS";
   splash->setPixmap(QPixmap(qApp->applicationDirPath() + "/../widgetSst25/png/android.png"));
   #endif

   #ifdef Q_OS_MACOS
   qDebug()<<"MAC OS";
   splash->setPixmap(QPixmap(qApp->applicationDirPath() + "/../widgetSst25/png/android.png"));
   #endif

   splash->setWindowOpacity(0.95);
   splash->show();
   QTimer::singleShot(1000,splash,SLOT(close()));

   MainWindow w;

   QIcon icon(qApp->applicationDirPath() +"/../widgetSst25/png/android.png");

   w.setWindowIcon(icon);
   w.move(QApplication::desktop()->screen()->rect().center() - w.rect().center());
   QTimer::singleShot(1000,&w,SLOT(show()));

   return a.exec();
}
