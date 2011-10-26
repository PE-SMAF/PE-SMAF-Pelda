#include "Decompressor.h"

#define SD Decompressor

const char SD::SGUI_4BYTES_HEADER[] = {'S', 'G', 'U', 'I', '\0'};

SD::Decompressor(){
    files = new QMap<QString, QByteArray>;
}

SD::~Decompressor(){
    delete files;
}

int SD::open(const QString &file){
    QFile sgui(file);
    if(!sgui.open(QIODevice::ReadOnly)){
        return SD::CANNOT_ACCESS;
    }
    QByteArray content = sgui.readAll();
    sgui.close();

    return parseContent(&content);
}

bool SD::hasFile(const QString &name){
    return (files->find(name) != files->end());
}

QByteArray SD::getFile(const QString &name){
    QMap<QString, QByteArray>::const_iterator i;
    if((i = files->find(name)) != files->end()){
        return qUncompress(i.value());
    }
    return QByteArray();
}

int SD::parseContent(QByteArray * content){
    if(content->length() < 4){
        return SD::INVALID_FORMAT;
    }
    QDataStream in(content, QIODevice::ReadOnly);
    char header[5];
    in.readRawData(header, 4);
        header[4] = '\0';

    if(strcmp(header, SD::SGUI_4BYTES_HEADER) != 0){
        return SD::INVALID_FORMAT;
    }

    QString identifier;
    int size;
    char * buffer;
    QByteArray * file;
    while(true){
        identifier = readChars(&in);
        if(identifier.isEmpty()){
            return SD::INVALID_FORMAT;
        }
        if(in.atEnd()){
            return SD::INVALID_FORMAT;
        }
        in >> size;
        if(in.atEnd()){
            return SD::INVALID_FORMAT;
        }

        buffer = new char[size];
        in.readRawData(buffer, size);
        file = new QByteArray(buffer, size);

        files->insert(identifier, *file);

        delete file;
        delete buffer;

        if(in.atEnd()){
            break;
        }
    }
    return SD::SUCCESS;
}

QString SD::readChars(QDataStream *stream){
    QString buffer;
    char * c = new char[1];
    while(true){
        if(stream->atEnd()){
            return QString();
        }
        stream->readRawData(c, 1);
        if(c[0] == 0){
            return buffer;
        }
        buffer.append(c[0]);
    }
    return QString();
}
