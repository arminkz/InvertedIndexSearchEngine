#ifndef TSNODE_H
#define TSNODE_H

#include <QString>

template <class T>
class TST;

template <class T>
class TSNode
{
	friend class TST<T>;

public:
	TSNode();
	TSNode(QChar);

	T data;
	QChar key;
	bool tag;

	TSNode<T>* LC; //pointer to left child
	TSNode<T>* RC; //pointer to right child
	TSNode<T>* MC; //pointer to middle child 

	virtual operator QString() {
		QString result = "";
		result += key;
		result += " -> " + data;
		return result;
	}

private:

};

template <class T>
TSNode<T>::TSNode()
{
	tag = false;
	LC = 0;
	RC = 0;
	MC = 0;
}

template <class T>
TSNode<T>::TSNode(QChar keyIn)
{
	tag = false;
	key = keyIn;
	LC = 0;
	RC = 0;
	MC = 0;
	//Do not set data (data is only for node's with positive tag) !
}

#endif // TSNODE_H