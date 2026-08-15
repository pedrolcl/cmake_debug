#include <QCoreApplication>
#include <QDebug>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QString originalString = "こんにちは世界";

    QByteArray encodedData = codec->fromUnicode(originalString);
    qDebug() << "Encoded bytes:" << encodedData.toHex();

    QString decodedString = codec->toUnicode(encodedData);
    qDebug() << "Decoded string:" << decodedString;
}
