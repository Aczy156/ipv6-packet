#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "QDateTime"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this); 
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // on click send buttons
    QString name = this->ui->lineEdit->text();
    QString ascii = this->ui->lineEdit_2->text();
    QByteArray asciiByteArray = ascii.toUtf8();
    QString hex = ascTohex(asciiByteArray);
    QString ip = this->ui->lineEdit_4->text();
    int port = this->ui->lineEdit_5->text().toInt();

    // transfer ascii to hex
    qDebug()<<"asc str is "<<ascii<<"hex is "<<hex<<endl;

    // add to packet vector
//    this->packetVector.push_back(packet("QDateTime::currentDateTime().toString()","this->myIP",this->myPort,"address",port,"","","ascii","hex"));

//    packet p = {time:QDateTime::currentDateTime().toString(),from_ip:this->myIP,from_port:this->myPort,to_ip:ip,to_port:port,Method:"",Error:"",ASCII:ascii,HEX:hex};
//    packet p = {.time = QDateTime::currentDateTime().toString(),.from_ip = this->myIP,.from_port = this->myPort,.to_ip = ip,.to_port = port,.Method = "",.Error = "",.ASCII = ascii,.HEX = hex};
    packet p;
    p.time = QDateTime::currentDateTime().toString();
    p.from_ip = this->myIP;
    p.from_port = this->myPort;
    p.to_ip = ip;
    p.to_port = port;
    p.Method = "";
    p.Error = "";
    p.ASCII = ascii;
    p.HEX = hex;
    packetVector.push_back(p);

    // render table
    this->ui->tableWidget_2->insertRow(this->ui->tableWidget_2->rowCount());
    int rowIdx = this->ui->tableWidget_2->rowCount()-1;
    QTableWidgetItem *item0 = new QTableWidgetItem(QDateTime::currentDateTime().toString());
    QTableWidgetItem *item1 = new QTableWidgetItem(this->myIP);
    QTableWidgetItem *item2 = new QTableWidgetItem(QString(this->myPort));
    QTableWidgetItem *item3 = new QTableWidgetItem(ip);
    QTableWidgetItem *item4 = new QTableWidgetItem(QString(port));
    QTableWidgetItem *item5 = new QTableWidgetItem("");
    QTableWidgetItem *item6 = new QTableWidgetItem("");
    QTableWidgetItem *item7 = new QTableWidgetItem(ascii);
    QTableWidgetItem *item8 = new QTableWidgetItem(hex);
    this->ui->tableWidget_2->setItem(rowIdx,0,item0);
    this->ui->tableWidget_2->setItem(rowIdx,1,item1);
    this->ui->tableWidget_2->setItem(rowIdx,2,item2);
    this->ui->tableWidget_2->setItem(rowIdx,3,item3);
    this->ui->tableWidget_2->setItem(rowIdx,4,item4);
    this->ui->tableWidget_2->setItem(rowIdx,5,item5);
    this->ui->tableWidget_2->setItem(rowIdx,6,item6);
    this->ui->tableWidget_2->setItem(rowIdx,7,item7);
    this->ui->tableWidget_2->setItem(rowIdx,8,item8);

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
