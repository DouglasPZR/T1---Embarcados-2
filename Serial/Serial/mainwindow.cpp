#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QtDebug>
#include <QTimer>

QTimer *timer = new QTimer(); //cria novo timer

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(timer, SIGNAL(timeout()),SLOT(timer_teste()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    serial->setPortName("COM12");
    serial->setBaudRate(9600);
    serial->setDataBits(static_cast<QSerialPort::DataBits>(8));
    serial->setParity(static_cast<QSerialPort::Parity>(0));
    serial->setStopBits(static_cast<QSerialPort::StopBits>(1));
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(0));
    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug("Porta Aberta");
        ui->label->setText("Status da Porta : ABERTA");
        timer->start(1000);
    }
    else
    {
        qDebug("Não Abriu");
        ui->label->setText("Status da Porta : FECHADA");
    }
}

void MainWindow::timer_teste()
{
    qDebug("Entra nesta função a cada 1s");
}
void MainWindow::readData()
{
    char buffer[30];
    int x=0;
    const QByteArray data = serial->readAll();
    qDebug(data);
    ui->lineEdit->setText(data);
    // ou
    /*
    while(x<1)
        x=serial->bytesAvailable();
    serial->read(buffer,2);
    */
}

void MainWindow::on_pushButton_2_clicked()
{
    char buffer[30];
    buffer[0]='1';

    if(serial->isOpen())// se porta aberta
    {
        serial->write(buffer,1);
    }
}
