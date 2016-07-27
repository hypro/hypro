LATEX=pdflatex -halt-on-error -interaction=nonstopmode

TARGET=beamer

all: $(TARGET)

$(TARGET): $(TARGET).tex
	$(LATEX) $(TARGET)

camera-ready: $(TARGET)
	cp $(TARGET).pdf dechir-hrs.pdf

clean:
	rm -f *.out *.snm *.toc *.aux *.log *.nav **/*-eps-converted-to.pdf *-eps-converted-to.pdf

mrproper: clean
	rm -r $(TARGET).pdf

.PHONY: clean mrproper
