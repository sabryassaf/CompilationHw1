#include "tokens.hpp"
#include <iostream>
#include <stdio.h>

extern int yylex();

int main()
{
	int token;
	while((token = yylex()) && token != 0) {
		std::cout << "yytext: " << yytext << std::endl;
		
		if (token == STRING) {
			std::cout << "STRING: " << yytext << std::endl;
		} else if (token == STRINGERROR) {
			std::cout << "STRINGERROR: " << yytext << std::endl;
		} else {
			std::cout << "TOKEN: " << token << std::endl;
		}
	}
	return 0;
}