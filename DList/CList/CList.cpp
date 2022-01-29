#include"CList.hpp"

const TNodePtr& CListNode::getPrev() {
	return pPrev;
}

const TNodePtr& CListNode::getNext() {
	return pNext;
}

const T& CListNode::getValue() {
	return value;
}

void CListNode::setPrev(CListNode* arg) {
	pPrev = arg;
}

void CListNode::setNext(CListNode* arg) {
	pNext = arg;
}

void CListNode::setValue(T arg) {
	value = arg;
}

void CListNode::setValueByRef(T& arg) {
	value = arg;
}
