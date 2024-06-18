#include "tokens.hpp"
#include <iostream>
#include <stdio.h>

extern int yylex();
extern char* yytext;

char* stripExtraEscapeSequence() {
	// strip the extra escape sequence
	char* newString = new char[yyleng];
	int j = 0;
	for (int i = 0; i < yyleng; i++) {
		if (yytext[i] == '\\') {
			if (yytext[i + 1] == 'n') {
				newString[j] = '\n';
				j++;
				i++;
			} else if (yytext[i + 1] == 't') {
				newString[j] = '\t';
				j++;
				i++;
			} else if (yytext[i + 1] == 'r') {
				newString[j] = '\r';
				j++;
				i++;
			} else if (yytext[i + 1] == '0') {
				newString[j] = '\0';
				j++;
				i++;
			} else if (yytext[i + 1] == '\\') {
				newString[j] = '\\';
				j++;
				i++;
			} else if (yytext[i + 1] == '\"') {
				newString[j] = '\"';
				j++;
				i++;
			} else if (yytext[i + 1] == 'x') {
				// hexa decimal
				char hex[3];
				hex[0] = yytext[i + 2];
				hex[1] = yytext[i + 3];
				hex[2] = '\0';
				newString[j] = (char)strtol(hex, NULL, 16);
				j++;
				i += 3;
			} else {
				newString[j] = yytext[i];
				j++;
			}
		} else {
			newString[j] = yytext[i];
			j++;
		}
	}
	newString[j] = '\0';
	return newString;
}

void checkUndefinedString() {
	// check if the string is undefined
	if (yytext[yyleng - 1] == '\n') {
		printf("Error Unclosed String\n");
		exit(0);
	}
	printf("Error %s\n", yytext);
	exit(0);
}

void handleIllegalEscape() {
	// handle illegal escape sequence
	char* newString = stripExtraEscapeSequence();
	printf("Error undefined escape squence %s\n", newString);
	exit(0);
}

void showToken(int token){
	// check incase of EOF
	if(token == ENDOFFILE) {
		// means a line is ended in middle of a string
		printf("Error Unclosed String\n");
		exit(0);
	}
	if (token == WRONGCHAR) {
		// means a wrong character is found
		printf("Error %s\n", yytext);
		exit(0);
	}
	if (token == UNDEFINEDSTRING) {
		// means a undefined string is found
		checkUndefinedString();
		return;
	}
	if (token == WHITESPACE) {
		return;
	}
	if (token == ILLEGALESCAPE) {
		// means a illegal escape sequence is found
		handleIllegalEscape();
		return;
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