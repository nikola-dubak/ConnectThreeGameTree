#pragma once

template <typename Type>
class Queue
{
	struct Node {
		Type value;
		Node* next = nullptr;
		Node(Type value) :value(value) {}
	};
	Node* first = nullptr;
	Node* last = nullptr;
public:
	bool Empty() const {
		return !first;
	}
	void Insert(Type);
	Type& Front() const {
		return first->value;
	}
	Type Delete();
	~Queue();
};

template<typename Type>
void Queue<Type>::Insert(Type value) {
	Node* node = new Node(value);
	if (!first) {
		first = last = node;
		return;
	}
	last->next = node;
	last = node;
}

template<typename Type>
Type Queue<Type>::Delete() {
	Node* current = first;
	Type value = current->value;
	first = first->next;
	delete current;
	return value;
}

template <typename Type>
Queue<Type>::~Queue() {
	if (!first) return;
	Node* current;
	while (first) {
		current = first;
		first = first->next;
		delete current;
	}
}
