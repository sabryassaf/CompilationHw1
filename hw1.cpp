#include "tokens.hpp"
#include <iostream>
#include <stdio.h>

extern int yylex();
void showToken(int token);

int main()
{
	int token;
	while(token = yylex() && token != 0) {
		showToken(token);
	}
	return 0;
}