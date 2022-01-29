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

	const TNodePtr& getPrev();
	const TNodePtr& getNext();
	const T& getValue();

	void setPrev(CListNode*);
	void setNext(CListNode*);
	void setValue(T);
	void setValueByRef(T&);

private:
	TNodePtr pPrev;
	TNodePtr pNext;
	T value;
}
