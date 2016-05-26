all: pca_main

pca_main: pca_main.o matrix.o
	gcc -o pca_main pca_main.o matrix.o

matrix.o: matrix.c
	gcc -c -Wall matrix.c

matrix.c: matrix.h

pca_main.o: pca_main.c
	gcc -c -Wall pca_main.c



