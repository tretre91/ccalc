%skeleton "lalr1.cc"
%require  "3.2"

%defines
%define api.namespace {ccalc}
%define api.parser.class {Parser}

%code requires {
    namespace ccalc {
        class Driver;
        class Scanner;
    }
}

%parse-param { Scanner  &scanner  }
%parse-param { Driver  &driver  }

%code {
    #include <iostream>
    //#include <cstdlib>
    #include <cmath>
    #include "driver.hpp"
    #undef yylex
    #define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

// types
%token <int> INT
%token <float> FLOAT
%token <std::string> ID
// basic operations
%token PLUS
%token MINUS
%token MULT
%token DIV
%token POWER
%token MOD
// other tokens
%token EQ
%token OP_PAR
%token CL_PAR
%token COMMA


%locations

%type <float> expr
%type <float> terme
%type <float> facteur
%type <std::vector<float>> arglist

%%

ligne   : expr { if (!driver.getErrorFlag()) std::cout << $1 << '\n'; }
        | ID EQ expr { driver.addVariable($1, $3); }
        | YYEOF { YYACCEPT; }
        ;

arglist : arglist COMMA expr { $$ = $1; $$.push_back($3); }
        | expr { $$.push_back($1); }
        ;

expr    : expr PLUS terme { $$ = $1 + $3; }
        | expr MINUS terme { $$ = $1 - $3; }
        | terme
        ;

terme   : terme MULT facteur { $$ = $1 * $3; }
        | terme DIV facteur { $$ = $1 / $3; }
        | terme POWER facteur { $$ = std::powf($1, $3); }
        | terme MOD facteur { $$ = std::fmodf($1, $3); }
        | facteur
        | PLUS facteur { $$ = $2; }
        | MINUS facteur { $$ = -$2; }
        ;

facteur : OP_PAR expr CL_PAR { $$ = $2; }
        | INT { $$ = static_cast<float>($1); }
        | FLOAT
        | ID OP_PAR arglist CL_PAR {
                try {
                    $$ = driver.call($1, $3);
                } catch (const std::invalid_argument& ia) {
                    error(scanner.getLocation(), "Function \"" + $1 + "\" takes " + ia.what());
                    driver.setErrorFlag(true);
                    $$ = 0.0f;
                } catch (const ccalc::unknown_identifier& ui) {
                    error(scanner.getLocation(), ui.what());
                    driver.setErrorFlag(true);
                    $$ = 0.0f;
                }
            }
        | ID { 
                try {
                    $$ = driver.getVariable($1);
                } catch (const ccalc::unknown_identifier& ui) {
                    error(scanner.getLocation(), ui.what());
                    driver.setErrorFlag(true);
                    $$ = 0.0f;
                }
             }
        ;

%%

void ccalc::Parser::error(const location_type& l, const std::string& msg) {
    std::cerr << "Parsing Error: " << l << ": " << msg << '\n';
}
