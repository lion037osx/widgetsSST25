#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <qextserialport.h>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();





private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_folder_clicked();

    void on_pushButton_uart_clicked();

    void on_pushButton_write_clicked();

   //void on_progressBar_valueChanged(int value);

    void receivedData();
    void delay();

    void on_pushButton_clearScreen_clicked();

private:
    Ui::MainWindow *ui;
        QextSerialPort *port;
        int m_cant_bytes_enviados;
        int counterDataReceived;
        char * rx_data;
        QString buffer;
        QFile file;
        bool  stat;
        QString global_filename;
        void writeSerialPort(const char* buff);
};

#endif // MAINWINDOW_H
