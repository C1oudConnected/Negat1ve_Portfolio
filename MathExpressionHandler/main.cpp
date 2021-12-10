#include <iostream>
#include <string>
#include "CMathExpr/CMathExpr.hpp"

int main(int argc, char *argv[]){
	TNodePtr exp = strToExprFrom(std::string_view(argv[1]), 0);
	std::cout << "Parsed " << std::endl;
	std::cout << exp->compute() << std::endl;
	exp->infixPrint();
}
