#Principal Component Analysis
-----------------------------
Implementation of PCA in C.
Tested with Iris Dataset.

What is it?
-----------
Principal component analysis (PCA) is a statistical procedure that
uses orthogonal transformations(implicit QR Decomposition) to convert a set of observations of possibly correlated variables into a set of values of linearly uncorrelated variables called principal components.
PCA is use to decrease the dimensions of a dataset as per requirement. First the covariance matrix of the dataset is found and then Singular Value Decomposition is applied to it (i.e. the covariance matrix undergoes implicit QR decomposition till it converges to a diagonal matrix). With the help of SVD the dimensions of the original dataset is reduced as per the user's requirement.

How to use?
-----------
To find the pca of a dataset -
```
$ make
$ ./pca_main -i <'input_filename'> -o <'output_filename'> -m <'max_iteration'>

```
To find the qr decomposition of a matrix -
```
$ make qr_example 
$ qr_example -i <'input_filename'> -o <'output_filename'>

````

To find k-means of the reduced dataset - 
First make and run pca_main on iput.txt to generate an output file with the dataset with reduced dimensions - 
```
$ make
$ ./pca_main -i input.txt -o output.txt

```
Then run python py/k_means_example.py on the output file -
```
$ pyrhon py/k_means_example.py -i output.txt

```
