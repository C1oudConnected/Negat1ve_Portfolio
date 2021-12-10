#pragma once
#include <iostream>
#include <string_view>
#include <memory>
#include <map>

class CMathExpr;
struct SNodeContent;

typedef std::unique_ptr<CMathExpr> TNodePtr;

struct SNodeContent {
	bool isOperator;
	double value;
};

class CMathExpr {
public:
	static std::map<char, std::pair<unsigned short, double(*)(double, double)> >
																							operators;

	CMathExpr(bool, double, TNodePtr, TNodePtr);
	CMathExpr(bool, double);

	double compute();
	void prefixPrint();
	void postfixPrint();
	void infixPrint();

	SNodeContent cnt;
	TNodePtr pLeft, pRight;
};

TNodePtr strToExprFrom(const std::string_view&, unsigned int);
TNodePtr strToExpr(const std::string_view&, unsigned int&);
