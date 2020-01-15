

pdflatex --shell-escape boxInterval.tex
pdflatex --shell-escape boxMinMaxPoint.tex
pdflatex --shell-escape hPolytope.tex
pdflatex --shell-escape vPolytope.tex
pdflatex --shell-escape supportFunction.tex
pdflatex --shell-escape zonotope.tex

mv *.png ../pics
rm *.log
rm *.aux
rm *.auxlock
rm *.out
rm *.pdf
rm *.md5
