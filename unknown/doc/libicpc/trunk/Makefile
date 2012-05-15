P=platex -kanji=utf8
D=dvipdfmx
A=notebook

all: $(A).pdf

clean:
	rm -f $(A).pdf $(A).dvi *.aux *.toc *.log

$(A).pdf: $(A).dvi
	$(D) $(A)

$(A).dvi: $(wildcard *.tex)
	$(P) $(A)
	$(P) $(A)
