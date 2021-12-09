#include <iostream>
#include <string>
#include "CMathExpr/CMathExpr.hpp"

int main(int argc, char *args[]){
	TNodePtr exp = strToExprFrom(std::string_view("1+2*3"), 0);
	std::cout<<exp->compute();
}
