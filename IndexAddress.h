#ifndef INDEXADDRESS_H
#define INDEXADDRESS_H

#include <QString>

//Class for Storing Index Data
class IndexAddress{
public:
    QString filename;
    int word;
    IndexAddress();
    IndexAddress(QString,int);

    bool operator ==(const IndexAddress &ia){
        return (ia.filename == this->filename  && ia.word==this->word);
    }

    virtual operator QString(){
        return "(" + filename + " : " + QString::number(word) + ")";
    }
};

IndexAddress::IndexAddress(){

}

IndexAddress::IndexAddress(QString fn,int n){
    filename = fn;
    word = n;
}

#endif // INDEXADDRESS_H
