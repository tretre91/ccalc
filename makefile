_FLAGS=/std:c++17 /EHsc /I $(BOOST_ROOT)
_SOURCES=driver.cpp parser.cc scanner.cc

CXX=cl.exe
CXXFLAGS=/Fe:ccalc $(_FLAGS)
CXXDEBUGFLAGS=$(CXXFLAGS) /Od /Zi
CXXTESTFLAGS=/Fe:ccalctest $(_FLAGS)
SOURCES=main.cpp $(_SOURCES)
TEST_SOURCES=test/main.cpp test/trigonometric_functions.cpp $(_SOURCES)
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

test: $(TEST_SOURCES)
	$(CXX) $(TEST_SOURCES) $(CXXTESTFLAGS)

clean:
	del *.obj *.exe *.cc *.hh *.ilk *.pdb
