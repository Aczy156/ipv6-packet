#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "packet.h"
#include "packetnetwork.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sendPacket(Packet *sendpacket);
private slots:
    void on_pushButton_3_clicked();

    QString ascTohex(QByteArray array);

    void on_sendBtn_clicked();

    void on_packetASCIIEdit_editingFinished();
    void on_packetASCIIEdit_lostFocus();
private:
    Ui::MainWindow *ui;
    PacketNetwork packetNetwork;
    QString myIP = "1.2.3.4";
    int myPort = 1234;
    struct packet{
        QString time = "";
        QString from_ip = "";
        int from_port = 0;
        QString to_ip = "";
        int to_port = 0;
        QString Method = "";
        QString Error = "";
        QString ASCII = "";
        QString HEX = "";
//        packet();
//        packet(int a,QString b):to_port(a),to_ip(b){};
//        packet(int a,QString b){
//            to_port = a;
//            to_ip = b;
//        }
//        packet(QString time,QString from_ip,int from_port,QString to_ip,int to_port,QString Method,QString Error,QString ASCII,QString HEX):
//            time(time),from_ip(from_ip),from_port(from_port),to_ip(to_ip),to_port(to_port),Method(Method),Error(Error),ASCII(ASCII),HEX(HEX){}
    };
    QVector<packet> packetVector;
};
#endif // MAINWINDOW_H
