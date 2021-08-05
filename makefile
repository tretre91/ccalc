CXX=cl.exe
CXXFLAGS=/Fe:ccalc /std:c++17 /EHsc /I include
CXXDEBUGFLAGS=$(CXXFLAGS) /Od /Zi
SOURCES=main.cpp driver.cpp calc.tab.cc lexer.yy.cc

FLEX=win_flex
FLEX_FLAGS=--wincompat -o lexer.yy.cc
BISON=win_bison
BISON_FLAGS=-d

lexer.yy.cc : calc.l
	$(FLEX) $(FLEX_FLAGS) calc.l

calc.tab.hh calc.tab.cc location.hh : calc.yy
	$(BISON) $(BISON_FLAGS) calc.yy

ccalc_debug: main.cpp driver.cpp calc.tab.cc lexer.yy.cc
	$(CXX) $(SOURCES) $(CXXDEBUGFLAGS)

ccalc: main.cpp driver.cpp calc.tab.cc lexer.yy.cc
	$(CXX) $(SOURCES) $(CXXFLAGS)

clean:
	del *.obj *.exe *.cc *.hh *.ilk *.pdb
