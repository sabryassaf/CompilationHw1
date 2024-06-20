#ifndef TOKENS_HPP_
#define TOKENS_HPP_
  enum tokentype
  {
    INT = 2,
    BYTE = 3,
    B = 4,
    BOOL = 5,
    AND = 6,
    OR = 7,
    NOT = 8,
    TRUE = 9,
    FALSE = 10,
    RETURN = 11,
    IF = 12,
    ELSE = 13,
    WHILE = 14,
    BREAK = 15,
    CONTINUE = 16, 
    SC = 17,
    LPAREN = 18,
    RPAREN = 19,
    LBRACE = 20,
    RBRACE = 21,
    ASSIGN = 22,
    RELOP = 23,
    BINOP = 24,
    COMMENT = 25,
    ID = 26,
    NUM = 27,
    STRINGEND = 28,
    STRINGERROR = 29,
    ENDOFFILE = 30,
    UNDEFINEDSTRING = 31,
    WRONGCHAR = 32,
    WHITESPACE = 33,
    ILLEGALESCAPE = 34,
    WORD = 35,
    ESCAPE = 36,
    UNCLOSEDSTRING = 37,
    STRINGSTART = 38
  };
  extern int yylineno;
  extern char* yytext;
  extern int yyleng;
  extern int yylex();
#endif /* TOKENS_HPP_ */