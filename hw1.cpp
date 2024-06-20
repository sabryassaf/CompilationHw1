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

std::string stripExtraEscapeSequence(const std::string& stringToStrip) {
    std::string newString;
    for (size_t i = 0; i < stringToStrip.size(); ++i) {
        if (stringToStrip[i] == '\\' && i + 1 < stringToStrip.size()) {
            switch (stringToStrip[i + 1]) {
                case 'n':
                    newString += '\n';
                    ++i;  // Skip the next character
                    break;
                case 't':
                    newString += '\t';
                    ++i;  // Skip the next character
                    break;
                case '0':
                    newString += '\0';
                    ++i;  // Skip the next character
                    break;
                case 'r':
                    newString += '\r';
                    ++i;  // Skip the next character
                    break;
                case '\"':
                    newString += '\"';
                    ++i;  // Skip the next character
                    break;
                case 'x':
                    if (i + 3 < stringToStrip.size()) {
                        char hex[3];
                        hex[0] = stringToStrip[i + 2];
                        hex[1] = stringToStrip[i + 3];
                        hex[2] = '\0';
                        newString += (char)strtol(hex, NULL, 16);
                        i += 3;  // Skip the next three characters
                    }
                    break;
                case '\\':
                    newString += '\\';
                    ++i;  // Skip the next character
                    break;
                default:
                    newString += stringToStrip[i];
                    break;
            }
        } else {
            newString += stringToStrip[i];
        }
    }
    return newString;
}
std::string stripExtraIllegalEscapeSequence(const std::string& stringToStrip) {
    //remove the first letter from strintToStrip
    std::cout<<stringToStrip<<std::endl;
    std::string newString = stringToStrip.substr(1);
    if (newString[newString.size()-1] == '\"') {
        newString = newString.substr(0, newString.size()-1);
    }
    return newString;

}

void handleIllegalEscape() {
	// handle illegal escape sequence
    std::string newString = stripExtraIllegalEscapeSequence(yytext);
    // if (newString[yyleng-2] == '\"') {
    //     newString = newString.substr(0, yyleng-2);
    // }
	std::cout << "Error undefined escape sequence " << newString << std::endl;
	exit(0);
}

void handleString() {
	// continue reading the string until the end of the string, or reaching an error
	int token;
	// initiate a new string to hold all of the words concatenated
	std::string newString = "";
	while((token = yylex())) {
		if (token == WORD || token == ESCAPE || token == WHITESPACE) {
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
	std::string strippedString = stripExtraEscapeSequence(newString);
	std::cout << yylineno << " STRING " << strippedString << std::endl;
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
    if (token == COMMENT) {
        std::string tokenName = getTokenName(token);
		std::cout << yylineno << " " << tokenName << " //" << std::endl;
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