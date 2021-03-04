#pragma once
#include "Const.h"

// Class describing the red-black tree node
template <class T, class V>
class Node
{
private:

	Node<T, V>* Parent;					// Pointer to parent node
	Node<T, V>* Left;					// Pointer to the left child
	Node<T, V>* Right;					// Pointer to the right child
	T Key;								// Node key
	V Value;							// Node element value
	int Color;							// Node color (red == 0; black == 1)


	/*
		Node class constructor
		Node* parent -- pointer to the parent of the node being created
		Node* left -- pointer to the left child of the node being created
		Node* right -- pointer to the right child of the node being created
		size_t key -- key of the node to be created
		int value -- the value of the node being created
	*/
	Node<T, V>(Node<T, V>* parent, Node<T, V>* left, Node<T, V>* right, T key, V value)
	{
		this->Parent = parent;
		this->Left = left;
		this->Right = right;
		this->Key = key;
		this->Value = value;
		this->Color = Red;
	}

	// Make RB_Tree a friend of Node
	template <class T, class V>
	friend class Map;

public:

	// Method that returns the key of the current item
	T get_key() { return this->Key; }

	// Method that returns the value of the current item
	V get_value() { return this->Value; }
};