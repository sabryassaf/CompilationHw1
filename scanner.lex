%{
#include <stdio.h>
#include <tokens.hpp>
%}

%option yylineno
%option noyywrap
digit   		  ([1-9])
letter  		  ([a-zA-Z])
whitespace	  ([\t\n\r ])

%x STRING

%%
int                                 return INT;
Byte                                return BYTE;
b                                   return B;
bool                                return BOOL;
and                                 return AND;
or                                  return OR;
not                                 return NOT;
true                                return TRUE;
false                               return FALSE;
return                              return RETURN;
if                                  return IF;
else                                return ELSE;
while                               return WHILE;
break                               return BREAK;
continue                            return CONTINUE;
(\;)                                return SC;
(\()                                return LPAREN;
(\))                                return RPAREN;
(\{)                                return LBRACE;
(\})                                return RBRACe;
(=)                                 return ASSIGN;
(==) | (!=) | (<) | (>) | (<=) | (>=) return RELOP;
(+) | (-) | (*) | (/)               return BINOP;
"//" ([^\x0a\x0d])*                 return COMMENT;    
{letter}+(0|{letter}|{digit})*      return ID;
0|({digit}({digit}|0)*)             return NUM;
(\")                                BEGIN(STRING);
<STRING>([^\x5c\x0a\x0d\x22]|()        return STRING;   
