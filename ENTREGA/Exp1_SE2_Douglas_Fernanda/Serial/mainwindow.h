#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void readData();
    void timerTeste();
    void conectar();
    void desconectar();
    void atualizarTela();
    void modbus(char dado);
    void switches();
    void temperatura();
    void umidade();

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_buttonLed1_clicked();

    void on_buttonLed2_clicked();

    void on_buttonLed3_clicked();

    void on_buttonLed4_clicked();

    void on_labelFloat_valueChanged(double arg1);

private:
    Ui::MainWindow *ui;
    QSerialPort *serial;
};

#endif // MAINWINDOW_H
