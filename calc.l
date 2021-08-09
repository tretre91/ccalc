%{
    #include <string>
    #include "scanner.hpp"
    #include "common.hpp"
    #undef YY_DECL
    #define YY_DECL int ccalc::Scanner::yylex(ccalc::Parser::semantic_type* lval, ccalc::Parser::location_type* location)
    #define YY_USER_ACTION loc->step(); loc->columns(yyleng);
    using token = ccalc::Parser::token;
%}

%option c++ noyywrap nodefault
%option yyclass="ccalc::Scanner"

id [a-zA-Z][a-zA-Z_0-9]*

number [0-9]+
int (\+|-)?{number}
float (\+|-)?({number}?\.{number}+|{number}+\.{number}?)
sci_float ({int}|{float})[eE]{int}

done "quit"|"exit"

%%

%{
    yylval = lval;
%}

{done} { setState(false); return token::YYEOF; }

{id} { yylval->emplace<std::string>(yytext); return token::ID; }

{int}|{float}|{sci_float} { yylval->emplace<Float>(Float(yytext)); return token::FLOAT; }

"+" { return token::PLUS; }
"-" { return token::MINUS; }
"*" { return token::MULT; }
"/" { return token::DIV; }
"=" { return token::EQ; }
"(" { return token::OP_PAR; }
")" { return token::CL_PAR; }
"," { return token::COMMA; }
"^"|"**" { return token::POWER; }
"%" { return token::MOD; }

\n { loc->lines(); return 0; }

<<EOF>> { setState(false); return token::YYEOF; }

[ \t\r] {}

. {}

%%
