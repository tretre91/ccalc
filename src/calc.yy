%skeleton "lalr1.cc"
%require  "3.2"

%defines
%output "parser.cc"
%language "c++"

%define api.namespace {ccalc}
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant

%define parse.assert
%define parse.error simple
%define parse.lac none

%code requires {
    #include <common.hpp>
    
    namespace ccalc {
        class Driver;
    }
}

%code {
    #include <iostream>
    #include <driver.hpp>
}

%param { Driver& driver }

%locations

// types
%token <ccalc::Float> FLOAT
%token <std::string> ID
%token <std::string> SPEC_ID
%token <std::string> LEX_ERROR
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
%token EOL 0

%left MOD
%left PLUS MINUS
%left MULT DIV
%left POWER

%type <ccalc::Float> expr
%type <ccalc::Float> terme
%type <ccalc::Float> facteur
%type <std::vector<ccalc::Float>> arglist

%%

ligne   : expr {
                driver.setLastResult($1);
                if (driver.getMode() != ccalc::Mode::test) {
                    std::cout << $1 << '\n';
                }
            }
        | ID EQ expr { driver.addVariable($1, $3); }
        | SPEC_ID OP_PAR arglist CL_PAR {
                try {
                    driver.callSysFunction($1, $3);
                } catch (const ccalc::UndefinedIdentifier& ui) {
                    error(@1, ui.what());
                } catch (const ccalc::InvalidArgument& ia) {
                    error(@3, ia.what());
                }
            }
        | EOL { YYACCEPT; }
        | error EOL { YYACCEPT; }
        | expr error EOL { YYACCEPT; }
        | ID EQ expr error EOL { YYACCEPT; }
        | SPEC_ID OP_PAR arglist CL_PAR error EOL { YYACCEPT; }
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
        | facteur
        ;

facteur : OP_PAR expr CL_PAR { $$ = $2; }
        | PLUS facteur { $$ = $2; }
        | MINUS facteur { $$ = -$2; }
        | facteur POWER facteur { $$ = mp::pow($1, $3); }
        | facteur MOD facteur { $$ = mp::fmod($1, $3); }
        | FLOAT
        | ID OP_PAR arglist CL_PAR {
                try {
                    $$ = driver.call($1, $3);
                } catch (const ccalc::UndefinedIdentifier& ui) {
                    error(@1, ui.what());
                    YYERROR;
                } catch (const ccalc::InvalidArgument& ia) {
                    error(@3, ia.what());
                    YYERROR;
                }
            }
        | ID { 
                try {
                    $$ = driver.getVariable($1);
                } catch (const ccalc::UndefinedIdentifier& ui) {
                    error(@1, ui.what());
                    YYERROR;
                }
            }
        | LEX_ERROR { error(@1, $1); YYERROR; }
        ;

%%

void ccalc::Parser::error(const location_type& l, const std::string& msg) {
    std::cerr << "Parsing Error (";
    if (l.begin.filename != nullptr)
        std::cerr << l;
    else
        std::cerr << l.begin.column << '-' << l.end.column;
    std::cerr << "): " << msg << '\n';
}
