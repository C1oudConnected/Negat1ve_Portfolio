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
	// Map of operators' characters and corresponding priorities and actions.
	static std::map<char, std::pair<unsigned short, double(*)(double, double)> >
																							operators;

	CMathExpr(bool, double);

	double compute();

	// Different representations;
	std::string prefixPrint	();
	std::string postfixPrint();
	std::string infixPrint	();
	void _prefixPrint		(std::string&);
	void _postfixPrint	(std::string&);
	void _infixPrint		(std::string&);

	SNodeContent cnt;
	TNodePtr pLeft, pRight;
};

//Parsing interface with default start in 0 ...
TNodePtr strToExprFrom(const std::string_view&, unsigned int);
// ... calling a function without default.
TNodePtr strToExpr(const std::string_view&, unsigned int&);
