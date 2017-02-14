#ifndef TRIE_H
#define TRIE_H

#include "TrieNode.h"
#include <QString>

template<class T>
class Trie
{
public:
	Trie();
	~Trie();
	void insert(QString,T);
	void remove(QString);
    TrieNode<T> * search(QString);
	QString printHtml();

private:
	TrieNode<T> * root;
	void destroy(TrieNode<T>*);
	void printHtml(TrieNode<T>*, QString, QString&);
	
};

template<class T>
Trie<T>::Trie() {
	root = new TrieNode<T>;
}

template<class T>
Trie<T>::~Trie() {
	destroy(root);
}

template<class T>
void Trie<T>::destroy(TrieNode<T>* node) {
	if (!node) return;

	for (int i = 0; i < 26; ++i) {
		if (node->children[i] != NULL) {
			destroy(node->children[i]);
		}
	}
	delete node;
}

template<class T>
void Trie<T>::insert(QString text, T data)
{
    TrieNode<T>* temp = root;

    for (int i =0;i < text.count();i++) {
		int index = text.at(i).toLatin1() - 'a';
        if (temp->children[index] == NULL) {
            temp->children[index] = new TrieNode<T>;
            temp->children[index]->parent = temp; // Assigning parent
		}

        temp = temp->children[index];
	}

	temp->tag = true;
    temp->data = data;      //Mark the occurence of the word
}

template<class T>
TrieNode<T>* Trie<T>::search(QString text)
{
    TrieNode<T>* temp = root;
    for(int i=0; i< text.count();i++) {
		int index = text.at(i).toLatin1() - 'a';
        if (temp->children[index] != NULL) {
            temp = temp->children[index];
        }
        else {
			return NULL;
        }
    }

	return temp;
}

template<class T>
void Trie<T>::remove(QString word)
{
	TrieNode<T>* temp = search(word);
	if (temp == NULL) {
		// Word not found
		return;
	}

	delete temp->data;   // Deleting the occurence
	temp->tag = false;
									 
	bool noChild = true;
	int childCount = 0;


	// Checking children of current node
	for (int i = 0; i < 26; ++i) {
		if (temp->children[i] != NULL) {
			noChild = false;
			++childCount;
		}
	}

	if (!noChild) {
		return;
	}

	TrieNode<T>* traverse;     // variable to assist in traversal

	while (!temp->tag == 0 && temp->parent != NULL && childCount < 2) {

		traverse = temp->parent;

		//Null up the parent node
		for (i = 0; i < 26; ++i) {
			if (temp == traverse->children[i]) {
				traverse->children[i] = NULL;
				break;
			}
		}

		//delete this node
		delete temp;
		temp = traverse;

		for (i = 0; i < 26; ++i) {
			if (temp->children[i] != NULL) {
				++childCount;
			}
		}
	}
}

template<class T>
QString Trie<T>::printHtml() {
	QString html = "<table>";
	printHtml(root, "", html);
	html += "</table>";
	return html;
}

template <class T>
void Trie<T>::printHtml(TrieNode<T>* node, QString pre, QString &result)
{

	if (!node) return;

	if (node->tag) {
		result += "<tr><td><font color=\"darkkhaki\">" + pre + "</font></td><td> -&gt; </td><td>" + node->data + "</td></tr>";
	}

	for (int i = 0; i < 26; ++i) {
		if (node->children[i] == NULL) {
			continue;
		}
		else {
			QChar c = QChar::fromLatin1((char)('a' + i));
			
			printHtml(node->children[i], pre + c, result);
		}
	}

}

#endif // !TRIE_H
