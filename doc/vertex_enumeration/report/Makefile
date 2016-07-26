LATEX = pdflatex -interaction=nonstopmode
BIB = biber

TARGET = rapport.pdf
MAIN_BASENAME = rapport
SOURCES = $(shell find . -name '*.tex') $(shell find . -name '*.eps') $(shell find . -name '*.eps_tex')
MP = $(shell find -L -name "*.mp")
UML = $(shell uml/outputs.sh)

MAIN = $(MAIN_BASENAME).tex

default: $(TARGET)

pdf: $(TARGET)

$(TARGET): $(SOURCES) $(UML) $(IMGPDF) Makefile	
	$(LATEX) $(MAIN)
	$(BIB) $(MAIN_BASENAME)
	$(LATEX) $(MAIN) 
	@while grep 'Rerun to get cross-references right.' $(MAIN_BASENAME).log; \
		do $(LATEX) $(MAIN); done
		
$(UML): $(MP)
	cd uml;\
	$(foreach mpfile,$(MP:./uml/%=%),mpost $(mpfile);)

clean:
	-rm -f *.log *.dvi *.aux *.blg *.bbl *.bcf *.toc *.xml *.out *converted-to.pdf $(PDF_GOAL) $(PDFNUP_GOAL) $(BBL_FILES)
	-rm -f *~ \#*#
	
mrproper: clean
	-rm -f $(TARGET) $(UML) $(MP:%.mp=%.log)
	-rm -f images/*.pdf
	
.SUFFIXES:	# Delete the default suffixes
.PHONY:		pdf clean pdfnup mrproper
