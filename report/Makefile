FILENAME=sbc-template
COMP=pdflatex

pdf:
	$(COMP) ${FILENAME}
	bibtex  ${FILENAME}||true
	$(COMP) ${FILENAME}
	$(COMP) ${FILENAME}

read:
	xdg-open ${FILENAME}.pdf &

clean:
	rm -f ${FILENAME}.{ps,pdf,log,aux,out,dvi,bbl,blg}
