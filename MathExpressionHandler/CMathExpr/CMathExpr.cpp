#include "CMathExpr.hpp"
#include <cctype>

typedef std::pair<char, unsigned short> mapEntry;

CMathExpr::priorities{
	mapEntry{'+', 2},
	mapEntry{'-', 2},
	mapEntry{'*', 1},
	mapEntry{'/', 1},
};

TNodePtr makeEmptyNode();
unsigned short getPriority(const SMathVal&);
bool operator>(TNodePtr, TNodePtr);

TNodePtr CMathExpr::strToExpr(std::string_view& str, unsigned int &start) {
	unsigned int i = start;
	TNodePtr* pHead = nullptr;

	int inv = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-') ++i;

	while (i < str.size() && str[i] != ')') {
		TNodePtr* tmp = nullptr;

		if (isdigit(str[i])) {
			tmp = &makeNode(SMathVal(false, inv * strtod(str.data()[i])));
			inv = 1;
		}
		else if (str[i] == '(')
			tmp = &strToExpr(str, ++i);
		else
			tmp = &makeNode(SMathVal(true, str[i]));

		if (!pHead)
			pHead = tmp;
		else {
			TNodePtr* pIndex = pHead;
			TNodePtr* pPrev = nullptr;
			while (!(*pIndex->isEmpty()) && *pIndex > *tmp) {
				pPrev = pIndex;
				pIndex = &(*pIndex)->pRight;
			}

			if (!pI->isEmpty()) {
				(*tmp)->pLeft = *pI;
				if (pPrev)
					(*pPrev)->pRight = pPrev;
			}
			*pI = *tmp;
		}
	}
}

TNodePtr makeEmptyNode(){
	return make_unique<CMathExpr>(SMathVal(true, END_NODE), TNodePtr(), TNodePtr());
}

unsigned short getPriority(const SMathVal& val){
	if (val.isOperator)
		return priorities[val.value];
	else return 0;
}

bool operator>(TNodePtr lhs, TNodePtr rhs) {
	return getPriority(lhs->val) > getPriority(rhs->val);
}

CMathExpr::CMathExpr(SMathVal _val)
                    	: val(_val), pLeft(makeEmptyNode()), pRight(makeEmptyNode())
						  	{}

CMathExpr::CMathExpr(SMathVal _val, TNodePtr _l, TNodePtr _r)
							: val(_val), pLeft(_l), pRight(_r)
							{}

bool CMathExpr::isEmpty() {
	return (val.isOperator && val.value == END_NODE);
}
