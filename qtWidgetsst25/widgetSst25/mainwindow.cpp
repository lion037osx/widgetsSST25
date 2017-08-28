#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "qextserialenumerator.h"

#include <QDebug>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>

//#include <QDateTime>
#include <QTimer>
#include <QTime>
//#include <QDate>
//#include <QPixmap>
//#include <QColor>
//#include <QPalette>
//#include <QColorDialog>
//#include <QFile>
//#include <QIcon>
//#include <QSize>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),port(NULL),counterDataReceived(0)
{
    ui->setupUi(this);
//on_progressBar_valueChanged(0);
    global_filename=qApp->applicationDirPath() + "/../widgetSst25/bmp/logoIcon480x272.bmp";

    qDebug()<<"filename:"<<global_filename;

    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_exit_clicked()
{
    qDebug()<<"Closed Port";
    delete port;
    port=NULL;
    this->close();
}

void MainWindow::on_pushButton_folder_clicked()
{
    QString filename=QFileDialog::getOpenFileName(
                this,
                tr("Open"),
                "/",
                "All files(*.*);;Text File(*.bmp);;"
                );
    QMessageBox::information(this,tr("File Name"),filename);
    global_filename=filename;
    ui->label_debug->setText(global_filename);
}





void MainWindow::on_pushButton_uart_clicked()
{
    if (!port)
    {
        QString sPort;
        port= new QextSerialPort(sPort, QextSerialPort::EventDriven);
        port->setBaudRate(BAUD115200);
        port->setFlowControl(FLOW_OFF);
        port->setParity(PAR_NONE);
        port->setDataBits(DATA_8);
        port->setStopBits(STOP_1);
        #ifdef Q_OS_MACOS
         port->setPortName("/dev/cu.SLAB_USBtoUART");
        #endif
        #ifdef Q_OS_LINUX
         port->setPortName("/dev/ttyUSB0");
        #endif
        if(port->open(QIODevice::ReadWrite)==true)
        {
             qDebug()<<"Open Port success!!!";
             connect(port, SIGNAL(readyRead()),this,SLOT (receivedData()));
        }
        else
        {
            qDebug()<<"Open Error ";
            delete port;
            port=NULL;
        }
    }
    else
    {
        qDebug()<<"Closed Port";
        delete port;
        port=NULL;
    }
    if (port && port->isOpen())
         ui->pushButton_uart->setText("Disconnect");
    else
        ui->pushButton_uart->setText("Connect");
}

void MainWindow::on_pushButton_write_clicked()
{

QFile fs_bmp(global_filename);
if(!fs_bmp.open(QIODevice::ReadOnly | QIODevice::Text))return;
QTextStream stream_reader(&fs_bmp);
QString temp_text;
char buff_tmp[8];
char bmpTmp[2];
//static char readByteBMP[((480*272*2)-(138-6)+1)];
static char checksum=0x00;
static char onebyte[2];

stream_reader.seek(0x1C);
fs_bmp.read(onebyte,sizeof(unsigned char));
buff_tmp[0]=0x00;
 port->write((char *)onebyte);
 checksum|=onebyte[0]&0xFF;

 stream_reader.seek(0x1C);
 fs_bmp.read(onebyte,sizeof(unsigned char));
 buff_tmp[1]=onebyte[0];
 port->write((char *)onebyte);
checksum|=onebyte[0]&0xFF;

temp_text=QByteArray::number(buff_tmp[1]);
qDebug()<<"size:"<<temp_text<<"bits";


//read size width
stream_reader.seek(0x16);
fs_bmp.read(onebyte,sizeof(unsigned char));
buff_tmp[2]=onebyte[0];
port->write((char *)onebyte);
checksum|=onebyte[0]&0xFF;

stream_reader.seek(0x17);
fs_bmp.read(onebyte,sizeof(unsigned char));
buff_tmp[3]=onebyte[0];
port->write((char *)onebyte);
checksum|=onebyte[0]&0xFF;

temp_text=QByteArray::number((unsigned short int)(((buff_tmp[3]<<8)&0xff00) | (buff_tmp[2]&0xff)));
qDebug()<<"width:"<<temp_text<<" pixels";


//read size height
stream_reader.seek(0x12);
fs_bmp.read(onebyte,sizeof(unsigned char));
buff_tmp[4]=onebyte[0];
port->write((char *)onebyte);
checksum|=onebyte[0]&0xFF;

stream_reader.seek(0x13);
fs_bmp.read(onebyte,sizeof(unsigned char));
port->write((char *)onebyte);
buff_tmp[5]=onebyte[0];
checksum|=onebyte[0]&0xFF;
buff_tmp[6]=0x00;

temp_text=QByteArray::number((unsigned short int)(((buff_tmp[5]<<8)&0xff00) | (buff_tmp[4]&0xff)));
qDebug()<<"height:"<<temp_text<<" pixels";


quint64 divCalcProgressBar=((480*272*2)-0x8A);
quint64 addressBinary=0x8A;
int progressBarPorcent=0;
int progressBarTmp=0;

    while(!stream_reader.atEnd())
    {
            stream_reader.seek(addressBinary);
            fs_bmp.read(bmpTmp,sizeof(unsigned char));
            port->write((char *)bmpTmp);

            progressBarPorcent=(int)( (addressBinary*100) / divCalcProgressBar );
        if(progressBarTmp!=progressBarPorcent){
            ui->progressBar->setValue(progressBarPorcent);
            progressBarTmp=progressBarPorcent;
        }
        addressBinary++;
    }
    qDebug()<<"Max address:"<<(addressBinary-1-0x8A);
    fs_bmp.close();
}


void MainWindow::writeSerialPort(const char* buff){
    port->write(buff);
}

void MainWindow::receivedData(){
    QByteArray bytes;
    int cant=port->bytesAvailable();
    //if(bytes.isNull())return;
    bytes.resize(cant);
    port->read(bytes.data(),bytes.size());//cant de datos a leer
    counterDataReceived+=cant;
    ui->plainTextEdit_uart->insertPlainText(bytes);
    ui->plainTextEdit_uart->ensureCursorVisible();
    if(stat==1){
        QTextStream stream( &file );
        stream<<bytes;
    }
    qDebug()<<"dDebug:"<<bytes;
}



void MainWindow::delay()
{
    QTime dieTime= QTime::currentTime().addMSecs(1);
    //QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime)
    QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


void MainWindow::on_pushButton_clearScreen_clicked()
{
    ui->plainTextEdit_uart->clear();
}
