import numpy as np
import sys


def get_finput():
  if (len(sys.argv) > 1):
    return sys.argv[1]

def main():
  finput = get_finput()
  fin = open(finput, 'r')
  fin.readline()
  l = [ map(float,line.split(' ')) for line in fin ]
  X = np.array(l)
  covariance =  np.cov(X.T)
  U,S,V = np.linalg.svd(covariance)
  print "U = ",U,'\n'
  print "S = ",S,'\n'
  print "V = ",V,'\n'
  fin.close()


if __name__ == '__main__':
  main()
