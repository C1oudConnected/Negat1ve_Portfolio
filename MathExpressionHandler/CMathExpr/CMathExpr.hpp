#pragma once
#include <string_view>
#include <memory>
#include <map>

const double END_NODE = -1;

class CMathExpr;
typedef std::unique_ptr<CMathExpr> TNodePtr;
auto makeNode = std::make_unique<CMathExpr>;


struct SMathVal {
	bool isOperator;
	double value;
}

class CMathExpr {
public:
	static std::map<char, unsigned short> priorities;

	CMathExpr(SMathVal, TNodePtr _l, TNodePtr _r);
   CMathExpr(SMathVal);

	bool isEmpty();

   SMathVal val;
   TNodePtr pLeft, pRight;
};

TNodePtr strToExpr(std::string_view&, unsigned int);
TNodePtr makeEmptyNode();
double computeExpr(const CMathExpr*);
