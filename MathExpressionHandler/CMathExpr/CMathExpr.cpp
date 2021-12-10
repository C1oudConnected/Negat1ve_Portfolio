#include "CMathExpr.hpp"
#include <cstdlib>
#include <ctype.h>

typedef std::pair<char, unsigned short> mapEntry;

std::map<char, unsigned short> CMathExpr::priorities{
	mapEntry{'+', 2},
	mapEntry{'-', 2},
	mapEntry{'*', 1},
	mapEntry{'/', 1}
};

std::map<char, double(*)(double, double)> CMathExpr::operators {
	{'+', [](double a, double b)-> double {return a + b;}},
	{'-', [](double a, double b)-> double {return a - b;}},
	{'*', [](double a, double b)-> double {return a * b;}},
	{'/', [](double a, double b)-> double {return a / b;}}
};

TNodePtr makeEmptyNode();
unsigned short getPriority(const SMathVal&);
bool operator>(TNodePtr&, TNodePtr&);

TNodePtr strToExpr(const std::string_view& str, unsigned int &start) {
	unsigned int& i = start;
	TNodePtr* pHead = nullptr;

	int inv = (str[i] == '-' ? -1 : 1);
	if (str[i] == '-') ++i;

	while (i < str.size() && str[i] != ')' && str[i] != '\n') {


		std::cout << "Processing: " << str[i] << std::endl;


		TNodePtr tmp{};

		if (isdigit(str[i])) {
			char* nextChar = nullptr;
			tmp = std::make_unique<CMathExpr>(SMathVal{
				false, inv * std::strtod(&(str.data()[i]), &nextChar)});
			inv = 1;
			i = nextChar - str.data();
		}
		else if (str[i] == '(')
			tmp = strToExpr(str, ++i);
		else
			tmp = std::make_unique<CMathExpr>(SMathVal{true, str[i++]});


		std::cout << "Here" << std::endl;


		if (!pHead) {
			std::cout << "Head SET: " << str[i-1] << std::endl;
			pHead = &tmp;
		}
		else {
			TNodePtr* pIndex = pHead;
			TNodePtr* pPrev = nullptr;
			while (!((*pIndex)->isEmpty()) && *pIndex > tmp) {
				std::cout << "inside search loop" << std::endl;
				pPrev = pIndex;
				pIndex = &(*pIndex)->pRight;
			}

			if (!(*pIndex)->isEmpty()) {
				(tmp)->pLeft = std::move(*pIndex);
				if (pPrev)
					(*pPrev)->pRight = std::move(tmp);
				else {
					std::cout << "Head OVERWRITE: " << tmp-> val.value << std::endl;
					pHead = &tmp;
				}
			}
		}
	}



			std::cout << "And Here " << (*pHead)->val.value << std::endl;


	return std::move(*pHead);
}

TNodePtr strToExprFrom(const std::string_view& str, unsigned int start = 0){
	return std::move(strToExpr(str, start));
}

TNodePtr makeEmptyNode() {
	return std::make_unique<CMathExpr>(SMathVal{true, END_NODE}, TNodePtr(), TNodePtr());
}

unsigned short getPriority(const SMathVal& val){
	if (val.isOperator)
		if (val.value == -1)
			return -1;
		else
			return CMathExpr::priorities[val.value];
	else return 0;
}

bool operator>(TNodePtr& lhs, TNodePtr& rhs) {
	std::cout << "cmp" << std::endl;
	return getPriority(lhs->val) > getPriority(rhs->val);
		std::cout << "!cmp" << std::endl;
}

CMathExpr::CMathExpr(SMathVal _val)
                    	: val(_val), pLeft(makeEmptyNode()), pRight(makeEmptyNode())
						  	{}

CMathExpr::CMathExpr(SMathVal _val, TNodePtr _l, TNodePtr _r)
							: val(_val), pLeft(std::move(_l)), pRight(std::move(_r))
							{}

bool CMathExpr::isEmpty() {
	return (val.isOperator && val.value == END_NODE);
}

double CMathExpr::compute() {
	if (val.isOperator)
		return operators[val.value](pRight->compute(), pLeft->compute());
}
