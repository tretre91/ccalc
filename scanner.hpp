#ifndef SCANNER_HPP
#define SCANNER_HPP

#if !defined(yyFlexLexerOnce)
#    include <FlexLexer.h>
#endif
#include "calc.tab.hh"
#include "location.hh"

namespace ccalc
{
    class Scanner : public yyFlexLexer
    {
    public:
        Scanner(std::istream* in) : yyFlexLexer(in) {
            loc = new ccalc::Parser::location_type();
        }

        virtual int yylex(ccalc::Parser::semantic_type* lval, ccalc::Parser::location_type* location);

        bool good() const {
            return ok;
        }
        void setState(bool state) {
            ok = state;
        }

        ccalc::Parser::location_type getLocation() const {
            return loc != nullptr ? *loc : ccalc::Parser::location_type();
        }

    private:
        ccalc::Parser::semantic_type* yylval = nullptr;
        ccalc::Parser::location_type* loc = nullptr;
        bool ok = true;
    };
} // namespace ccalc

#endif // !SCANNER_HPP
