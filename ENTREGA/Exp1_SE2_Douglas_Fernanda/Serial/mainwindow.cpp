#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QtDebug>
#include <QTimer>
#include <QPixmap>

QTimer *timer = new QTimer(); //cria novo timer
int isConected = 0;
uint8_t ledState = 0;

typedef union{
    struct{
        unsigned char high;
        unsigned char low;
        unsigned char high1;
        unsigned char low1;
    }parcial;
    float total;
}INTEIRO;
INTEIRO dado16,temp,umid;

/* Table of CRC values for high–order byte */
static unsigned char auchCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
    0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
    0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
    0x40
} ;
/* Table of CRC values for low–order byte */
static unsigned char auchCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
    0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
    0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
    0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
    0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
    0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
    0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
    0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
    0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
    0x40
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(timer, SIGNAL(timeout()),SLOT(timerTeste()));
    QPixmap luzOn ("D:/EE/2021_1/SE2/Exp1_SE2_Douglas_Fernanda/Serial/on.png");
    QPixmap luzOff ("D:/EE/2021_1/SE2/Exp1_SE2_Douglas_Fernanda/Serial/off.png");
    ui->led1->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
    ui->led2->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
    ui->led3->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
    ui->led4->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
    atualizarTela();
}

unsigned short CRC16 (unsigned char *puchMsg, unsigned short usDataLen){ /* The function returns the CRC as a unsigned short type */
    unsigned char uchCRCHi = 0xFF ; /* high byte of CRC initialized */
    unsigned char uchCRCLo = 0xFF ; /* low byte of CRC initialized */
    unsigned uIndex ; /* will index into CRC lookup table */
    while (usDataLen--){ /* pass through message buffer */
        uIndex = uchCRCLo ^ *puchMsg++; /* calculate the CRC */
        uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
        uchCRCHi = auchCRCLo[uIndex] ;
    }
    return (uchCRCLo << 8 | uchCRCHi);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerTeste()
{
    switches();
    temperatura();
    umidade();
}

void MainWindow::readData()
{
    char buffer[10];

    serial->read(buffer,1);
    modbus(buffer[0]);
}


void MainWindow::conectar()
{
    serial->setPortName("COM7");
    serial->setBaudRate(9600);
    serial->setDataBits(static_cast<QSerialPort::DataBits>(8));
    serial->setParity(static_cast<QSerialPort::Parity>(0));
    serial->setStopBits(static_cast<QSerialPort::StopBits>(1));
    serial->setFlowControl(static_cast<QSerialPort::FlowControl>(0));
    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug("Porta Aberta");
        ui->label1->setText("Status da Porta : ABERTA");
        timer->start(1000);
        isConected = 1;
    }
    else
    {
        qDebug("Não Abriu");
        ui->label1->setText("Status da Porta : FECHADA");
    }
}
void MainWindow::desconectar()
{
    if(serial->isOpen()) {
        serial->close();
    }
    isConected = 0;
}

void MainWindow::atualizarTela()
{
    if(isConected)
    {
        ui->lineEdit->setEnabled(true);
        ui->pushButton1->setText("Desconectar");
        ui->pushButton2->setEnabled(true);
        ui->umid->setEnabled(true);
        ui->temp->setEnabled(true);
        ui->labelFloat->setEnabled(true);
        ui->label4->setEnabled(true);
        ui->label5->setEnabled(true);
        ui->buttonLed1->setEnabled(true);
        ui->buttonLed2->setEnabled(true);
        ui->buttonLed3->setEnabled(true);
        ui->buttonLed4->setEnabled(true);
        ui->led1->setEnabled(true);
        ui->led2->setEnabled(true);
        ui->led3->setEnabled(true);
        ui->led4->setEnabled(true);
        ui->switch1->setEnabled(true);
        ui->switch2->setEnabled(true);
        ui->switch3->setEnabled(true);
        ui->switch4->setEnabled(true);
    }
    else
    {
        ui->lineEdit->setEnabled(false);
        ui->pushButton1->setText("Conectar");
        ui->pushButton2->setEnabled(false);
        ui->umid->setEnabled(false);
        ui->temp->setEnabled(false);
        ui->labelFloat->setEnabled(false);
        ui->label4->setEnabled(false);
        ui->label5->setEnabled(false);
        ui->buttonLed1->setEnabled(false);
        ui->buttonLed2->setEnabled(false);
        ui->buttonLed3->setEnabled(false);
        ui->buttonLed4->setEnabled(false);
        ui->led1->setEnabled(false);
        ui->led2->setEnabled(false);
        ui->led3->setEnabled(false);
        ui->led4->setEnabled(false);
        ui->switch1->setEnabled(false);
        ui->switch2->setEnabled(false);
        ui->switch3->setEnabled(false);
        ui->switch4->setEnabled(false);
    }
}

void MainWindow::modbus(char dado){
    static int state = 0;
    uint8_t crcHigh, crcLow;
    unsigned char buffer[15];
    unsigned short crc;

    switch(state){
          case 0:
            if(dado == 0x01){ //endereço do kit
              buffer[0] = dado;
              state = 1;
            }else{
              state = 0;
            }break;

          case 1:
            if(dado == 0x02){ //função Switches
              buffer[1] = dado;
              state = 2;
            }else if(dado == 0x03){ //função  e Umidade
              buffer[1] = dado;
              state = 6;
            }else{
              state = 0;
            }break;

          case 2:
            if(dado == 0x01){ //número de bytes
              buffer[2] = dado;
              state = 3;
            }else{
              state = 0;
            }break;

          case 3:
            if(dado & (1 << 0)){
                ui->switch1->setText("Switch 1 - On");
            }else{
                ui->switch1->setText("Switch 1 - Off");
            }if(dado & (1 << 1)){
                ui->switch2->setText("Switch 2 - On");
            }else{
                ui->switch2->setText("Switch 2 - Off");
            }if(dado & (1 << 2)){
                ui->switch3->setText("Switch 3 - On");
            }else{
                ui->switch3->setText("Switch 3 - Off");
            }if(dado & (1 << 3)){
                ui->switch4->setText("Switch 4 - On");
            }else{
                ui->switch4->setText("Switch 4 - Off");
            }
            buffer[3] = dado;
            state = 4;
        break;

        case 4:
          crcHigh = dado;
          state = 5;
        break;

        case 5:
          crcLow = dado;
          state = 0;
        break;
        //Função Temperatura - SHT15
        case 6:
          if(dado == 0x06){ //número de bytes
            buffer[2] = dado;
            state = 7;
          }else{
            state = 0;
          }break;

        case 7:
          if(dado == 0x00){
            buffer[3] = dado;
            state = 8;
          }else{
            state = 0;
          }
        break;

        case 8:
          if(dado == 0x01){
            buffer[4] = dado;
            state = 9;
          }else if(dado == 0x02){
              buffer[4] = dado;
              state = 15;
          }else{
            state = 0;
          }
        break;

        case 9:
          temp.parcial.low = dado;
          buffer[5] = dado;
          state = 10;
        break;

        case 10:
          temp.parcial.high = dado;
          buffer[6] = dado;
          state = 11;
        break;

        case 11:
          temp.parcial.low1 = dado;
          buffer[7] = dado;
          state = 12;
        break;

        case 12:
          temp.parcial.high1 = dado;
          buffer[8] = dado;
          ui->temp->display(temp.total);
          state = 13;
        break;

        case 13:
          crcHigh = dado;
          state = 14;
        break;

        case 14:
          crcLow = dado;
          state = 0;

          crc = CRC16(buffer,9);
          buffer[9] = ((crc >> 8) & 0xff);
          buffer[10] = ((crc) & 0xff);

         /*if((buffer[7] == crcHigh) && (buffer[8] == crcLow)){
            qDebug("CRC ok!");
         }else{
            qDebug("CRC error!");
         }*/
      break;

        case 15:
          umid.parcial.low = dado;
          buffer[5] = dado;
          state = 16;
        break;

        case 16:
          umid.parcial.high = dado;
          buffer[6] = dado;
          state = 17;
        break;

        case 17:
          umid.parcial.low1 = dado;
          buffer[7] = dado;
          state = 18;
        break;

        case 18:
          umid.parcial.high1 = dado;
          buffer[8] = dado;
          ui->umid->display(umid.total);
          state = 19;
        break;

        case 19:
          crcHigh = dado;
          state = 20;
        break;

        case 20:
          crcLow = dado;
          state = 0;

          crc = CRC16(buffer,9);
          buffer[9] = ((crc >> 8) & 0xff);
          buffer[10] = ((crc) & 0xff);
        break;
    }
}


void MainWindow::switches(){
    unsigned char switchesCom[9];
    unsigned short crc;

    switchesCom[0] = 0x01;
    switchesCom[1] = 0x02;
    switchesCom[2] = 0x00;
    switchesCom[3] = 0x02;
    switchesCom[4] = 0x00;
    switchesCom[5] = 0x04;

    crc = CRC16(switchesCom,6);

    switchesCom[6] = (crc >> 8) & 0xff;
    switchesCom[7] = crc & 0xff;

    serial->write((char*)switchesCom,8);
}

void MainWindow::temperatura(){
    unsigned char tempCom[9];
    unsigned short crc;

    tempCom[0] = 0x01;
    tempCom[1] = 0x03;
    tempCom[2] = 0x00;
    tempCom[3] = 0x04;
    tempCom[4] = 0x00;
    tempCom[5] = 0x03;

    crc = CRC16(tempCom,6);

    tempCom[6] = (crc >> 8) & 0xff;
    tempCom[7] = crc & 0xff;

    serial->write((char*)tempCom,8);
}

void MainWindow::umidade(){
    unsigned char umiCom[9];
    unsigned short crc;

    umiCom[0] = 0x01;
    umiCom[1] = 0x03;
    umiCom[2] = 0x00;
    umiCom[3] = 0x05;
    umiCom[4] = 0x00;
    umiCom[5] = 0x03;

    crc = CRC16(umiCom,6);

    umiCom[6] = (crc >> 8) & 0xff;
    umiCom[7] = crc & 0xff;

    serial->write((char*)umiCom,8);
}

void MainWindow::on_pushButton1_clicked()
{
    if(isConected)
    {
        desconectar();
    }
    else
    {
        conectar();
    }
    atualizarTela();

}

void MainWindow::on_pushButton2_clicked()
{
    unsigned char buffer[26];
        char aux[16];
        QString frase;
        unsigned short crc;
        //buffer[0]='1';
        frase = ui->lineEdit->text();
        strcpy(aux,frase.toLatin1());

        buffer[0]  = 0x01;
        buffer[1]  = 0x10;
        buffer[2]  = 0x00;
        buffer[3]  = 0x00;
        buffer[4]  = 0x00;
        buffer[5]  = 0x10;
        buffer[6]  = 0x20;
        buffer[7]  = aux[0];
        buffer[8]  = aux[1];
        buffer[9]  = aux[2];
        buffer[10] = aux[3];
        buffer[11] = aux[4];
        buffer[12] = aux[5];
        buffer[13] = aux[6];
        buffer[14] = aux[7];
        buffer[15] = aux[8];
        buffer[16] = aux[9];
        buffer[17] = aux[10];
        buffer[18] = aux[11];
        buffer[19] = aux[12];
        buffer[20] = aux[13];
        buffer[21] = aux[14];
        buffer[22] = aux[15];

        crc = CRC16(buffer,23);

        buffer[23] = (crc >> 8) & 0xff;
        buffer[24] = crc & 0xff;

        if(serial->isOpen())// se porta aberta
        {
            serial->write((char*)buffer,sizeof(buffer));
        }
}


void MainWindow::on_buttonLed1_clicked()
{
    unsigned char led1State[13];
    unsigned short crc;
    QPixmap luzOn ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/on.png");
    QPixmap luzOff ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/off.png");

    if(serial->isOpen()){// se porta aberta

        led1State[0] = 0x01;
        led1State[1] = 0x0F;
        led1State[2] = 0x00;
        led1State[3] = 0x01;
        led1State[4] = 0x00;
        led1State[5] = 0x04;
        led1State[6] = 0x01;

        ledState ^= (1 << 0);

         if(ledState & (1 << 0)){
           ui->led1->setPixmap(luzOn.scaled(71,61,Qt::KeepAspectRatio));
         }else{
           ui->led1->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
         }

        led1State[7] = ledState;
        crc = CRC16(led1State,8);

        led1State[8] = (crc >> 8) & 0xff;
        led1State[9] = crc & 0xff;

        serial->write((char*)led1State,10);
    }
}


void MainWindow::on_buttonLed2_clicked()
{
    unsigned char led2State[13];
    unsigned short crc;
    QPixmap luzOn ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/on.png");
    QPixmap luzOff ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/off.png");

    if(serial->isOpen()){// se porta aberta

        led2State[0] = 0x01;
        led2State[1] = 0x0F;
        led2State[2] = 0x00;
        led2State[3] = 0x01;
        led2State[4] = 0x00;
        led2State[5] = 0x04;
        led2State[6] = 0x01;

        ledState ^= (1 << 1);

         if(ledState & (1 << 1)){
           ui->led2->setPixmap(luzOn.scaled(71,61,Qt::KeepAspectRatio));
         }else{
           ui->led2->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
         }

        led2State[7] = ledState;
        crc = CRC16(led2State,8);

        led2State[8] = (crc >> 8) & 0xff;
        led2State[9] = crc & 0xff;

        serial->write((char*)led2State,10);
    }
}


void MainWindow::on_buttonLed3_clicked()
{
    unsigned char led3State[13];
    unsigned short crc;
    QPixmap luzOn ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/on.png");
    QPixmap luzOff ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/off.png");

    if(serial->isOpen()){// se porta aberta

        led3State[0] = 0x01;
        led3State[1] = 0x0F;
        led3State[2] = 0x00;
        led3State[3] = 0x01;
        led3State[4] = 0x00;
        led3State[5] = 0x04;
        led3State[6] = 0x01;

        ledState ^= (1 << 2);

         if(ledState & (1 << 2)){
           ui->led3->setPixmap(luzOn.scaled(71,61,Qt::KeepAspectRatio));
         }else{
           ui->led3->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
         }

        led3State[7] = ledState;
        crc = CRC16(led3State,8);

        led3State[8] = (crc >> 8) & 0xff;
        led3State[9] = crc & 0xff;

        serial->write((char*)led3State,10);
    }
}


void MainWindow::on_buttonLed4_clicked()
{
    unsigned char led4State[13];
    unsigned short crc;
    QPixmap luzOn ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/on.png");
    QPixmap luzOff ("C:/Users/dougl/Google Drive/Faculdade/GitHub/Embarcados II/Trabalho 1 - Douglas P Rodrigues/T1---Embarcados-2/ENTREGA/Exp1_SE2_Douglas_Fernanda/Serial/off.png");

    if(serial->isOpen()){// se porta aberta

        led4State[0] = 0x01;
        led4State[1] = 0x0F;
        led4State[2] = 0x00;
        led4State[3] = 0x01;
        led4State[4] = 0x00;
        led4State[5] = 0x04;
        led4State[6] = 0x01;

        ledState ^= (1 << 3);

         if(ledState & (1 << 3)){
           ui->led4->setPixmap(luzOn.scaled(71,61,Qt::KeepAspectRatio));
         }else{
           ui->led4->setPixmap(luzOff.scaled(71,61,Qt::KeepAspectRatio));
         }

        led4State[7] = ledState;
        crc = CRC16(led4State,8);

        led4State[8] = (crc >> 8) & 0xff;
        led4State[9] = crc & 0xff;

        serial->write((char*)led4State,10);
    }
}

void MainWindow::on_labelFloat_valueChanged(double arg1)
{
    unsigned char floatCom[13];
    unsigned short crc;

    if(serial->isOpen())// se porta aberta
    {
        floatCom[0] = 0x01;
        floatCom[1] = 0x10;
        floatCom[2] = 0x00;
        floatCom[3] = 0x06;
        floatCom[4] = 0x00;
        floatCom[5] = 0x02;
        floatCom[6] = 0x04;

        dado16.total = arg1;

        floatCom[7] = dado16.parcial.low;
        floatCom[8] = dado16.parcial.high;
        floatCom[9] = dado16.parcial.low1;
        floatCom[10] = dado16.parcial.high1;

        crc = CRC16(floatCom,11);

        floatCom[11] = (crc >> 8) & 0xff;
        floatCom[12] = crc & 0xff;

        serial->write((char*)floatCom,13);
    }
}
