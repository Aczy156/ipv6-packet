#include "packet.h"
#include <QDebug>

Packet::Packet()
{
    init();
}
void Packet::init()
{
    name = "";
    hexString = "";
    fromIP = "";
    toIP = "";
    errorString = "";
    port = 55005;
}
QByteArray Packet::getByteArray()
{
    return HEXtoByteArray(hexString);
}
QByteArray Packet::HEXtoByteArray(QString thehex)
{

    //function already ignores invalid chars...
    return QByteArray::fromHex(thehex.toLatin1());;
}
QString Packet::hexToASCII(QString &hex)
{


    QStringList hexSplit;

    //remove invalid characters of popular deliminators...
    hex = hex.replace(",", " ");
    hex = hex.replace(".", " ");
    hex = hex.replace(":", " ");
    hex = hex.replace(";", " ");
    hex = hex.replace("0x", " ");
    hex = hex.replace("x", " ");
    hex = hex.replace("\n", " ");
    hex = hex.replace("\r", " ");
    hex = hex.replace("\t", " ");

    QString hexText = hex.simplified();
    if (hexText.isEmpty()) {
        return "";
    }

    if ((hexText.size() % 2 != 0)) {
        //Not divisible by 2. What should I do?
        if (!hexText.contains(" ") && hexText.size() > 2) {
            //Seems to be one big hex stream. Front-load it with a 0.
            hexText.prepend("0");
        }

    }


    if (!hexText.contains(" ") && hexText.size() > 2 && hexText.size() % 2 == 0) {
        //does not contain any spaces.  Maybe one big hex stream?
        qDebug() << "no spaces" << "even digits";
        QStringList hexList;
        hexList.clear();
        QString append;
        append.clear();
        for (int i = 0; i < hexText.size(); i += 2) {
            append.clear();
            append.append(hexText[i]);
            append.append(hexText[i + 1]);
            hexList << append;
        }
        hexText = hexList.join(" ").trimmed();
        hex = hexText;
    }

    hexSplit = hexText.split(" ");
    QString asciiText = "";
    unsigned int convertInt;
    bool ok = false;
    int malformed = 0;
    bool malformedBool = false;
    QChar malformedChar;


    QString checkSpace = hex.at(hex.size() - 1);
    if (checkSpace == " ") {
        hexText.append(" ");
    }

    hex = hexText;

    // qDebug() << __FILE__ << "/" << __LINE__  << __FUNCTION__ <<"analyze hex split" << hexSplit;

    for (int i = 0; i < hexSplit.size(); i++) {
        if (hexSplit.at(i).size() > 2) {
            malformedBool = true;
            malformed = i;
            malformedChar = hexSplit.at(i).at(2);
            // qDebug() << __FILE__ << "/" << __LINE__ << __FUNCTION__  << "malformed at"<< QString::number(i) << "is" << malformedChar;
            break;
        }

    }

    if (malformedBool) {
        QString fixText = "";
        QString testChar;

        for (int i = 0; i < malformed; i++) {
            fixText.append(hexSplit.at(i));
            fixText.append(" ");
        }


        testChar.append(malformedChar);
        testChar.toUInt(&ok, 16);

        // qDebug() << __FILE__ << "/" << __LINE__  << __FUNCTION__ << "malformed digitvalue" << malformedChar.digitValue();

        if (ok) {
            fixText.append(hexSplit.at(malformed).at(0));
            fixText.append(hexSplit.at(malformed).at(1));
            fixText.append(" ");
            fixText.append(malformedChar);
        }
        hexText = (fixText.simplified());
        hex = hexText;
        hexSplit = hexText.split(" ");
    }



    for (int i = 0; i < hexSplit.size(); i++) {
        convertInt = hexSplit.at(i).toUInt(&ok, 16);
        // qDebug() << __FILE__ << "/" << __LINE__ << __FUNCTION__  <<"hex at"<< QString::number(i) << "is" << QString::number(convertInt);
        if (ok) {
            if (convertInt >= 0x20 && convertInt <= 0x7e && convertInt != '\\') {
                // qDebug() << __FILE__ << "/" << __LINE__  << __FUNCTION__ << "Converted to " << QChar(convertInt);
                asciiText.append((QChar(convertInt)));
            } else {
                asciiText.append("\\");
                switch ((char)convertInt) {
                    case '\n':
                        asciiText.append("n");
                        break;
                    case '\r':
                        asciiText.append("r");
                        break;
                    case '\t':
                        asciiText.append("t");
                        break;
                    case '\\':
                        asciiText.append("\\");
                        break;
                    default:
                        if (convertInt < 16) {
                            asciiText.append("0");
                        }
                        asciiText.append(QString::number(convertInt, 16));
                        break;

                }

            }

        } else {
            // qDebug() << __FILE__ << "/" << __LINE__  << __FUNCTION__ << "Convert failed";
            hexSplit[i] = "";
            hex = (hexSplit.join(" "));
        }

    }


    return asciiText;

}
int Packet::hexToInt(QChar hex)
{
    hex = hex.toLower();

    if (hex == 'f') {
        return 15;
    }
    if (hex == 'e') {
        return 14;
    }
    if (hex == 'd') {
        return 13;
    }
    if (hex == 'c') {
        return 12;
    }
    if (hex == 'b') {
        return 11;
    }
    if (hex == 'a') {
        return 10;
    }

    return hex.digitValue();

}

QString Packet::ASCIITohex(QString &ascii)
{
    if (ascii.isEmpty()) {
        return "";
    }

    QString asciiText = ascii;
    QString hexText = "";
    QChar tempChar1, tempChar2;
    QChar charTest;
    QString convertTest;
    bool msb = false;
    bool lsb = false;
    int lsbInt = 0;
    int msbInt = 0;

    // qDebug() << __FILE__ << "/" << __LINE__;

    //convert special sequences to raw numbers.
    asciiText.replace("\\\\", "\\" + QString::number('\\', 16));
    asciiText.replace("\\n", "\\0" + QString::number('\n', 16));
    asciiText.replace("\\r", "\\0" + QString::number('\r', 16));
    asciiText.replace("\\t", "\\0" + QString::number('\t', 16));

    // qDebug() << __FILE__ << "/" << __LINE__;
    if (asciiText.size() > 0) {
        if (asciiText.at(asciiText.size() - 1) == '\\') { //last char is a slash
            asciiText.append("00");
        }
    }

    // qDebug() << __FILE__ << "/" << __LINE__;
    if (asciiText.size() > 2) {
        if (asciiText.at(asciiText.size() - 2) == '\\') { //second last char is a slash
            //slide 0 in between

            // qDebug() << __FILE__ << "/" << __LINE__ <<"second last is slash";

            charTest = asciiText.at(asciiText.size() - 1);
            asciiText[asciiText.size() - 1] = '0';
            asciiText.append(charTest);
        }
    }
    // qDebug() << __FILE__ << "/" << __LINE__ <<"analyze" << asciiText;


    for (int i = 0 ; i < asciiText.size(); i++) {
        msb = false;
        lsb = false;
        lsbInt = 0;
        msbInt = 0;

        charTest = asciiText.at(i);

        // qDebug() << __FILE__ << "/" << __LINE__ <<"checking" << charTest;

        if (charTest == '\\') {
            // qDebug() << __FILE__ << "/" << __LINE__ <<"found slash";
            if (i + 1 < asciiText.size()) {
                msbInt = hexToInt(asciiText.at(i + 1));
                if (msbInt > -1) {
                    msb = true;
                }
                // qDebug() << __FILE__ << "/" << __LINE__ <<"msb convert test is" << msb;

            }
            if (i + 2 < asciiText.size()) {
                lsbInt = hexToInt(asciiText.at(i + 2));
                if (lsbInt > -1) {
                    lsb = true;
                }
                // qDebug() << __FILE__ << "/" << __LINE__ <<"lsb convert test is" << lsb;
            }

            if (msb) {
                hexText.append(QString::number(msbInt, 16));
                // qDebug() << __FILE__ << "/" << __LINE__ <<"hexText append result" << hexText;
                i++;
            }

            if (lsb) {
                hexText.append(QString::number(lsbInt, 16));
                // qDebug() << __FILE__ << "/" << __LINE__ <<"hexText append" << hexText;
                i++;
            }

        } else {
            // qDebug() << __FILE__ << "/" << __LINE__ <<"no slash";
            lsbInt = ((int) charTest.toLatin1()) & 0xff;
            if (lsbInt > 0 && lsbInt < 16) {
                hexText.append("0");
            }
            hexText.append(QString::number(lsbInt, 16));
            // qDebug() << __FILE__ << "/" << __LINE__ <<"appended lsbInt:" << QString::number(lsbInt, 16);
        }

        hexText.append(" ");
        // qDebug() << __FILE__ << "/" << __LINE__ <<"hex test now " << hexText;

    }

    return hexText;

}


