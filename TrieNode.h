#ifndef TRIENODE_H
#define TRIENODE_H

template <class T>
class Trie;

template<class T>
class TrieNode
{
	friend class Trie<T>;
public:
	TrieNode();

	T data;
	bool tag;

	TrieNode<T>* parent;
	TrieNode<T>* children[26];
	
};

template<class T>
TrieNode<T>::TrieNode() {
	for (int i = 0;i < 26;i++) {
		children[i] = NULL;
	}
	tag = false;
}


#endif // !TRIENODE_H
