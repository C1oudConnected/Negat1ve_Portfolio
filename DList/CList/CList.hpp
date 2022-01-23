#pragma once
#include

template<typename T>
using TNodePtr = std::unique_ptr< CNode<T> >;

template<typename T>
class CList {

};

template<typename T>
class CNode {
public:
private:
	T val;
	TNodePtr<T> pLeft;
	TNodePtr<T> pRight;
};

template<typename T>
class CListIterator : std::iterator {
	
}
