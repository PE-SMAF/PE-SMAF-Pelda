#include "Compressor.h"

// SGUI file header (Magic Numbers)
const char * Compressor::SGUI_4BYTES_HEADER = "SGUI";

Compressor::Compressor(const char * output_file){
    cout << "Target file: " << output_file << endl;
    QString ofile(output_file);
    out = new QFile(ofile);
    if(!out->open(QIODevice::WriteOnly)){
        cout << "ERROR: Cannot open target file for writing!" << endl;
        throw -1;
    }
    sout = new QDataStream(out);
    sout->setVersion(QDataStream::Qt_4_3);
}

Compressor::~Compressor(){
    out->close();
    delete sout;
    delete out;
}

bool Compressor::compress(const char * source_directory, const QStringList& filelist){
    QString qbase(source_directory);
    if(!QRegExp(".*[\\|/]$").exactMatch(qbase)){
        qbase.append("/");
    }

    sout->writeRawData(SGUI_4BYTES_HEADER, 4);
    QStringList::const_iterator i = filelist.begin();
    QByteArray * current;
    QFile * file;
    int size;
    char NULL_BYTE[] = {'\0'};
    for(; i!=filelist.end(); i++){
        try{
            cout << "\t" << (*i).toStdString() << "... " << endl;
            file = new QFile(qbase+(*i));
            file->open(QIODevice::ReadOnly);
            if(file->isOpen() && file->isReadable()){
                current = new QByteArray(file->readAll());
                size = current->length();
                current = new QByteArray(qCompress(*current, 9));
                cout << "\t\tsize: " << current->length() << " bytes (" << (float)((int)((float)(current->length())/size*10000))/100 << "%)";
                sout->writeRawData(((QString)(*i)).toStdString().c_str(), ((QString)(*i)).length());
                sout->writeRawData(NULL_BYTE, 1);

                //*sout << current->length(); // QByteArray length is written in by default, this line is not needed
                //if(current->length() > 0){
                    *sout << *current;
                //}
                delete current;
            }else{
                cout << " ERROR: Can't read!";
            }
            cout << endl;
            file->close();
            delete file;
        }catch(...){
            cout << endl << "UNKNOWN ERROR!" << endl;
        }
    }
    return true;
}
