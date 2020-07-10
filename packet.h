#ifndef PACKET_H
#define PACKET_H
#include<QString>
#include<QDateTime>

class Packet
{
private:
 static int hexToInt(QChar hex);
public:
    QString name;
    QString hexString;
    QString fromIP;
    QString toIP;
    QString resolvedIP;
    QString errorString;
    QDateTime timestamp;
    float repeat;
    unsigned int port;
    unsigned int fromPort;
    Packet();
    static QString ASCIITohex(QString &ascii);
    static QString hexToASCII(QString &hex);
    static QByteArray HEXtoByteArray(QString thehex);
    QByteArray getByteArray();
    void init();
};

#endif // PACKET_H
