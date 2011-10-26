#ifndef DIRECTORYPROCESSOR_H
#define DIRECTORYPROCESSOR_H

#include <QString>
#include <QStringList>

#include <QFileInfo>
#include <QDir>

#include <QRegExp>

#include <iostream>
using namespace std;

class DirectoryProcessor{
private:
    static void getContent(QStringList& list, const QString& base, const QString& path){
        QDir dir(base+path);
        QStringList::iterator i;
        QStringList files = dir.entryList(QDir::Files);
        for(i=files.begin(); i!=files.end(); i++){
           list.append(path+(*i));
        }

        QStringList dirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(i=dirs.begin(); i!=dirs.end(); i++){
           getContent(list, base, path+(*i)+"/");
        }
    }

public:
    static QStringList list(const char * source_directory) throw (int){
        QStringList filelist;
        QString qbase(source_directory);
        if(!QRegExp(".*[\\|/]$").exactMatch(qbase)){
            qbase.append("/");
        }

        QFileInfo dir(qbase);
        if(!dir.isDir()){
            cout << "ERROR: Source is not a directory!" << endl;
            throw -1;
        }
        if(!dir.isReadable()){
            cout << "ERROR: Cannot access source directory!" << endl;
            throw -1;
        }

        cout << "Source directory: " << qbase.toStdString() << endl;

        getContent(filelist, qbase, "");

        cout << "\t" << filelist.length() << " files found!" << endl;

        return filelist;
    }
};

#endif // DIRECTORYPROCESSOR_H
