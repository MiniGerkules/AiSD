#include "Map.h"
#include <stdexcept>

using namespace std;

//--------------------------------------
// Private methods
//--------------------------------------

/*
	BFT_iterator class constructor
	Node<T, V>* start -- RB-Tree root
	Node<T, V>* nil -- dummy tree node
}*/
template<class T, class V>
Map<T, V>::BFT_iterator::BFT_iterator(Node<T, V>* start, Node<T, V>* nil)
{
	this->queue = new Queue<T, V>();
	if (this->queue == nullptr)
		throw out_of_range("Memory allocation error for queue!");

	this->current = start;
	queue->push(start);
	this->nil = nil;
}

//Destructor of the BFT_iterator class
template <class T, class V>
Map<T, V>::BFT_iterator::~BFT_iterator()
{
	current = nullptr;
	delete queue;
}

// The method will know if there is a next item
template <class T, class V>
bool Map<T, V>::BFT_iterator::has_next()
{
	if (!queue->is_empty())
		return true;
	else
		return false;
}

// Move to next item
template <class T, class V>
Node<T, V>* Map<T, V>::BFT_iterator::next()
{
	if (has_next())
	{
		current = queue->pop();
		if (current->Left != nil)
			queue->push(current->Left);
		if (current->Right != nil)
			queue->push(current->Right);

		return current;
	}
	else
		throw out_of_range("No more items available!");
}

/*
	Method finding the grandfather of the current tree node
	Node<T, V>* current -- pointer to the current node
*/
template <class T, class V>
Node<T, V>* Map<T, V>::get_grandpa(Node<T, V>* current)
{
	if (current->Parent != Nil)
		return current->Parent->Parent;
	else
		return Nil;
}

/*
	Method finding the uncle of the current tree node
	Node<T, V>* current -- pointer to the current node
*/
template <class T, class V>
Node<T, V>* Map<T, V>::get_uncle(Node<T, V>* current)
{
	Node<T, V>* grandpa = get_grandpa(current);

	if (grandpa != Nil)
	{
		if (current->Parent == grandpa->Left)
			return grandpa->Right;
		else
			return grandpa->Left;
	}
	else 
		return nullptr;
}

/*
	Left turn method
	Node<T, V>* current -- pointer to the current tree element
*/
template <class T, class V>
void Map<T, V>::left_turn(Node<T, V>* current)
{
	Node<T, V>* child;						// The variable into which we store the value of the son

	child = current->Right;
	current->Right = child->Left;
	
	if (child->Left != Nil)
		child->Left->Parent = current;

	child->Parent = current->Parent;

	if (current->Parent == Nil)
		Root = child;
	else if (current == current->Parent->Left)
		current->Parent->Left = child;
	else
		current->Parent->Right = child;

	child->Left = current;
	current->Parent = child;
}

/*
	Right turn method
	Node<T, V>* current -- pointer to the current tree element
*/
template <class T, class V>
void Map<T, V>::right_turn(Node<T, V>* current)
{
	Node<T, V>* child;						// The variable into which we store the value of the son

	child = current->Left;
	current->Left = child->Right;

	if (child->Right != Nil)
		child->Right->Parent = current;

	child->Parent = current->Parent;

	if (current->Parent == Nil)
		Root = child;
	else if (current == current->Parent->Right)
		current->Parent->Right = child;
	else
		current->Parent->Left = child;

	child->Right = current;
	current->Parent = child;
}

/*
	Algorithm for restoring the properties of a red-black tree
	Node<T, V>* current -- pointer to the current node
*/
template <class T, class V>
void Map<T, V>::recovery(Node<T, V>* current)
{
	if (current->Parent == Nil)
		// We repaint the root so that its color is always black
		Root->Color = Black;
	else if (current->Parent->Color != Black)
		// If the ancestor is not black, then the tree is wrong
		first_input_case(current);
}

/*
	The first possible way to restore the tree
	Node<T, V>* current -- pointer to the current node
*/
template <class T, class V>
void Map<T, V>::first_input_case(Node<T, V>* current)
{
	Node<T, V>* uncle = get_uncle(current);

	if (uncle->Color == Red)
	{
		// If parent and uncle are red, recolor them and grandpa
		uncle->Color = Black;
		current->Parent->Color = Black;
		uncle->Parent->Color = Red;

		// Now grandfather can break the rules of tree
		recovery(uncle->Parent);
	}
	else
		second_input_case(current);
}

/*
	The second possible way to restore the tree
	Node<T, V>* current -- pointer to the current node
*/
template <class T, class V>
void Map<T, V>::second_input_case(Node<T, V>* current)
{
	Node<T, V>* grandpa = get_grandpa(current);

	if ((current == current->Parent->Right) && (current->Parent == grandpa->Left))
	{
		current = current->Parent;
		left_turn(current);
	}
	else if ((current == current->Parent->Left) && (current->Parent == grandpa->Right))
	{
		current = current->Parent;
		right_turn(current);
	}

	// We still have father and son the same color, let's fix it
	third_input_case(current);
}

/*
	The third possible way to restore the tree
	Node<T, V>* current -- pointer to the current node
*/
template <class T, class V>
void Map<T, V>::third_input_case(Node<T, V>* current)
{
	if (current == current->Parent->Left)
	{
		// We recolor the vertices and make a turn relative to the father
		current->Parent->Color = Black;
		current->Parent->Parent->Color = Red;
		right_turn(current->Parent->Parent);
	}
	else
	{
		// We recolor the vertices and make a turn relative to the father
		current->Parent->Color = Black;
		current->Parent->Parent->Color = Red;
		left_turn(current->Parent->Parent);
	}
}

/*
	Method replacing the deleted node with its descendant
	Node<T, V>* u -- first node of red-black tree
	Node<T, V>* v -- second node of red-black tree
*/
template <class T, class V>
void Map<T, V>::RB_transplant(Node<T, V>* u, Node<T, V>* v)
{
	if (u->Parent == Nil)
		Root = v;
	else if (u == u->Parent->Left)
		u->Parent->Left = v;
	else
		u->Parent->Right = v;

	v->Parent = u->Parent;
}

/*
	Method that finds the smallest element in the current subtree
	Node<T, V>* start -- the node from which we start to search
*/
template <class T, class V>
Node<T, V>* Map<T, V>::find_min(Node<T, V>* start)
{
	Node<T, V>* answer = start;						// Element with minimum key

	if (answer != Nil)
	{
		while (answer->Left != Nil)
			answer = answer->Left;
	}
	else
		throw domain_error("The node passed was a leaf!");

	return answer;
}

/*
	A method that restores the properties of a red-black tree after removing a black node
	Node<T, V>* current -- the node from which we begin to restore tree properties
*/
template <class T, class V>
void Map<T, V>::delete_recovery(Node<T, V>* current)
{
	Node<T, V>* sec_child;						// Second child of the current node

	while ((current != Root) && (current->Color == Black))
	{
		if (current == current->Parent->Left)
		{
			sec_child = current->Parent->Right;

			if (sec_child->Color == Red)
			{
				sec_child->Color = Black;
				current->Parent->Color = Red;
				left_turn(current->Parent);
				sec_child = current->Parent->Right;
			}
			else if ((sec_child->Left->Color == Black) && (sec_child->Right->Color == Black))
			{
				sec_child->Color = Red;
				current = current->Parent;
			}
			else if (sec_child->Right->Color == Black)
			{
				sec_child->Left->Color = Black;
				sec_child->Color = Red;
				right_turn(sec_child);
				sec_child = current->Parent->Right;
			}
			else
			{
				sec_child->Color = current->Parent->Color;
				current->Parent->Color = Black;
				sec_child->Right->Color = Black;
				left_turn(current->Parent);
				current = Root;
			}
		}
		else
		{
			sec_child = current->Parent->Left;

			if (sec_child->Color == Red)
			{
				sec_child->Color = Black;
				current->Parent->Color = Red;
				left_turn(current->Parent);
				sec_child = current->Parent->Left;
			}
			else if ((sec_child->Left->Color == Black) && (sec_child->Right->Color == Black))
			{
				sec_child->Color = Red;
				current = current->Parent;
			}
			else if (sec_child->Left->Color == Black)
			{
				sec_child->Right->Color = Black;
				sec_child->Color = Red;
				left_turn(sec_child);
				sec_child = current->Parent->Left;
			}
			else
			{
				sec_child->Color = current->Parent->Color;
				current->Parent->Color = Black;
				sec_child->Left->Color = Black;
				right_turn(current->Parent);
				current = Root;
			}
		}
	}

	current->Color = Black;
}

/*
	Method recursively deleting tree elements
	Node<T, V>* current -- current tree node
*/
template <class T, class V>
void Map<T, V>::clean(Node<T, V>* current)
{
	if (current->Left != Nil)
		clean(current->Left);
	if (current->Right != Nil)
		clean(current->Right);

	delete current;
}

//--------------------------------------
// Public methods
//--------------------------------------

// Map class constructor
template <class T, class V>
Map<T, V>::Map()
{
	Root = nullptr;

	Nil = new Node<T, V>(nullptr, nullptr, nullptr, T(), V());
	if (Nil == nullptr)
		throw domain_error("Error allocating memory for a fictitious node!");

	Nil->Color = Black;
	Root = Nil;
}

// Map class destructor
template <class T, class V>
Map<T, V>::~Map()
{
	clear();
	
	delete Nil;
}

// Creating an iterator that implements breadth-first traversal methods
template <class T, class V>
Iterator<T, V>* Map<T, V>::create_bft_iterator()
{
	BFT_iterator* iterator;

	if (Root == Nil)
		throw out_of_range("There are no elements in the RB-tree!");

	iterator = new BFT_iterator(Root, Nil);
	if (iterator == nullptr)
		throw out_of_range("Memory allocation error for iterator!");

	return iterator;
}

/*
	Adding an item with key and value
	int key -- node key
	int value -- node value
*/
template <class T, class V>
void Map<T, V>::insert(T key, V value)
{
	if (Root == Nil)
	{
		Root = new Node<T, V>(Nil, Nil, Nil, key, value);
		if (Root == nullptr)
			throw out_of_range("Memory allocation error for root node!");

		Root->Color = Black;
	}
	else
	{
		Node<T, V>* current;					// Pointer to the current element
		Node<T, V>* added;						// The node that we will insert
		bool can_move;							// Flag showing whether we have reached the leaf of the tree

		current = Root;
		can_move = true;

		do
		{
			// If you need to move to the right and you can, go to the right child
			if ((key >= current->Key) && (current->Right != Nil))
				current = current->Right;
			// If you need to move to the left and you can, go to the left child
			else if ((key < current->Key) && (current->Left != Nil))
				current = current->Left;
			// Otherwise we stop
			else
				can_move = false;
		} while (can_move);

		added = new Node<T, V>(current, Nil, Nil, key, value);
		if (added == nullptr)
			throw out_of_range("Error while allocating memory for a tree element!");

		// Add a node according to the rules of the binary search tree
		if (key > current->Key)
			current->Right = added;
		else
			current->Left = added;

		//Restoring the properties of red-black wood
		recovery(added);
	}
}

/*
	Finding a red-black tree element by key
	T key -- the key of the required node
*/
template <class T, class V>
Node<T, V>* Map<T, V>::find(T key)
{
	Node<T, V>* current = Root;

	while ((current->Key != key) && (current != Nil))
	{
		if (key > current->Key)
			current = current->Right;
		else
			current = current->Left;
	}

	if (current == Nil)
		throw domain_error("The item with the passed key does not exist!");

	return current;
}


// Outputting the tree to the console
template <class T, class V>
void Map<T, V>::print()
{
	Iterator<T, V>* iterator;					// Breadth First Iterator
	Node<T, V>* current;						// Current tree node

	iterator = create_bft_iterator();
	if (iterator == nullptr)
		throw out_of_range("Error allocating memory for an iterator!");

	cout << "Key values = " << T() << " indicates that the child does not exist." << endl;
	while (iterator->has_next())
	{
		current = iterator->next();
		cout << "Key -- " << current->Key << ", value -- " << current->Value << ", color -- " << 
				(current->Color == 1 ? "BLACK" : "RED") << ", left child key -- " << current->Left->Key << 
				", right child key -- " << current->Right->Key << endl;
	}

	delete iterator;
}

// Method that returns a vector of keys
template <class T, class V>
std::vector<T>* Map<T, V>::get_keys()
{
	Iterator<T, V>* iterator;					// Breadth First Iterator
	std::vector<T>* keys = new vector<T>();		// The vector of keys

	iterator = create_bft_iterator();
	if (iterator == nullptr)
		throw out_of_range("Error allocating memory for an iterator!");

	while (iterator->has_next())
		keys->push_back(iterator->next()->Key);

	delete iterator;
	return keys;
}

// Method that returns a vector of values
template <class T, class V>
std::vector<V>* Map<T, V>::get_values()
{
	Iterator<T, V>* iterator;					// Breadth First Iterator
	std::vector<V>* values = new vector<V>();	// The vector of values

	iterator = create_bft_iterator();
	if (iterator == nullptr)
		throw out_of_range("Error allocating memory for an iterator!");

	while (iterator->has_next())
		values->push_back(iterator->next()->Value);

	delete iterator;
	return values;
}

// Clearing an associative array
template <class T, class V>
void Map<T, V>::clear()
{
	if (Root != Nil)
	{
		clean(Root);
		Root = Nil;
	}
}

/*
	Method that removes a tree element by key
	T key -- search item key
*/
template <class T, class V>
void Map<T, V>::remove(T key)
{
	Node<T, V>* deleted = find(key);			// The element to be removed
	Node<T, V>* x;								// The node with which we will restore the tree properties
	int original_color = deleted->Color;		// The color of the item to remove

	if (deleted->Left == Nil)
	{
		x = deleted->Right;
		RB_transplant(deleted, deleted->Right);
	}
	else if (deleted->Left == Nil)
	{
		x = deleted->Left;
		RB_transplant(deleted, deleted->Left);
	}
	else
	{
		Node<T, V>* change;						// The node with which we will replace the deleted
		
		change = find_min(deleted->Right);
		original_color = change->Color;
		
		x = change->Right;
		if (change->Parent == deleted)
			x->Parent = change;
		else
		{
			RB_transplant(change, change->Right);
			change->Right = deleted->Right;
			change->Right->Parent = change;
		}

		RB_transplant(deleted, change);
		change->Left = deleted->Left;
		change->Left->Parent = change;
		change->Color = deleted->Color;
	}

	delete deleted;

	if (original_color == Black)
		delete_recovery(x);
}
