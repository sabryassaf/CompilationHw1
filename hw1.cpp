#include "tokens.hpp"
#include <iostream>
#include <stdio.h>

extern int yylex();

void showToken(int token){
	// check incase of EOF
	if(token == 30) {
		// means a line is ended in middle of a string
		printf("Error Unclosed String\n");
		// exit(0);
	}
	if (token == 32) {
		// means a wrong character is found
		printf("Error %s\n", yytext);
		// exit(0);
	}
	if (token == 31) {
		// means a undefined string is found
		printf("undefined string %s\n", yytext);
		// exit(0);
	}
	

}
int main()
{
	int token;
	while((token = yylex()) && token != 0) {
		showToken(token);
	}
	return 0;
}