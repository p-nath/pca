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
To find the pca of a data set use $:make and execute the pca_main executable using the proper flags.
To find the qr decomposition of a matrix use $make qr_test and execute the qr_test executable using the necessary flags


