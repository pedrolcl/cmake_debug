#include <QCoreApplication>
#include <QDebug>

#if defined(USE_TEXT_CODECS)
#include <QTextCodec>
#endif

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString helloString = "こんにちは世界";

#if defined(USE_TEXT_CODECS)
    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
    QByteArray encodedData = codec->fromUnicode(helloString);
    qDebug() << "Encoded bytes:" << encodedData.toHex();
    QString decodedString = codec->toUnicode(encodedData);
    qDebug() << "Decoded string:" << decodedString;
#else
    qDebug() << helloString;
#endif
}
