#include "tokens.hpp"
#include <iostream>
#include <stdio.h>


const std::string tokenNames[] = {
    "", "", "INT", "BYTE", "B", "BOOL", "AND", "OR", "NOT", "TRUE", "FALSE",
    "RETURN", "IF", "ELSE", "WHILE", "BREAK", "CONTINUE", "SC", "LPAREN",
    "RPAREN", "LBRACE", "RBRACE", "ASSIGN", "RELOP", "BINOP", "COMMENT", "ID",
    "NUM", "STRING", "STRINGERROR", "ENDOFFILE", "UNDEFINEDSTRING", "WRONGCHAR",
    "WHITESPACE", "ILLEGALESCAPE", "WORD", "ESCAPE", "UNCLOSEDSTRING", "STRINGSTART"
};

std::string getTokenName(int token) {
    if (token >= 2 && token < sizeof(tokenNames) / sizeof(std::string)) {
        return tokenNames[token];
    }
    return "Invalid token";
}

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

void handleIllegalEscape() {
	// handle illegal escape sequence
	char* newString = stripExtraEscapeSequence();
	printf("Error undefined escape squence %s\n", newString);
	exit(0);
}

void handleString() {
	// continue reading the string until the end of the string, or reaching an error
	int token;
	// initiate a new string to hold all of the words concatenated
	std::string newString = "";
	while((token = yylex())) {
		std::cout<<"here1"<<std::endl;
		if (token == WORD || token == ESCAPE) {
			// append the word to the new string
			newString += yytext;
			continue;
		}
		if (token == ILLEGALESCAPE) {
			handleIllegalEscape();
		}
		if (token == UNCLOSEDSTRING) {
			std::cout << "Error unclosed string" << std::endl;
			exit(0);
		}
		if (token == STRINGEND) {
			// append the string to the new string
			break;
		}
	}

	// print the new string
	std::cout << yylineno << " STRING " << newString << std::endl;
}

void showToken(int token){
	if (token == WRONGCHAR) {
		std::cout << "Error " << yytext << std::endl;
		exit(0);
	}
	if (token == STRINGSTART) {
		handleString();
		return;
	}
	if (token == WHITESPACE) {
		return;
	}
	else {
		//print the line, token and token value from tokentype
		std::string tokenName = getTokenName(token);
		std::cout << yylineno << " " << tokenName << " " << yytext << std::endl;
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