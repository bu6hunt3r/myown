# Creating pdf documents with latex via pandoc and markdown input
## Structure
1. Create a structure in locals fs like the following e.g.:
```
.
├── introduction.md
├── introduction.pdf
├── Makefile
├── pre.tex
├── RAW.md
├── README.md
└── resources
```
## Creation Process

Makefile should include following lines:

```
all: introduction
introduction:
        docker run --rm -v $(shell pwd):/slides bu6hunt3r/pandoc-latex pandoc -f markdown -t beamer -H pre.tex --latex-engine=xelatex -V theme:metropolis -o introduction.pdf introduction.md
```
