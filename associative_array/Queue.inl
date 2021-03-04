#include "Queue.h"

// Queue class constructor
template <class T, class V>
Queue<T, V>::Queue()
{
	Begin = nullptr;
	End = nullptr;
}

// Destructor of the Stack class
template <class T, class V>
Queue<T, V>::~Queue()
{
	while (Begin != nullptr)
		pop();

	Begin = nullptr;
	End = nullptr;
}

/*
	Queue_item class constructor
	Queue_item* next -- pointer to next item
	int value -- the value of the information field of the queue item
*/
template <class T, class V>
Queue<T, V>::Queue_item::Queue_item(Queue_item* next, Node<T, V>* value)
	: Next(next), Value(value)
{}

/*
	The function that adds an item to the queue
	int value -- the value of the information field of the queue item
*/
template <class T, class V>
void Queue<T, V>::push(Node<T, V>* value)
{
	if (Begin == nullptr)
	{
		Begin = new Queue_item(nullptr, value);
		if (Begin == nullptr)
			throw std::out_of_range("Memory not allocated.");
		End = Begin;
	}
	else
	{
		End->Next = new Queue_item(nullptr, value);
		if (End->Next == nullptr)
			throw std::out_of_range("Memory not allocated.");
		End = End->Next;
	}
}

// Function that returns the top of the stack
template <class T, class V>
Node<T, V>* Queue<T, V>::pop()
{
	Queue_item* deleted;						// Excluded queue item
	Node<T, V>* value;					// Queue item value

	if (Begin == nullptr)
		throw std::out_of_range("The queue is empty.");

	value = Begin->Value;
	deleted = Begin;
	Begin = Begin->Next;
	delete deleted;

	return value;
}

// Function that check the queue for emptiness (if empty -- true, otherwise -- false)
template <class T, class V>
bool Queue<T, V>::is_empty()
{
	bool answer;								// The program's response about the empty list

	if (Begin == nullptr)
		answer = true;
	else
		answer = false;

	return answer;
}