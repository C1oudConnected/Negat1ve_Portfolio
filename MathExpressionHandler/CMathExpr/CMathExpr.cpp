#include "CMathExpr.hpp"
#include <cstdlib>
#include <ctype.h>
#include <math.h>

// Add new operators here.
std::map<char, std::pair<unsigned short, double(*)(double, double)> >
 																CMathExpr::operators {
	{'+', {3, [](double a, double b)-> double {return a + b;		}}},
	{'-', {3, [](double a, double b)-> double {return a - b;		}}},
	{'*', {2, [](double a, double b)-> double {return a * b;		}}},
	{'/', {2, [](double a, double b)-> double {return a / b;		}}},
	{'^', {1, [](double a, double b)-> double {return pow(a,b);	}}}
};
unsigned short getPriority(const CMathExpr*);

TNodePtr strToExpr(const std::string_view& str, unsigned int &start) {
	//Pointer to handle the brackets.
	const TNodePtr* pNested_expr = nullptr;

	unsigned int& i = start;
	TNodePtr pHead{};

	//To handle unary minus operator.
	int inv = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-') ++i;

	// Looping through characters, nested_expressions continue the loop internally.
	while (i < str.size() && str[i] != ')' && str[i] != '\n') {
		TNodePtr tmp;
		double tmp_prio = 0;
  	bool isNested = false;

		// Setting object being proccessed.
		// If the character starts a number...
		if (isdigit(str[i])) {
			char* nextChar = nullptr;
			tmp = std::make_unique<CMathExpr>(
				false,
				inv * std::strtod(&(str.data()[i]), &nextChar));
			inv = 1;
			i = nextChar - str.data();
		}
		// ... or an expression in brackets ...
		else if (str[i] == '(') {
			tmp = strToExpr(str, ++i);
    	isNested = true;
		}
		// ... or an operator.
		else {
			char ch = str[i++];
			tmp = std::make_unique<CMathExpr>(true, ch);
			tmp_prio = CMathExpr::operators[ch].first;
		}

		// Searching for object's position in tree.
		// Nested Expression ptr. is important to ignore priority check.
		TNodePtr* pIndex = &pHead;
		TNodePtr* pPrev = nullptr;
		while (*pIndex && pIndex != pNested_expr
						&& getPriority((*pIndex).get()) > tmp_prio)
		{
    	pPrev = pIndex;
			pIndex = &(*pIndex)->pRight;
		}

		// Nullifying nested expression pointer, don't need it after search.
		pNested_expr = nullptr;

		// If object has to replace some entry, entry becomes it's left child.
		if (*pIndex)
			tmp->pLeft = std::move(*pIndex);

		// If object's gonna have a parent, object settles as it's right child.
		if (pPrev) {
			(*pPrev)->pRight = std::move(tmp);
    		if (isNested) {
      		pNested_expr = &(*pPrev)->pRight;
    		}
		}
		// Else it just becoming the HEAD of the tree.
		else {
			pHead = std::move(tmp);
    		if (isNested) {
      		pNested_expr = &pHead;
    		}
		}
	}

	if (str[i] == ')')
		++i;

	return std::move(pHead);
}

TNodePtr strToExprFrom(const std::string_view& str, unsigned int start = 0){
	return std::move(strToExpr(str, start));
}

unsigned short getPriority(const CMathExpr* arg){
	if (arg->cnt.isOperator) {
		return CMathExpr::operators[arg->cnt.value].first;
	}
	else return 0;
}

CMathExpr::CMathExpr(bool _isOp, double _v)
                    	: cnt{_isOp, _v}, pLeft(), pRight()
						  	{}


double CMathExpr::compute() {
	if (cnt.isOperator)
		return operators[cnt.value].second(pLeft->compute(), pRight->compute());
	else
		return cnt.value;
}

std::string CMathExpr::prefixPrint() {
	std::string str{};
	_prefixPrint(str);
	return str;
}

std::string CMathExpr::postfixPrint() {
	std::string str{};
	_postfixPrint(str);
	return str;
}

std::string CMathExpr::infixPrint() {
	std::string str{};
	_infixPrint(str);
	return str;
}

void CMathExpr::_prefixPrint(std::string& str) {
	str += std::to_string(cnt.value) + " ";
	if (cnt.isOperator) {
		pLeft->_prefixPrint(str);
		pRight->_prefixPrint(str);
	}
}

void CMathExpr::_postfixPrint(std::string& str) {
	if (cnt.isOperator) {
		pLeft->_prefixPrint(str);
		pRight->_prefixPrint(str);
	}
	str += std::to_string(cnt.value) + " ";
}

void CMathExpr::_infixPrint(std::string& str) {

	if (cnt.isOperator) {
		if (getPriority(this) < getPriority(pLeft.get())) {
			str += "( ";
			pLeft->_infixPrint(str);
			str += ") ";
		}
		else
			pLeft->_infixPrint(str);

		str += std::to_string((char)cnt.value) + " ";

		if (getPriority(this) < getPriority(pRight.get())) {
			str += "( ";
			pRight->_infixPrint(str);
			str += ") ";
		}
		else
			pRight->_infixPrint(str);
	}
	else
		str += std::to_string(cnt.value) + " ";
}
