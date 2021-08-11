CXX=cl.exe
CXXFLAGS=/Fe:ccalc /std:c++17 /EHsc /I include /I $(BOOST_ROOT)
CXXDEBUGFLAGS=$(CXXFLAGS) /Od /Zi
SOURCES=main.cpp driver.cpp parser.cc scanner.cc
BOOST_ROOT="C:\Program Files\boost\boost_1_76_0"

FLEX=win_flex
FLEX_FLAGS=--wincompat -o scanner.cc
BISON=win_bison
BISON_FLAGS=

scanner.cc: calc.l
	$(FLEX) $(FLEX_FLAGS) calc.l

parser.hh parser.cc location.hh: calc.yy
	$(BISON) $(BISON_FLAGS) calc.yy

ccalc_debug: $(SOURCES)
	$(CXX) $(SOURCES) $(CXXDEBUGFLAGS)

ccalc: $(SOURCES)
	$(CXX) $(SOURCES) $(CXXFLAGS)

clean:
	del *.obj *.exe *.cc *.hh *.ilk *.pdb
