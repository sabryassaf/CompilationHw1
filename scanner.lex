%{
#include <stdio.h>
#include "tokens.hpp"
%}

%option yylineno
%option noyywrap
digit   		  ([1-9])
letter  		  ([a-zA-Z])
whitespace	      ([\t\n\r ])
escape            (\\)(x([0-7][0-9A-Fa-f])|n|r|t|0|\"|\\)
word              ([!#-\[\]-~])


%x STRING

%%
int                                 return INT;
byte                                return BYTE;
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
(\})                                return RBRACE;
(=)                                 return ASSIGN;
==|!=|<|>|<=|>= return RELOP;
(\+|\-|\*|\/)           return BINOP;
\/\/.*                              return COMMENT;    
{letter}+(0|{letter}|{digit})*      return ID;
0|({digit}({digit}|0)*)             return NUM;

(\")                                BEGIN(STRING); return STRINGSTART;
<STRING>{word}*                     return WORD;
<STRING>{escape}                    return ESCAPE;
<STRING>\\x[8-9A-Fa-f][0-9A-Za-z]   return ILLEGALESCAPE;
<STRING>\\x[^0-9A-Fa-f]+            return ILLEGALESCAPE;
<STRING>\\x[0-7][^0-9A-Fa-f]        return ILLEGALESCAPE;
<STRING>\\x.{0,1}                    return ILLEGALESCAPE;
<STRING>(\\)[^"\\nrt0x]             return ILLEGALESCAPE;
<STRING><<EOF>>                     return ENDOFFILE;
<STRING>[\n\r]                      return UNCLOSEDSTRING;
<STRING>({whitespace})              return WHITESPACE;
<STRING>(\")                        BEGIN(INITIAL); return STRINGEND;
({whitespace})+                     return WHITESPACE;
.                                   return WRONGCHAR;
%%
 