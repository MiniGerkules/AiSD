#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"
#include <stdexcept>
#include <iostream>

// Class that describes the data structure of the QUEUE
template <class T, class V>
class Queue
{
private:
	// Class describing the queue element
	class Queue_item
	{
	public:
		Queue_item* Next;						// Next item in the queue
		Node<T, V>* Value;							// Queue item information field

		/*
			Queue_item class constructor
			Queue_item* next -- pointer to next item
			Node<T, V>* value -- the value of the information field of the queue member
		*/
		Queue_item(Queue_item* next, Node<T, V>* value);
	};

	Queue_item* Begin;							// Beginning of the queue
	Queue_item* End;							// End of the queue

public:

	// Queue class constructor
	Queue();

	// Destructor of the Stack class
	~Queue();

	/*
		A function that adds an item to the queue
		Node<T, V>* value -- the value of the information field of the queue item
	*/
	void push(Node<T, V>* value);

	// A function that returns an element from the beginning of the queue
	Node<T, V>* pop();

	// Function that check the queue for emptiness (if empty -- true, otherwise -- false)
	bool is_empty();
};

#include "Queue.inl"

#endif QUEUE_H
