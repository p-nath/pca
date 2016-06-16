import numpy as np

file = open("other.txt", 'r')
file.readline()
l = [ map(float,line.split(' ')) for line in file ]
X = np.array(l)
covariance =  np.cov(X.T)
U,S,V = np.linalg.svd(X.T)
print "U=",U,'\n'
print "S=",S,'\n'
print "V=",V,'\n'

q, r = np.linalg.qr(X)
print "Q=",q,'\n'
print "R=",r,'\n'

#np.savetxt('output_py.txt', covariance, fmt = '%.6f')

file.close()