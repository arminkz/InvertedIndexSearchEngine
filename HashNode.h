#ifndef HASHNODE_H
#define HASHNODE_H

template <class T>
class HashNode
{

public:
    HashNode(QString,T);
    T data;
    QString key;
    HashNode<T>* next; //pointer to next hash node (chaining)

    virtual operator QString() {
        QString result = key +  " -> " + data;
        return result;
    }

private:

};

template <class T>
HashNode<T>::HashNode(QString key,T data){
	this->key = key;
    this->data = data;
	this->next = NULL;
}


#endif // HASHNODE_H
