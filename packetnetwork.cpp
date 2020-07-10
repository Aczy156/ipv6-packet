#include "packetnetwork.h"
#include <QHostAddress>

PacketNetwork::PacketNetwork()
{

}
void PacketNetwork::setPacket(Packet *sendPacket)
{
    this->sendPacket = sendPacket;
    this->data = sendPacket->getByteArray();
}
bool PacketNetwork::init()
{
    socket = new QTcpSocket();
    socket->connectToHost(QHostAddress(this->sendPacket->toIP), this->sendPacket->port, QTcpSocket::ReadWrite);
//    socket->connectToHost(QHostAddress::LocalHost, 8081);
    connect(socket, SIGNAL(connected()), this, SLOT(send()));
    return socket->waitForConnected();
}
bool PacketNetwork::send()
{
    qDebug() << "send";
    if(socket->isOpen())
        {
//            socket->write(IntToArray(data.size())); //write size of data
            qDebug() << data;
            socket->write(data); //write the data itself
            return socket->waitForBytesWritten();
        }
        else
            return false;
}
void PacketNetwork::packetToSend(Packet *sendPacket)
{
    setPacket(sendPacket);
    // 如果連接失敗回傳 false
    qDebug() << init();
    socket->close();
    delete socket;
    qDebug() << "close";
}
