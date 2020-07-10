#ifndef PACKETNETWORK_H
#define PACKETNETWORK_H
#include<QTcpSocket>
#include "packet.h"

class PacketNetwork: public QObject
{
    Q_OBJECT
public:
    QTcpSocket *socket;
    QByteArray data;
    Packet *sendPacket;
    PacketNetwork();
    void setPacket(Packet *packet);
    bool init();
public slots:
    bool send();
    void packetToSend(Packet *);
};

#endif // PACKETNETWORK_H
