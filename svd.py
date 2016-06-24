import numpy as np
import sys

def foo():
  if (len(sys.argv) > 1):
    fname = str(sys.argv[1])


if __name__ == '__main__':
  fname = "input.txt"

fin = open(fname, 'r')
fin.readline()
l = [ map(float,line.split(' ')) for line in fin ]
X = np.array(l)
covariance =  np.cov(X.T)
U,S,V = np.linalg.svd(covariance)
print "U = ",U,'\n'
print "S = ",S,'\n'
print "V = ",V,'\n'

fin.close()