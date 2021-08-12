%{
    #include <string>
    #include "common.hpp"
    #include "driver.hpp"
    #include "parser.hh"
    #define YY_USER_ACTION loc.step(); loc.columns(yyleng);
%}

%option noyywrap

id [a-zA-Z][a-zA-Z_0-9]*
special_id _{id}

int [0-9]+
float ({int}?\.{int}+|{int}+\.{int}?)
sci_float ({int}|{float})[eE](\+|-)?{int}

done "quit"|"exit"

%%

%{
    ccalc::location& loc = driver.getLocation();
%}

{done} { driver.endParse(); return ccalc::Parser::make_EOL(loc); }

{id} { return ccalc::Parser::make_ID(yytext, loc); }

{special_id} { return ccalc::Parser::make_SPEC_ID(yytext + 1, loc); }

{int}|{float}|{sci_float} { return ccalc::Parser::make_FLOAT(ccalc::Float(yytext), loc); }

"+" { return ccalc::Parser::make_PLUS(loc); }
"-" { return ccalc::Parser::make_MINUS(loc); }
"*" { return ccalc::Parser::make_MULT(loc); }
"/" { return ccalc::Parser::make_DIV(loc); }
"=" { return ccalc::Parser::make_EQ(loc); }
"(" { return ccalc::Parser::make_OP_PAR(loc); }
")" { return ccalc::Parser::make_CL_PAR(loc); }
"," { return ccalc::Parser::make_COMMA(loc); }
"^"|"**" { return ccalc::Parser::make_POWER(loc); }
"%" { return ccalc::Parser::make_MOD(loc); }

\n { loc.lines(); return ccalc::Parser::make_EOL(loc); }

<<EOF>> { return ccalc::Parser::make_EOL(loc); }

[ \t\r]+ {}

. { return ccalc::Parser::make_LEX_ERROR(std::string("Unknown token \"") + yytext + "\"", loc); }

%%

void ccalc::Driver::parse(std::istream& stream) {
    shouldEnd = false;
    if (!stream || stream.eof()) {
        return;
    }
    ccalc::Parser parser(*this);
    std::string buffer;

    if (driverMode == Mode::eval) {
        std::getline(stream, buffer);
        yy_scan_string(buffer.c_str());
        parser.parse();
        yy_delete_buffer(YY_CURRENT_BUFFER);
    } else {
        const std::string prompt = driverMode == Mode::interactive ? ">> " : "";
        auto getInput = [&buffer,&stream,&prompt]() -> bool { std::cout << prompt; return static_cast<bool>(std::getline(stream, buffer)); };
        while (!shouldEnd && getInput()) {
            yy_scan_string(std::string(buffer + '\n').c_str());
            parser.parse();
            yy_delete_buffer(YY_CURRENT_BUFFER);
        }
    }
}