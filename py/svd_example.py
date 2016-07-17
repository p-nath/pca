import numpy as np
import sys

def help():
  print sys.argv[0], "-i <input_filename>"
  exit(1)

def get_input_filename():
  if (len(sys.argv) > 1):
    if (sys.argv[1] == "-i") and (2 < len(sys.argv)):
      return sys.argv[2]
  help()

def main():
  input_filename = get_input_filename()
  fin = open(input_filename, 'r')
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
