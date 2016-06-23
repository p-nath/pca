import numpy as np
import sys

fname = str(sys.argv[1])
fin = open(fname, 'r')
fin.readline()
l = [ map(float,line.split(' ')) for line in fin ]
X = np.array(l)
covariance =  np.cov(X.T)
U,S,V = np.linalg.svd(covariance)
print "U=",U,'\n'
print "S=",S,'\n'
print "V=",V,'\n'

#q, r = np.linalg.qr(X)
#print "Q=",q,'\n'
#print "R=",r,'\n'

#np.savetxt('output_py.txt', covariance, fmt = '%.6f')

fin.close()