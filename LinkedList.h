#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LLNode.h"
#include <QString>
#include <iostream>


template <class T>
class LinkedList
{
public:
    LinkedList();  //constructor
    ~LinkedList(); //destructor
    void addWithSort(T);
    void add(T);
	bool isEmpty();
	int count();
	void remove(int);

	LLNode<T> * nodeAt(int);
	LLNode<T>* search(T);
    QString toString();
	
	LLNode<T> * startPtr;
	LLNode<T> * endPtr;

	LLNode<T> * iterPtr;
	LLNode<T> * iterPrevPtr;
	LLNode<T> * iterPrev2Ptr;
	void iterBegin();
	bool iterHasNext();
	LLNode<T> * iterNext();
	void iterDel();

    virtual operator QString(){
        return toString();
    }

private:
    void insertBegin(T);
    void insertEnd(T);
};



template <class T>
LinkedList<T>::LinkedList() //creates list with start and end as NULL
{
    startPtr = 0;
    endPtr = 0;
}

template <class T>
LinkedList<T>::~LinkedList()
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
bool LinkedList<T>::isEmpty()
{
    return (startPtr == 0);
}

template <class T>
int LinkedList<T>::count()
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
void LinkedList<T>::insertBegin(T dataIn)
{
    if(isEmpty())
    {
        LLNode<T> * newPtr = new LLNode<T>(dataIn);
        startPtr = newPtr;
        endPtr = newPtr;
    }else
    {
        LLNode<T> * newPtr = new LLNode<T>(dataIn);
        newPtr->link = startPtr;
        startPtr = newPtr;
    }
}

template <class T>
void LinkedList<T>::insertEnd(T dataIn)
{
    if(isEmpty())
    {
        LLNode<T> * newPtr = new LLNode<T>(dataIn);
        startPtr = newPtr;
        endPtr = newPtr;
    }else
    {
        LLNode<T> * newPtr = new LLNode<T>(dataIn);
        endPtr->link = newPtr;
        endPtr = newPtr;
    }
}

template <class T>
void LinkedList<T>::add(T dataIn) //adds node (without sort)
{
    insertBegin(dataIn);
}

template <class T>
void LinkedList<T>::addWithSort(T dataIn) //adds node (with sort)
{
    if(isEmpty())
    {
        insertBegin(dataIn);
    }else
    {
        if(dataIn < startPtr->data)
        {
            insertBegin(dataIn);
        }
        else if(dataIn >= endPtr->data)
        {
            insertEnd(dataIn);
        }
        else
        {
            LLNode<T> * currentPtr = startPtr;
            LLNode<T> * newPtr = new LLNode<T>(dataIn);
            while(currentPtr != endPtr)
            {
                if((newPtr->data < currentPtr->link->data) && (newPtr->data >= currentPtr->data))
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
LLNode<T> * LinkedList<T>::nodeAt(int n)
{
	LLNode<T> * p = startPtr;
	while (n) {
		p = p->link;
		n--;
	}
	return p;
}

template<class T>
void LinkedList<T>::remove(int n) 
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
QString LinkedList<T>::toString()
{
    if(isEmpty())
    {
        return "n/a";

    }else
    {
        QString res = " ";
        LLNode<T> * currentPtr = startPtr;
        bool first = true;

        while(currentPtr != 0)
        {
            if(!first){
                res += " , ";
            }else{
                first = false;
            }

			QString ta = currentPtr->data;
			res += ta;
            currentPtr = currentPtr->link;
        }
        res += " ";
        return res;
    }
}

template <class T>
void LinkedList<T>::iterBegin() {
	iterPrev2Ptr = NULL;
	iterPrevPtr = NULL;
	iterPtr = startPtr;
}

template <class T>
bool LinkedList<T>::iterHasNext() {
	return iterPtr != NULL;
}

template <class T>
LLNode<T> * LinkedList<T>::iterNext() {
	LLNode<T> * res = iterPtr;
	iterPrev2Ptr = iterPrevPtr;
	iterPrevPtr = iterPtr;
	iterPtr = iterPtr->link;
	return res;
}

template <class T>
void LinkedList<T>::iterDel() {
	if (iterPrevPtr) {
		if (iterPrev2Ptr) {
			iterPrev2Ptr->link = iterPrevPtr->link;
			delete iterPrevPtr;
		}
		else {
			startPtr = iterPrevPtr->link;
			delete iterPrevPtr;
			iterPrev2Ptr = NULL;
			iterPrevPtr = NULL;
			iterPtr = startPtr;
		}
	}

}

/*template <class T>
LLNode<T>* LinkedList<T>::search(T key)
{
    LLNode<T>* nodePtr;
    bool found = false;

    nodePtr = startPtr;

    while((!found) && (nodePtr != NULL)) //runs through list until data is found within a node or end of list is reached
    {
        if(nodePtr->data == key) //if the node's data equals the key then the node has been found
            found = true;
        else
            nodePtr = nodePtr->nextPtr; //moves to next node in list
    }
    return nodePtr; //returns pointer to the node that contains data equal to key (NULL if not found)
}*/

#endif // LINKEDLIST_H
