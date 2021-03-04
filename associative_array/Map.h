#ifndef MAP_H
#define MAP_H

#include "Iterator.h"
#include "Queue.h"
#include <vector>

// Class describing the structure of a red-black tree
template <class T, class V>
class Map
{
private:

	Node<T, V>* Root;						// Red-black tree root node
	Node<T, V>* Nil;						// Fictitious vertex

	// Class describing the breadth-first iterator
	class BFT_iterator : public Iterator<T, V>
	{
	private:

		Queue<T, V>* queue;					// The queue to which we will add items
		Node<T, V>* current;				// Current crawled item
		Node<T, V>* nil;					// Copy of the dummy tree node

	public:
		/*
			BFT_iterator class constructor
			Node<T, V>* start -- binary heap root
			Node<T, V>* nil -- dummy tree node
		*/
		BFT_iterator(Node<T, V>* start, Node<T, V>* nil);

		//Destructor of the BFT_iterator class
		~BFT_iterator();

		// The method will know if there is a next item
		bool has_next() override;

		// Move to next item
		Node<T, V>* next() override;
	};

	/*
		Method finding the grandfather of the current tree node
		Node<T, V>* current -- pointer to the current node
	*/
	Node<T, V>* get_grandpa(Node<T, V>* current);

	/*
		Method finding the uncle of the current tree node
		Node<T, V>* current -- pointer to the current node
	*/
	Node<T, V>* get_uncle(Node<T, V>* current);

	/*
		Left turn method
		Node<T, V>* current -- pointer to the current tree element
	*/
	void left_turn(Node<T, V>* current);

	/*
		Right turn method
		Node<T, V>* current -- pointer to the current tree element
	*/
	void right_turn(Node<T, V>* current);

	/*
		Algorithm for restoring the properties of a red-black tree
		Node<T, V>* current -- pointer to the current node
	*/
	void recovery(Node<T, V>* current);

	/*
		The first possible way to restore the tree
		Node<T, V>* current -- pointer to the current node
	*/
	void first_input_case(Node<T, V>* current);

	/*
		The second possible way to restore the tree
		Node<T, V>* current -- pointer to the current node
	*/
	void second_input_case(Node<T, V>* current);

	/*
		The third possible way to restore the tree
		Node<T, V>* current -- pointer to the current node
	*/
	void third_input_case(Node<T, V>* current);

	/*
		
		Node<T, V>* u -- first node of red-black tree
		Node<T, V>* v -- second node of red-black tree
	*/
	void RB_transplant(Node<T, V>* u, Node<T, V>* v);

	/*
		Method that finds the smallest element in the current subtree
		Node<T, V>* start -- the node from which we start to search
	*/
	Node<T, V>* find_min(Node<T, V>* start);

	/*
		A method that restores the properties of a red-black tree after removing a black node
		Node<T, V>* current -- the node from which we begin to restore tree properties
	*/
	void delete_recovery(Node<T, V>* current);

	/*
		Method recursively deleting tree elements
		Node<T, V>* current -- current tree node
	*/
	void clean(Node<T, V>* current);

public:

	// Map class constructor
	Map();

	// Map class destructor
	~Map();

	// Method that returns the root of the tree
	Node<T, V>* get_root() { return Root; }

	// Creating an iterator that implements breadth-first traversal methods
	Iterator<T, V>* create_bft_iterator();

	/*
		Adding an item with key and value
		int key -- node key
		int value -- node value
	*/
	void insert(T key, V value);

	/*
		Finding a red-black tree element by key
		T key -- the key of the required node
	*/
	Node<T, V>* find(T key);

	// Outputting the tree to the console
	void print();

	// Method that returns a vector of keys
	std::vector<T>* get_keys();

	// Method that returns a vector of values
	std::vector<V>* get_values();

	// Clearing an associative array
	void clear();

	/*
		Method that removes a tree element by key
		T key -- search item key
	*/
	void remove(T key);
};

// We connect the definition
#include "Map.inl"

#endif RB_TREE_H
