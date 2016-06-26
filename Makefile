all: pca_main

pca_main: matrix.o svd.o pca_main.o
	gcc -o pca_main pca_main.o svd.o matrix.o
	
matrix.o: matrix.c
	gcc -c -Wall matrix.c

matrix.c: matrix.h

svd.o: svd.c
	gcc -c -Wall svd.c

svd.c: svd.h

pca_main.o: pca_main.c
	gcc -c -Wall pca_main.c

clean:
	rm *.o pca_main

