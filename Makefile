all: pca_main

pca_main: pca_main.o matrix.o svd.o
	gcc -o pca_main pca_main.o matrix.o

svd.o: svd.c
	gcc -c -Wall svd.c
	
matrix.o: matrix.c
	gcc -c -Wall matrix.c

matrix.c: matrix.h

pca_main.o: pca_main.c
	gcc -c -Wall pca_main.c

clean:
	rm *.o

