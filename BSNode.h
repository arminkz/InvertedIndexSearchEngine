#ifndef BSNODE_H
#define BSNODE_H

#include <QString>

template <class T>
class BST;

template <class T>
class BSNode
{
    friend class BST<T>;

public:
    BSNode();
	~BSNode();
    BSNode(QString,T);
    T data;
    QString key;
    BSNode<T>* LC; //pointer to left child node of node
    BSNode<T>* RC; //pointer to right child node of node

	virtual operator QString() {
        QString result = "";
        result += key;
        for(int i=key.count();i<10;i++) result += " ";
        result += " -> " + data ;
		return result;
	}

private:
    int height;
};

template <class T>
BSNode<T>::BSNode()
{
    LC = 0;
    RC = 0;
}

//Destructor
template <class T>
BSNode<T>::~BSNode()
{
	
}


template <class T>
BSNode<T>::BSNode(QString keyIn, T dataIn)
{
    key = keyIn;
    data = dataIn;
    LC = 0;
    RC = 0;
    height = 1;
}

#endif // BSNODE_H
