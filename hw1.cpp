#include "tokens.hpp"
#include <iostream>
#include <stdio.h>

extern int yylex();
void showToken(int token);

int main()
{
	int token;
	while(token = yylex()) {
		showToken(token);
	}
	return 0;
}