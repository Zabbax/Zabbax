#include <iostream>

//node and list templates
template <typename T>
struct node {
	T data;
	node* next;

	//const and deconst
	node() { next = nullptr; }
	~node() { delete next; }
};


template <class T>
class List {
public:
	//const and deconst
	List();
	~List();

	//getters and setters
	node<T>* getHead();
	int getLength();
	node<T>* getNodeAtPosition(int n);
	void setHead(node<T>* head);

	//checks and clears
	bool isEmpty();
	void clearList();

	//insert and remove
	bool insertAtFront(T& data);
	bool removeNode(node<T>* match);

private:
	node<T>* pHead;
};

//const and deconst functions
template <class T>
List<T>::List() {
	pHead = nullptr;
}

template <class T>
List<T>::~List() {
	delete pHead;
}

//getter and setter functions
template <class T>
node<T>* List<T>::getHead() {
	return pHead;
}

template <class T>
void List<T>::setHead(node<T>* head) {
	pHead = head;
}

//functions
template <class T>
bool List<T>::isEmpty() {
	return (pHead == nullptr);
}

template <class T>
void List<T>::clearList() {
	if (!isEmpty()) {
		delete pHead;
		pHead = nullptr;
	}
}


template <class T>
int List<T>::getLength() {
	int count = 0;
	node<T>* pCurrent = this->getHead();
	while (pCurrent != nullptr) {
		pCurrent = pCurrent->next;
		count++;
	}

	return count;
}

template <class T>
node<T>* List<T>::getNodeAtPosition(int n) {
	if (n <= this->getLength() - 1) {
		node<T>* pCurrent = pHead;
		for (int i = 0; i < n; i++) {
			pCurrent = pCurrent->next;
		}

		return pCurrent;
	}
	else {
		return nullptr;
	}
}

template <class T>
bool List<T>::insertAtFront(T& data) {
	node<T>* pNew = new node<T>;
	pNew->data = data;

	if (pNew != 0) {
		if (isEmpty()) {
			pHead = pNew;
		}
		else {
			pNew->next = pHead;
			pHead = pNew;
		}

		return true;
	}

	return false;
}

template <class T>
bool List<T>::removeNode(node<T>* match) {
	node<T>* pCurrent = this->getHead();
	if (pCurrent->data == match->data) {
		this->setHead(pCurrent->next);
		delete pCurrent;
		return true;
	}
	else {
		node<T>* pPrev = pCurrent;
		pCurrent = pCurrent->next;

		while (pCurrent != nullptr) {
			if (pCurrent->data == match->data) {
				pPrev->next = pCurrent->next;
				delete pCurrent;
				return true;
			}
			pPrev = pCurrent;
			pCurrent = pCurrent->next;
		}
	}
	return false;
}