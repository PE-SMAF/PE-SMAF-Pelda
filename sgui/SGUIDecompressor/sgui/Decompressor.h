#ifndef DECOMPRESSOR_H
#define DECOMPRESSOR_H

#include <QByteArray>
#include <QString>
#include <QMap>

#include <QFile>
#include <QDataStream>

#include <iostream>
using namespace std;

class Decompressor{
private:
    QMap<QString, QByteArray> * files;

    QString readChars(QDataStream * stream);

    int parseContent(QByteArray * content);
public:
    static const char SGUI_4BYTES_HEADER[];

    enum Status{
        CANNOT_ACCESS,
        INVALID_FORMAT,
        SUCCESS
    };

    Decompressor();
    ~Decompressor();

    int open(const QString& file);
    QByteArray getFile(const QString& name);
    bool hasFile(const QString& name);
};

#endif // SGUIDECOMPRESSOR_H
