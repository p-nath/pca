Principal Component Analysis
-----------------------------
Implementation of PCA using C.

What is it?
-----------
Principal component analysis (PCA) is a statistical procedure that uses an orthogonal transformation to convert a set of observations of possibly correlated variables into a set of values of linearly uncorrelated variables called principal components.
<!--from Wikipedia-->
<!--First the covariance matrix of the dataset is found and then implicit qr algorithm is applied to it till the covariance matrix converges to a diagonal matrix i.e SVD of the dataset is found.-->

How to use?
-----------
To find the pca of a data set use $:make and execute the pca_main executable using the proper flags.
To find the qr decomposition of a matrix use $:make qr_test and execute the qr_test executable using the necessary flags


