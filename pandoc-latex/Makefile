all: introduction
introduction:
	docker run --rm -v $(shell pwd):/slides bu6hunt3r/pandoc-latex pandoc -f markdown -t beamer -H pre.tex --latex-engine=xelatex -V theme:metropolis -o introduction.pdf introduction2.md

