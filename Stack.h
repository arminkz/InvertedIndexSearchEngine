#ifndef STACK_H
#define STACK_H

#include "LLNode.h"
#include "LinkedListA.h"

template<class T>
class Stack {
private:
	LinkedListA<T> * A;
public :
	Stack();
	void push(T data);
	int pop(T &data);
	int pop();

	bool isEmpty();
	//bool isFull();
};

template<class T>
Stack<T>::Stack() {
	A = new LinkedListA<T>;
}

template<class T>
bool Stack<T>::isEmpty() {
	return A->isEmpty();
}

template<class T>
void Stack<T>::push(T data) {
	A->add(data);
}

template<class T>
int Stack<T>::pop(T &data) {
	if (!isEmpty()) {
		LLNode<T> * lln = A->nodeAt(0);
		data = lln->data;
		A->remove(0);
		return 1;
	}
	return 0;
}

template<class T>
int Stack<T>::pop() {
	if (!isEmpty()) {
		A->remove(0);
		return 1;
	}
	return 0;
}

#endif
