#pragma once
#include <memory>

template<typename T>
using TNodePtr = std::unique_ptr< CListNode<T> >;

template<typename T>
class CList {
public:

private:
	
}

template<typename T>
class CListNode {
public:

private:
	TNodePtr pPrev;
	TNodePtr pNext;
	T value;
}
