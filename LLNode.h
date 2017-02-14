#ifndef LLNODE_H
#define LLNODE_H

template <class T>
class LinkedList;

template <class T>
class LLNode
{
    friend class LinkedList<T>;

public:
    LLNode(T); //constructor
    T data;
    LLNode* link;

private:

};

template <class T>
LLNode<T>::LLNode(T dataIn)
{
    data = dataIn;
    link = 0;
}

/*template <class T>
T ListNode<T>::getData() //returns data stored in node
{
    return data;
}*/


#endif // LLNODE_H
