#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <map>

const double END_NODE = -1;

class CMathExpr;
struct SMathVal;

typedef std::unique_ptr<CMathExpr> TNodePtr;


struct SMathVal {
	bool isOperator;
	double value;
};

class CMathExpr {
public:
	static std::map<char, unsigned short> priorities;
	static std::map<char, double(*)(double, double)> operators;

	CMathExpr(SMathVal, TNodePtr _l, TNodePtr _r);
	CMathExpr(SMathVal);

	bool isEmpty();
	double compute();

	SMathVal val;
	TNodePtr pLeft, pRight;
};

TNodePtr strToExprFrom(const std::string_view&, unsigned int);
TNodePtr strToExpr(const std::string_view&, unsigned int&);
TNodePtr makeEmptyNode();
