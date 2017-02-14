#ifndef HASHMAP_H
#define HASHMAP_H

#include "HashNode.h"
#include <QString>

template <class T>
class HashMap
{
public:
    //Constructor / Destructor
    HashMap();
    ~HashMap();

    void put(QString,T);
    HashNode<T>* get(QString);
    void remove(QString);

    QString printHtml();

private:
    HashNode<T> **table;
    unsigned long hashFunc(QString);
};

template <class T>
HashMap<T>::HashMap(){
    table = new HashNode<T>*[2000]();
}

template <class T>
HashMap<T>::~HashMap(){
    for (int i = 0; i < 2000; ++i) {
        HashNode<T> *entry = table[i];
        while (entry != NULL) {
            HashNode<T> *prev = entry;
            entry = entry->next;
            delete prev;
        }
        table[i] = NULL;
    }
    // destroy the hash table
    delete [] table;
}

template <class T>
unsigned long HashMap<T>::hashFunc(QString key){
    return qHash(key) % 1999 + 1;
}

template <class T>
void HashMap<T>::put(QString key, T value) {
    unsigned long hashValue = hashFunc(key);

    HashNode<T> *prev = NULL;
    HashNode<T> *entry = table[hashValue];

    while (entry != NULL && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == NULL) {
        entry = new HashNode<T>(key, value);
        if (prev == NULL) {
            // insert as first
            table[hashValue] = entry;
        } else {
            prev->next = entry;
        }
    } else {
        // just update the value
        entry->data = value;
    }
}

template <class T>
void HashMap<T>::remove(QString key) {
    unsigned long hashValue = hashFunc(key);
    HashNode<T> *prev = NULL;
    HashNode<T> *entry = table[hashValue];

    while (entry != NULL && entry->key != key) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == NULL) {
        // key not found
        return;
    }
    else {
        if (prev == NULL) {
            // remove first bucket of the list
            table[hashValue] = entry->next;
        } else {
            prev->next = entry->next;
        }
        delete entry;
    }
}

template <class T>
HashNode<T>* HashMap<T>::get(QString key){
    unsigned long hashValue = hashFunc(key);
    HashNode<T> *entry = table[hashValue];

    while (entry != NULL) {
        if (entry->key == key) {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}

template <class T>
QString HashMap<T>::printHtml()
{
    QString html = "<table>";

    for(int i=0;i<2000;i++){
        HashNode<T>* entry = table[i];
        while(entry != NULL){
            html += "<tr><td><font color=\"darkkhaki\">" + entry->key + "</font></td><td> -&gt; </td><td>" + entry->data + "</td></tr>";
            entry = entry->next;
        }
    }

    html += "</table>";
    return html;

}

#endif // HASHMAP_H
