#pragma once
#include <iostream>
#include "Queue.h"
using namespace std;

template <typename Type>
class Tree
{
protected:
	int order;
	struct Node {
		Type value;
		Node* parent = nullptr;
		Node** children;
		Node(Type value, int order) :value(value) {
			children = new Node*[order]();
		}
		~Node() { delete[] children; }
	};
	Node* root = nullptr;
public:
	explicit Tree(int order) :order(order) {}
	void Insert(Type);
	int Width() const;
	void Print() const;
	~Tree();
};

template <typename Type>
void Tree<Type>::Insert(Type value) {
	Node* node = new Node(value, order);
	if (!root) {
		root = node;
		return;
	}
	Node* current;
	Queue<Node*> queue;
	queue.Insert(root);
	while (!queue.Empty()) {
		current = queue.Delete();
		for (int i = 0; i < order; i++) {
			if (current->children[i]) {
				queue.Insert(current->children[i]);
			}
			else {
				node->parent = current;
				current->children[i] = node;
				return;
			}
		}
	}
}

template<typename Type>
int Tree<Type>::Width() const {
	if (!root) return 0;
	int maxWidth = 0, currentWidth = 0;
	Node* current;
	Queue<Node*> queue;
	queue.Insert(root);
	queue.Insert(nullptr);
	while (queue.Front()) {
		current = queue.Delete();
		currentWidth++;
		for (int i = 0; i < order; i++) {
			if (current->children[i]) {
				queue.Insert(current->children[i]);
			}
		}
		if (!queue.Front()) {
			queue.Insert(nullptr);
			queue.Delete();
			if (currentWidth > maxWidth)
				maxWidth = currentWidth;
			currentWidth = 0;
		}
	}
	queue.Delete();
	return maxWidth;
}

template <typename Type>
void Tree<Type>::Print() const {
	if (!root) { 
		cout << "Stablo je prazno!" << endl; // Tree is empty!
		return; 
	}
	int level = 1;
	Node* current;
	Queue<Node*> queue;
	queue.Insert(root);
	queue.Insert(nullptr);
	while (queue.Front()) {
		current = queue.Delete();
		for (int i = 0; i < order; i++) {
			if (current->children[i]) {
				queue.Insert(current->children[i]);
			}
		}
		cout << current->value << ' ';
		if (!queue.Front()) {
			queue.Insert(nullptr);
			queue.Delete();
			level++; 
			cout << endl;
		}
		else if (queue.Front()->parent != current->parent) {
			cout << "| ";
		}
	}
	queue.Delete();
	cout << endl;
}

template <typename Type>
Tree<Type>::~Tree() {
	if (!root) return;
	Node* current;
	Queue<Node*> queue;
	queue.Insert(root);
	while (!queue.Empty()) {
		current = queue.Delete();
		for (int i = 0; i < order; i++) {
			if (current->children[i]) {
				queue.Insert(current->children[i]);
			}
		}
		delete current;
	}
}

