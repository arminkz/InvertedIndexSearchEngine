#ifndef TST_H
#define TST_H

#include <TSNode.h>
#include <QString>

template<class T>
class TST {

public:
	TST();
	~TST();
	void insert(QString,T);
	TSNode<T>* search(QString);
	QString printHtml();

private:
	TSNode<T>* root;
	void destroy(TSNode<T>*);
	TSNode<T>* insert(TSNode<T>*, QString, int, T);
	TSNode<T>* search(TSNode<T>*, QString, int);
	void printHtml(TSNode<T>*,QString,QString&);
};

template<class T>
TST<T>::TST() {
	root = NULL;
}

template<class T>
TST<T>::~TST() {
	destroy(root);
}

template<class T>
void TST<T>::destroy(TSNode<T>* node) {
	if (!node) return;
	destroy(node->LC);
	destroy(node->MC);
	destroy(node->RC);
	delete node;
}

template<class T>
void TST<T>::insert(QString key, T data) {
	root = insert(root, key, 0, data);
}

template<class T>
TSNode<T>* TST<T>::insert(TSNode<T>* p, QString key, int index,T data) {

	QChar ci = key.at(index); //char at index

	if (!p) {
		p = new TSNode<T>(ci);
	}

	if (p->key > ci)
		p->LC = insert(p->LC, key, index,data);
	else if (p->key < ci)
		p->RC = insert(p->RC, key, index,data);
	else if (index < key.count() - 1)
		p->MC = insert(p->MC, key, index + 1,data);
	else {
		//Leaf node !
		p->tag = true;
		p->data = data;
	}
		
	return p;
}

template<class T>
TSNode<T>* TST<T>::search(QString word) {
	return search(root, word, 0);
}

template<class T>
TSNode<T>* TST<T>::search(TSNode<T> * p, QString key, int index) {

	QChar ci = key.at(index); //char at index

	if (p == NULL)
		return NULL;

	if (p->key > ci)
		return search(p->LC, key, index);
	if (p->key < ci)
		return search(p->RC, key, index);
	if (index < key.count() - 1)
		return search(p->MC, key, index + 1);

	return p;
}

template<class T>
QString TST<T>::printHtml() {
	QString html = "<table>";
	printHtml(root, "", html);
	html += "</table>";
	return html;
}

template<class T>
void TST<T>::printHtml(TSNode<T>* node,QString pre,QString &result) {
	if (!node) return;

	if (node->tag) {
		result += "<tr><td><font color=\"darkkhaki\">" + pre + node->key + "</font></td><td> -&gt; </td><td>" + node->data + "</td></tr>";
	}

	printHtml(node->RC, pre , result);
	printHtml(node->MC, pre + node->key, result);
	printHtml(node->LC, pre , result);
}


#endif