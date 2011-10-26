#include <QtCore/QCoreApplication>

#include "sgui/Decompressor.h"

#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path("E:\\Dumb_stuff\\test.sgui");

    Decompressor dc;
    int result = dc.open(path);
    switch(result){
    case Decompressor::CANNOT_ACCESS:
        cout << "ERROR: Can't open file!" << endl;
        return -1;
    case Decompressor::INVALID_FORMAT:
        cout << "ERROR: Invalid file format!" << endl;
        return -1;
    default:
        break;
    }

    QString testfile("testdir/tesfile.txt");
    std::cout << QString(dc.getFile(testfile)).toStdString() << std::endl;

    return a.exec();
}
