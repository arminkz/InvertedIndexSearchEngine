#ifndef TREE_H
#define TREE_H

#include "BSNode.h"
#include "Stack.h"
#include <QString>
#include <QTextEdit>

template <class T>
class BST
{
public:
	//Constructor / Destructor
	BST();
	~BST();

	//Insert / Remove
	void insert(QString,T);
	void remove(QString);
	BSNode<T>* search(QString);
	bool isEmpty();

	//Iterator
	void iterBegin();
	bool iterHasNext();
	BSNode<T> * iterNext();

	//Print
	QString preOrderPrint();
	QString inOrderPrint();
	QString postOrderPrint();
	
	virtual operator QString();

private:
	BSNode<T> *root;
	void destroy(BSNode<T>*);
    BSNode<T>* insert(BSNode<T>*,QString, T);
    BSNode<T>* remove(BSNode<T> *,QString);
	BSNode<T>* searchUtility(BSNode<T>*, QString);

    BSNode<T>* minValueNode(BSNode<T> *);

	Stack<BSNode<T> *> iterStack;
	void iterPushAll(BSNode<T> *);


    BSNode<T>* rightRotate(BSNode<T>*);
    BSNode<T>* leftRotate(BSNode<T>*);

    int max(int,int);
    int height(BSNode<T>*);
    int getBalance(BSNode<T>*);

	void preOrderPrintUtility(BSNode<T>*,QString&);
	void inOrderPrintUtility(BSNode<T>*,QString&);
	void postOrderPrintUtility(BSNode<T>*,QString&);
};

template <class T>
BST<T>::BST()
{
	root = NULL;
}

template <class T>
BST<T>::~BST()
{
	destroy(root);
}

template <class T>
void BST<T>::destroy(BSNode<T> * node) {
	if (!node) return;
	destroy(node->LC);
	destroy(node->RC);
	delete node;
}

template <class T>
void BST<T>::insert(QString key,T dataIn)
{
    root = insert(root,key, dataIn);
}

//Utility function for insert
template <class T>
BSNode<T>* BST<T>::insert(BSNode<T>* node, QString key, T dataIn)
{
    /*if (temp == 0)
        temp = new BSNode<T>(key,dataIn);
	else
	{
        if (key < temp->key) {
            insert(temp->LC,key, dataIn);
		}
        else if (key >(temp)->key)
		{
            insert(temp->RC, key, dataIn);
		}
		else{
				
		}
    }*/


    if (node == NULL)
        return new BSNode<T>(key,dataIn);

    if (key < node->key)
        node->LC  = insert(node->LC, key, dataIn);
    else if (key > node->key)
        node->RC = insert(node->RC, key,dataIn);
    else // Equal keys are not allowed in BST
        return node;

    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->LC),
                           height(node->RC));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->LC->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->RC->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->LC->key)
    {
        node->LC =  leftRotate(node->LC);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->RC->key)
    {
        node->RC = rightRotate(node->RC);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;

}

template <class T>
void BST<T>::remove(QString key)
{
	root = remove(root, key);
}

//utility function for remove
template <class T>
BSNode<T> * BST<T>::remove(BSNode<T> * p, QString key)
{
	// base case
	if (p == NULL) return p;

	// search for node 
	if (key < p->key)
		p->LC = remove(p->LC, key);

	else if (key > p->key)
		p->RC = remove(p->RC, key);

	// node found !
	else
	{
		// node with only one child or no child
		if (p->LC == NULL)
		{
			BSNode<T> *temp = p->RC;
			delete p;
			return temp;
		}
		else if (p->RC == NULL)
		{
			BSNode<T> *temp = p->LC;
			delete p;
			return temp;
		}

		// node with two children: Get the inorder successor (smallest
		// in the right subtree)
		BSNode<T> * temp = minValueNode(p->RC);

		// Copy the inorder successor's content to this node
		p->key = temp->key;
		p->data = temp->data;

		// Delete the inorder successor
		p->RC = remove(p->RC, temp->key);
	}
	return p;
}

template <class T>
BSNode<T> * BST<T>::minValueNode(BSNode<T> * node)
{
	BSNode<T> * current = node;
	while (current->LC != NULL)
		current = current->LC;
	return current;
}

template <class T>
bool BST<T>::isEmpty() {
	return root == NULL;
}

template <class T>
void BST<T>::iterBegin() {
	while (!iterStack.isEmpty()) {
		iterStack.pop();
	}
	iterPushAll(root);
}

template <class T>
void BST<T>::iterPushAll(BSNode<T> * p) {
	while (p != NULL) {
		iterStack.push(p);
		p = p->LC;
	}
}

template <class T>
bool BST<T>::iterHasNext() {
	return !iterStack.isEmpty();
}

template <class T>
BSNode<T>* BST<T>::iterNext() {
	BSNode<T> * temp;
	int s = iterStack.pop(temp);
	if (s) {
		iterPushAll(temp->RC);
		return temp;
	}
}

template <class T>
QString BST<T>::preOrderPrint()
{
	QString result = "";
	preOrderPrintUtility(root,result);
	return result;
}

template <class T>
void BST<T>::preOrderPrintUtility(BSNode<T>* temp,QString & out)
{
	if (temp != 0)
	{
        out += *temp + "\n";
		preOrderPrintUtility(temp->LC, out);
		preOrderPrintUtility(temp->RC,out);
	}
}

//Prints inOrder (HTML Format)
template <class T>
QString BST<T>::inOrderPrint()
{
    QString result = "<table>";
	inOrderPrintUtility(root,result);
    result += "</table>";
	return result;
}

template <class T>
void BST<T>::inOrderPrintUtility(BSNode<T>* temp,QString & out)
{
	if (temp != 0)
	{
		inOrderPrintUtility(temp->LC,out);
        out += "<tr><td><font color=\"darkkhaki\">" + temp->key + "</font></td><td> -&gt; </td><td>" + temp->data + "</td></tr>";
		inOrderPrintUtility(temp->RC,out);
	}
}


template <class T>
QString BST<T>::postOrderPrint()
{
	QString result = "";
	postOrderPrintUtility(root,result);
	return result;
}

template <class T>
void BST<T>::postOrderPrintUtility(BSNode<T>* temp, QString & out)
{
	if (temp != 0)
	{
		postOrderPrintUtility(temp->LC,out);
		postOrderPrintUtility(temp->RC,out);
        out += *temp + "\n";
	}
}

template <class T>
BSNode<T>* BST<T>::search(QString key)
{
	return searchUtility(root, key);
}

template <class T>
BSNode<T>* BST<T>::searchUtility(BSNode<T>* leaf, QString key)
{
	if (leaf != NULL)
	{
		if (key == leaf->key)
			return leaf;
		if (key < leaf->key)
			return searchUtility(leaf->LC, key);
		else
			return searchUtility(leaf->RC, key);
	}
	else
		return NULL;
}

template <class T>
BST<T>::operator QString() {
	return inOrderPrint();
}

template <class T>
int BST<T>::height(BSNode<T> * N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

template <class T>
int BST<T>::max(int a, int b)
{
    return (a > b)? a : b;
}
template <class T>
int BST<T>::getBalance(BSNode<T>* N)
{
    if (N == NULL)
        return 0;
    return height(N->LC) - height(N->RC);
}

template <class T>
BSNode<T>* BST<T>::rightRotate(BSNode<T>* y)
{
    BSNode<T>* x = y->LC;
    BSNode<T>* T2 = x->RC;

    // Perform rotation
    x->RC = y;
    y->LC = T2;

    // Update heights
    y->height = max(height(y->LC), height(y->RC))+1;
    x->height = max(height(x->LC), height(x->RC))+1;

    // Return new root
    return x;
}

template <class T>
BSNode<T>* BST<T>::leftRotate(BSNode<T>* x)
{
    BSNode<T>* y = x->RC;
    BSNode<T>* T2 = y->LC;

    // Perform rotation
    y->LC = x;
    x->RC = T2;

    //  Update heights
    x->height = max(height(x->LC), height(x->RC))+1;
    y->height = max(height(y->LC), height(y->RC))+1;

    // Return new root
    return y;
}

#endif 
