#ifndef COMPRESSOR_H
#define COMPRESSOR_H

#include <QFile>
#include <QDataStream>
#include <QByteArray>
#include <QStringList>

#include <iostream>
using namespace std;

class Compressor{
private:
    QFile * out;
    QDataStream * sout;
public:
    // SGUI file header (Magic Numbers)
    static const char * SGUI_4BYTES_HEADER;

    Compressor(const char * output_file);
    ~Compressor();
    bool compress(const char * source_directory, const QStringList& filelist);
};

#endif // COMPRESSOR_H
