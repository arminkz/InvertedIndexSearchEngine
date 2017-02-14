#ifndef LINKEDLIST_H_A
#define LINKEDLIST_H_A

#include "LLNode.h"
#include <QString>
#include <iostream>


template <class T>
class LinkedListA
{
public:
	LinkedListA();  //constructor
	~LinkedListA(); //destructor
	void addWithSort(T);
	void add(T);
	bool isEmpty();
	int count();
	void remove(int);

	LLNode<T> * nodeAt(int);
	LLNode<T>* search(T);

	LLNode<T> * startPtr;
	LLNode<T> * endPtr;

	LLNode<T> * iterPtr;
	LLNode<T> * iterPrevPtr;
	void iterBegin();
	bool iterHasNext();
	LLNode<T> * iterNext();
	void iterDel();

private:
	void insertBegin(T);
	void insertEnd(T);
};



template <class T>
LinkedListA<T>::LinkedListA() //creates list with start and end as NULL
{
	startPtr = 0;
	endPtr = 0;
}

template <class T>
LinkedListA<T>::~LinkedListA()
{
	/* if (!isEmpty())
	{
	LLNode<T> * currentPtr = startPtr;
	LLNode<T> * tempPtr;

	while (currentPtr != 0) // delete remaining nodes
	{
	tempPtr = currentPtr;
	currentPtr = currentPtr->link;
	delete tempPtr;
	}
	}*/
}


template <class T>
bool LinkedListA<T>::isEmpty()
{
	return (startPtr == 0);
}

template <class T>
int LinkedListA<T>::count()
{
	int c = 0;
	LLNode<T> * p = startPtr;
	while (p != NULL) {
		c++;
		p = p->link;
	}
	return c;
}

template <class T>
void LinkedListA<T>::insertBegin(T dataIn)
{
	if (isEmpty())
	{
		LLNode<T> * newPtr = new LLNode<T>(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	}
	else
	{
		LLNode<T> * newPtr = new LLNode<T>(dataIn);
		newPtr->link = startPtr;
		startPtr = newPtr;
	}
}

template <class T>
void LinkedListA<T>::insertEnd(T dataIn)
{
	if (isEmpty())
	{
		LLNode<T> * newPtr = new LLNode<T>(dataIn);
		startPtr = newPtr;
		endPtr = newPtr;
	}
	else
	{
		LLNode<T> * newPtr = new LLNode<T>(dataIn);
		endPtr->link = newPtr;
		endPtr = newPtr;
	}
}

template <class T>
void LinkedListA<T>::add(T dataIn) //adds node (without sort)
{
	insertBegin(dataIn);
}

template <class T>
void LinkedListA<T>::addWithSort(T dataIn) //adds node (with sort)
{
	if (isEmpty())
	{
		insertBegin(dataIn);
	}
	else
	{
		if (dataIn < startPtr->data)
		{
			insertBegin(dataIn);
		}
		else if (dataIn >= endPtr->data)
		{
			insertEnd(dataIn);
		}
		else
		{
			LLNode<T> * currentPtr = startPtr;
			LLNode<T> * newPtr = new LLNode<T>(dataIn);
			while (currentPtr != endPtr)
			{
				if ((newPtr->data < currentPtr->link->data) && (newPtr->data >= currentPtr->data))
				{
					LLNode<T> * next = currentPtr->link;
					currentPtr->link = newPtr;
					newPtr->link = next;
					break;
				}
				currentPtr = currentPtr->link; //moves to the next node in the list
			}
		}
	}
}

template<class T>
LLNode<T> * LinkedListA<T>::nodeAt(int n)
{
	LLNode<T> * p = startPtr;
	while (n) {
		p = p->link;
		n--;
	}
	return p;
}

template<class T>
void LinkedListA<T>::remove(int n)
{
	LLNode<T> * q = 0;
	LLNode<T> * p = startPtr;
	while (n) {
		q = p;
		p = p->link;
		n--;
	}

	if (p != NULL) {
		if (q != NULL) {
			q->link = p->link;
			delete p;
		}
		else {
			startPtr = p->link;
			delete p;
		}
	}


}


template <class T>
void LinkedListA<T>::iterBegin() {
	iterPrevPtr = NULL;
	iterPtr = startPtr;
}

template <class T>
bool LinkedListA<T>::iterHasNext() {
	return iterPtr != NULL;
}

template <class T>
LLNode<T> * LinkedListA<T>::iterNext() {
	LLNode<T> * res = iterPtr;
	iterPrevPtr = iterPtr;
	iterPtr = iterPtr->link;
	return res;
}

template <class T>
void LinkedListA<T>::iterDel() {
	if (startPtr && iterPtr) {
		if (iterPrevPtr) {
			iterPrevPtr->link = iterPtr->link;
			delete iterPtr;
		}
		else {
			startPtr = iterPtr->link;
			delete iterPtr;
			iterPtr = startPtr;
			iterPrevPtr = NULL;
		}
	}

}

#endif // LINKEDLIST_H
