#pragma once
#include "Node.h"

//Base iterator class
template <class T, class V>
class Iterator
{
public:
	virtual Node<T, V>* next() = 0;
	virtual bool has_next() = 0;
};