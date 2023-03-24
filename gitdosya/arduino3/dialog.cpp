#include "dialog.h"
#include "./ui_dialog.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->send_button, &QPushButton::clicked, this, &Dialog::sendMessage);
    //connect(ui->send_button, &QPushButton::clicked, this, &Dialog::waitForRespond);
    connect(ui->receive_button, &QPushButton::clicked, this, &Dialog::receiveMessage);
    connect(ui->button_left, &QPushButton::clicked, this, &Dialog::setMotorDirectionLeft);
    connect(ui->button_right, &QPushButton::clicked, this, &Dialog::setMotorDirectionRight);

    arduino_is_available = false;
    arduino_port_name = "";

    arduino = new QSerialPort;

    QProcess *process1 = new QProcess(this);

    process1->start(QString("lsusb"), QIODevice::ReadWrite);

    bool retval = false;
    QByteArray buffer;

    while ((retval = process1->waitForFinished()))
        buffer.append(process1->readAll());

    if (!retval) {
        qDebug() << "Process 2 error:" << process1->errorString();
    }

    qDebug() << buffer;

    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()) {
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
        }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if (serialPortInfo.hasProductIdentifier()) {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
        }
    }
/*

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
    {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            if(serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id){
                if(serialPortInfo.productIdentifier() == arduino_uno_product_id) {
                    arduino_port_name = serialPortInfo.portName();
                    qDebug() << "Arduino port name: " + arduino_port_name;
                    arduino_is_available = true;
                }
            }
        }
    }

    if (arduino_is_available) {
        arduino->setPortName(arduino_port_name);
        bool isSuccesfull = arduino->open(QSerialPort::ReadWrite);
        arduino->setBaudRate(QSerialPort::Baud115200);
        arduino->setDataBits(QSerialPort::Data8);
        arduino->setParity(QSerialPort::NoParity);
        arduino->setStopBits(QSerialPort::OneStop);
        arduino->setFlowControl(QSerialPort::NoFlowControl);

        qDebug() << "Arduino configured!";
        qDebug() << "Is arduino open for connection: " << isSuccesfull;
        qDebug() << "The error is" << arduino->errorString();
    } else {
        QMessageBox::warning(this, "Port error", "Couldnt find arduino!");
    }*/

}

Dialog::~Dialog()
{
    if (arduino->isOpen()) {
        arduino->close();
    }

    delete ui;
}

void Dialog::sendMessage()
{
    qDebug() << "Is Arduino open: " << arduino->isOpen();
    qDebug() << "Is Arduino writable: " << arduino->isWritable();

    if (arduino->isOpen()) {


        if (ui->radioButton_dial->isChecked()) {
            /* Dial */
            arduino->write(QString::number(ui->dial->value() * m_motorDirection).append("\n").toStdString().c_str());
            qDebug() <<  "Message is sent! Message: " << QString::number(ui->dial->value() * m_motorDirection).append("\n").toStdString().c_str();
        }
        else if (ui->radioButton_lineEdit->isChecked()) {
            /* Line Edit */
            arduino->write(ui->lineEdit->text().append("\n").toStdString().c_str());
            qDebug() << "Message is sent! Message: " << ui->lineEdit->text().toStdString().c_str();
        }
        else if (ui->radioButton_spinBox->isChecked()) {
            /* Spin Box */
            arduino->write(QString::number(ui->spinBox->value()).append("\n").toStdString().c_str());
            qDebug() << "Message is sent! Message: " << QString::number(ui->spinBox->value()).toStdString().c_str();
        }
    } else {
        qDebug() << "Couldnt write to Serial!";
    }
}

void Dialog::receiveMessage()
{
    m_readData.remove(0, m_readData.length());

    m_readData.append(arduino->readAll());

    qDebug() << "Received message is : " << m_readData;
    ui->label_received->setText(m_readData);
}

void Dialog::waitForRespond()
{
    /*
    if (!arduino->waitForReadyRead()) {
        ui->receive_button->setEnabled(false);
    }
    ui->receive_button->setEnabled(true);
    */
}

void Dialog::setMotorDirectionRight()
{
    m_motorDirection = +1;
}

void Dialog::setMotorDirectionLeft()
{
    m_motorDirection = -1;
}
