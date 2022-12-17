./latex-compiled/main.pdf: main.tex
	latexmk -shell-escape -synctex=1 -interaction=nonstopmode -file-line-error -xelatex -outdir='./latex-compiled' main.tex