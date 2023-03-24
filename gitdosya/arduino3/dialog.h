#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
    QSerialPort *arduino;

    static const quint16 arduino_uno_vendor_id = 6790;
    static const quint16 arduino_uno_product_id = 29987;
    QString arduino_port_name;
    bool arduino_is_available;
    //Vendor ID:  6790
    //Product ID:  29987
    QByteArray m_readData;

    int m_motorDirection = 0;

private slots:
    void sendMessage();
    void receiveMessage();
    void waitForRespond();
    void setMotorDirectionRight();
    void setMotorDirectionLeft();

};
#endif // DIALOG_H
