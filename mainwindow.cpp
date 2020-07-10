#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QDateTime"
#include "packet.h"
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
    qDebug() << " packet send connect attempt:" << connect(this, SIGNAL(sendPacket(Packet *)),
             &packetNetwork, SLOT(packetToSend(Packet *)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendBtn_clicked()
{
    Packet *testPacket = new Packet();
    // on click send buttons
    testPacket->name = ui->name->text();
    testPacket->port = ui->port->text().toUInt();
    testPacket->toIP = ui->address->text();
    testPacket->fromIP = "::1";
    testPacket->hexString =  ui->packetHexEdit->text().simplified();
    testPacket->timestamp = QDateTime::currentDateTime();
    emit sendPacket(testPacket);

    // render table
    this->ui->tableWidget_2->insertRow(this->ui->tableWidget_2->rowCount());
    int rowIdx = this->ui->tableWidget_2->rowCount()-1;
    QTableWidgetItem *item0 = new QTableWidgetItem(QDateTime::currentDateTime().toString());
    QTableWidgetItem *item1 = new QTableWidgetItem(testPacket->fromIP);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString::number(this->myPort));
    QTableWidgetItem *item3 = new QTableWidgetItem(testPacket->toIP);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString::number(testPacket->port));
    QTableWidgetItem *item5 = new QTableWidgetItem("");
    QTableWidgetItem *item6 = new QTableWidgetItem("");
    QTableWidgetItem *item7 = new QTableWidgetItem(ui->packetASCIIEdit->text());
    QTableWidgetItem *item8 = new QTableWidgetItem(testPacket->hexString);
    this->ui->tableWidget_2->setItem(rowIdx,0,item0);
    this->ui->tableWidget_2->setItem(rowIdx,1,item1);
    this->ui->tableWidget_2->setItem(rowIdx,2,item2);
    this->ui->tableWidget_2->setItem(rowIdx,3,item3);
    this->ui->tableWidget_2->setItem(rowIdx,4,item4);
    this->ui->tableWidget_2->setItem(rowIdx,5,item5);
    this->ui->tableWidget_2->setItem(rowIdx,6,item6);
    this->ui->tableWidget_2->setItem(rowIdx,7,item7);
    this->ui->tableWidget_2->setItem(rowIdx,8,item8);
    delete testPacket;
}

void MainWindow::on_pushButton_3_clicked()
{
    // on click save button
}

// ascii to hex
QString MainWindow::ascTohex(QByteArray array)
{
    QString str = "";
    QString tem = array.toHex();
    for(int i = 0;i < tem.count();i++)
    {
        str.push_back(tem.at(i));
        if(i % 2 == 1 && i != 0)
        {
            str.push_back(' ');
        }
    }
    return str;
}
void MainWindow::on_packetASCIIEdit_lostFocus()
{
    QString quicktestASCII =  ui->packetASCIIEdit->text();
    ui->packetHexEdit->setText(Packet::ASCIITohex(quicktestASCII));


    QString quicktestASCII2 =  ui->packetHexEdit->text();

    ui->packetASCIIEdit->setText(Packet::hexToASCII(quicktestASCII2));
    ui->packetASCIIEdit->setToolTip("");

    qDebug() << __FILE__ << "/" << __LINE__ << "on_serialASCIIEdit_lostFocus";

}

void MainWindow::on_packetASCIIEdit_editingFinished()
{
    on_packetASCIIEdit_lostFocus();
}
