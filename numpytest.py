import numpy as np

file = open("input.txt", 'r')
file.readline()
l = [ map(float,line.split(' ')) for line in file ]
X = np.array(l)
#covariance =  np.cov(X.T)
#U,S,V = np.linalg.svd(X.T)

q, r = np.linalg.qr(X.T)
print q;
print r;

np.savetxt('output_py.txt', covariance, fmt = '%.6f')

file.close()