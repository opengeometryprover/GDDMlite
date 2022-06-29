# Makefile para os programas dos apontamentos

BASE = gddm
CPP    = g++
BISON = bison
CXX = g++
FLEX = flex
XSLTPROC = xsltproc
BISONFLAGS = -Wcounterexamples

.PHONY : clean all

# $(BASE)
all: $(BASE)

%.cpp %.hpp %.xml %.gv: %.yy
	$(BISON) $(BISONFLAGS) --xml --graph=$*.gv -o $*.cpp $<

%.cpp: %.ll
	$(FLEX) $(FLEXFLAGS) -o $@ $<

%.o: %.cpp
	$(CXX) -g $(CXXFLAGS) -c -o $@ $<


$(BASE): $(BASE).o foftodb.o parser.o scanner.o dbRAM.o prover.o
	$(CXX) -g -o $@ $@.cpp foftodb.o parser.o scanner.o prover.o dbRAM.o -lsqlite3 

$(BASE).o: parser.hpp
parser.o: parser.hpp
scanner.o: parser.hpp

compile: $(BASE)
	@echo "Finished compilation"

run: $(BASE)
	@echo "Type arithmetic expressions.  Quit with ctrl-d."
	./$< -

html: parser.html
%.html: %.xml
	$(XSLTPROC) $(XSLTPROCFLAGS) -o $@ $$($(BISON) --print-datadir)/xslt/xml2xhtml.xsl $<

CLEANFILES =										\
  $(BASE) *.o										\
  parser.hpp parser.cpp parser.output parser.xml parser.html parser.gv location.hpp	\
  scanner.cpp
clean:
	rm -f $(CLEANFILES) $(BASE)
