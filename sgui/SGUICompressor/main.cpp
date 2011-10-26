#include <iostream>

#include <QtCore/QCoreApplication>

#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QTextStream>

#include "DirectoryProcessor.h"
#include "Compressor.h"

using namespace std;

const char * HEADER = "SGUI";

int main(int argc, char *argv[])
{
    if(argc != 3){
        cout
                << "SGUI compressor for Scriptable Markup based Application Framework" << endl << endl
                << "Usage: " << argv[0] << " source_directory target_file" << endl << endl;
        return 0;
    }

    QStringList filelist;
    try{
        filelist.append(DirectoryProcessor::list(argv[1]));
    }catch(int){
        return -1;
    }

    try{
        Compressor * cp = new Compressor(argv[2]);
        cp->compress(argv[1], filelist);
        delete cp;
    }catch(int){
        return -1;
    }

    return 0;
}
