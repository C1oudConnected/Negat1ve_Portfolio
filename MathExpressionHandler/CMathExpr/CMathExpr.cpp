#include "CMathExpr.hpp"
#include <cstdlib>
#include <ctype.h>
#include <math.h>

std::map<char, std::pair<unsigned short, double(*)(double, double)> >
 																CMathExpr::operators {
	{'+', {3, [](double a, double b)-> double {return a + b;		}}},
	{'-', {3, [](double a, double b)-> double {return a - b;		}}},
	{'*', {2, [](double a, double b)-> double {return a * b;		}}},
	{'/', {2, [](double a, double b)-> double {return a / b;		}}},
	{'^', {1, [](double a, double b)-> double {return pow(a,b);	}}}
};

TNodePtr makeEmptyNode();
unsigned short getPriority(const TNodePtr&);

TNodePtr strToExpr(const std::string_view& str, unsigned int &start) {
	unsigned int& i = start;
	TNodePtr pHead{};

	int inv = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-') ++i;

	while (i < str.size() && str[i] != ')' && str[i] != '\n') {
		TNodePtr tmp;
		double tmp_prio = 0;

		if (isdigit(str[i])) {
			char* nextChar = nullptr;
			tmp = std::make_unique<CMathExpr>(
				false,
				inv * std::strtod(&(str.data()[i]), &nextChar));
			inv = 1;
			i = nextChar - str.data();
		}
		else if (str[i] == '(') {
			tmp = strToExpr(str, ++i);
		}
		else {
			char ch = str[i++];
			tmp = std::make_unique<CMathExpr>(true, ch);
			tmp_prio = CMathExpr::operators[ch].first;
		}

		if (!pHead) {
			pHead = std::move(tmp);
		}
		else {
			TNodePtr* pIndex = &pHead;
			TNodePtr* pPrev = nullptr;
			while (*pIndex && getPriority(*pIndex) > tmp_prio) {
				pPrev = pIndex;
				pIndex = &(*pIndex)->pRight;
			}

			if (*pIndex) {
				tmp->pLeft = std::move(*pIndex);
			}
			if (pPrev)
				(*pPrev)->pRight = std::move(tmp);
			else {
				pHead = std::move(tmp);
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

unsigned short getPriority(const TNodePtr& arg){
	if (arg->cnt.isOperator) {
		return CMathExpr::operators[arg->cnt.value].first;
	}
	else return 0;
}

CMathExpr::CMathExpr(bool _isOp, double _v, TNodePtr _l, TNodePtr _r)
                    	: cnt{_isOp, _v}, pLeft(std::move(_l)), pRight(std::move(_r))
						  	{}

CMathExpr::CMathExpr(bool _isOp, double _v)
                    	: cnt{_isOp, _v}, pLeft(), pRight()
						  	{}


double CMathExpr::compute() {
	if (cnt.isOperator)
		return operators[cnt.value].second(pRight->compute(), pLeft->compute());
	else
		return cnt.value;
}

void CMathExpr::prefixPrint() {

}

void CMathExpr::postfixPrint() {

}

void CMathExpr::infixPrint() {

}
