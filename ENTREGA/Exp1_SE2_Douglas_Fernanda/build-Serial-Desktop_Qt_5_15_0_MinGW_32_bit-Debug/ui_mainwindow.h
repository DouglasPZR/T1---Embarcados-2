/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton1;
    QPushButton *pushButton2;
    QLineEdit *lineEdit;
    QLabel *label1;
    QLCDNumber *temp;
    QLCDNumber *umid;
    QDoubleSpinBox *labelFloat;
    QPushButton *buttonLed1;
    QPushButton *buttonLed2;
    QPushButton *buttonLed3;
    QPushButton *buttonLed4;
    QLabel *led1;
    QLabel *led2;
    QLabel *led3;
    QLabel *led4;
    QLabel *label4;
    QLabel *label5;
    QLabel *switch1;
    QLabel *switch2;
    QLabel *switch3;
    QLabel *switch4;
    QLabel *label2;
    QLabel *label3;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(379, 510);
        MainWindow->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton1 = new QPushButton(centralWidget);
        pushButton1->setObjectName(QString::fromUtf8("pushButton1"));
        pushButton1->setGeometry(QRect(20, 390, 331, 51));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        pushButton1->setFont(font);
        pushButton2 = new QPushButton(centralWidget);
        pushButton2->setObjectName(QString::fromUtf8("pushButton2"));
        pushButton2->setGeometry(QRect(150, 210, 201, 31));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(150, 150, 201, 51));
        lineEdit->setMaxLength(16);
        label1 = new QLabel(centralWidget);
        label1->setObjectName(QString::fromUtf8("label1"));
        label1->setGeometry(QRect(110, 460, 141, 16));
        temp = new QLCDNumber(centralWidget);
        temp->setObjectName(QString::fromUtf8("temp"));
        temp->setGeometry(QRect(40, 60, 91, 41));
        temp->setLayoutDirection(Qt::LeftToRight);
        temp->setFrameShape(QFrame::Box);
        temp->setFrameShadow(QFrame::Raised);
        temp->setLineWidth(1);
        temp->setMidLineWidth(0);
        temp->setSmallDecimalPoint(true);
        temp->setDigitCount(3);
        temp->setSegmentStyle(QLCDNumber::Flat);
        umid = new QLCDNumber(centralWidget);
        umid->setObjectName(QString::fromUtf8("umid"));
        umid->setGeometry(QRect(220, 60, 91, 41));
        umid->setSmallDecimalPoint(true);
        umid->setDigitCount(3);
        umid->setSegmentStyle(QLCDNumber::Flat);
        umid->setProperty("value", QVariant(0.000000000000000));
        labelFloat = new QDoubleSpinBox(centralWidget);
        labelFloat->setObjectName(QString::fromUtf8("labelFloat"));
        labelFloat->setGeometry(QRect(20, 160, 111, 61));
        QFont font1;
        font1.setPointSize(18);
        labelFloat->setFont(font1);
        labelFloat->setAlignment(Qt::AlignCenter);
        labelFloat->setKeyboardTracking(true);
        labelFloat->setSingleStep(0.050000000000000);
        buttonLed1 = new QPushButton(centralWidget);
        buttonLed1->setObjectName(QString::fromUtf8("buttonLed1"));
        buttonLed1->setGeometry(QRect(60, 260, 61, 23));
        buttonLed2 = new QPushButton(centralWidget);
        buttonLed2->setObjectName(QString::fromUtf8("buttonLed2"));
        buttonLed2->setGeometry(QRect(60, 290, 61, 21));
        buttonLed3 = new QPushButton(centralWidget);
        buttonLed3->setObjectName(QString::fromUtf8("buttonLed3"));
        buttonLed3->setGeometry(QRect(60, 320, 61, 21));
        buttonLed4 = new QPushButton(centralWidget);
        buttonLed4->setObjectName(QString::fromUtf8("buttonLed4"));
        buttonLed4->setGeometry(QRect(60, 350, 61, 21));
        led1 = new QLabel(centralWidget);
        led1->setObjectName(QString::fromUtf8("led1"));
        led1->setGeometry(QRect(30, 260, 21, 21));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setWeight(75);
        led1->setFont(font2);
        led1->setFrameShape(QFrame::Box);
        led1->setFrameShadow(QFrame::Plain);
        led1->setAlignment(Qt::AlignCenter);
        led2 = new QLabel(centralWidget);
        led2->setObjectName(QString::fromUtf8("led2"));
        led2->setGeometry(QRect(30, 290, 21, 21));
        led2->setFont(font2);
        led2->setFrameShape(QFrame::Box);
        led2->setFrameShadow(QFrame::Plain);
        led2->setAlignment(Qt::AlignCenter);
        led3 = new QLabel(centralWidget);
        led3->setObjectName(QString::fromUtf8("led3"));
        led3->setGeometry(QRect(30, 320, 21, 21));
        led3->setFont(font2);
        led3->setFrameShape(QFrame::Box);
        led3->setFrameShadow(QFrame::Plain);
        led3->setAlignment(Qt::AlignCenter);
        led4 = new QLabel(centralWidget);
        led4->setObjectName(QString::fromUtf8("led4"));
        led4->setGeometry(QRect(30, 350, 21, 21));
        led4->setFont(font2);
        led4->setFrameShape(QFrame::Box);
        led4->setFrameShadow(QFrame::Plain);
        led4->setAlignment(Qt::AlignCenter);
        label4 = new QLabel(centralWidget);
        label4->setObjectName(QString::fromUtf8("label4"));
        label4->setGeometry(QRect(10, 20, 171, 31));
        QFont font3;
        font3.setPointSize(15);
        label4->setFont(font3);
        label4->setAlignment(Qt::AlignCenter);
        label5 = new QLabel(centralWidget);
        label5->setObjectName(QString::fromUtf8("label5"));
        label5->setGeometry(QRect(200, 20, 131, 31));
        label5->setFont(font3);
        label5->setAlignment(Qt::AlignCenter);
        switch1 = new QLabel(centralWidget);
        switch1->setObjectName(QString::fromUtf8("switch1"));
        switch1->setGeometry(QRect(220, 260, 91, 20));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        switch1->setFont(font4);
        switch1->setAlignment(Qt::AlignCenter);
        switch2 = new QLabel(centralWidget);
        switch2->setObjectName(QString::fromUtf8("switch2"));
        switch2->setGeometry(QRect(220, 290, 91, 20));
        switch2->setFont(font4);
        switch2->setAlignment(Qt::AlignCenter);
        switch3 = new QLabel(centralWidget);
        switch3->setObjectName(QString::fromUtf8("switch3"));
        switch3->setGeometry(QRect(220, 320, 91, 20));
        switch3->setFont(font4);
        switch3->setAlignment(Qt::AlignCenter);
        switch4 = new QLabel(centralWidget);
        switch4->setObjectName(QString::fromUtf8("switch4"));
        switch4->setGeometry(QRect(220, 350, 91, 20));
        switch4->setFont(font4);
        switch4->setAlignment(Qt::AlignCenter);
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(30, 130, 81, 20));
        label3 = new QLabel(centralWidget);
        label3->setObjectName(QString::fromUtf8("label3"));
        label3->setGeometry(QRect(190, 130, 121, 20));
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton1->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        pushButton2->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Status da Porta : FECHADA", nullptr));
        buttonLed1->setText(QCoreApplication::translate("MainWindow", "Led 1", nullptr));
        buttonLed2->setText(QCoreApplication::translate("MainWindow", "Led 2", nullptr));
        buttonLed3->setText(QCoreApplication::translate("MainWindow", "Led 3", nullptr));
        buttonLed4->setText(QCoreApplication::translate("MainWindow", "Led 4", nullptr));
        led1->setText(QString());
        led2->setText(QString());
        led3->setText(QString());
        led4->setText(QString());
        label4->setText(QCoreApplication::translate("MainWindow", "Temperatura (\302\260C)", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "Umidade (%)", nullptr));
        switch1->setText(QCoreApplication::translate("MainWindow", "Switch 1 - Off", nullptr));
        switch2->setText(QCoreApplication::translate("MainWindow", "Switch 2 - Off", nullptr));
        switch3->setText(QCoreApplication::translate("MainWindow", "Switch 3 - Off", nullptr));
        switch4->setText(QCoreApplication::translate("MainWindow", "Switch 4 - Off", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "N\303\232MERO FLOAT", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "MENSAGEM DO DISPLAY", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
