import numpy as np
import sys
import argparse

def parse_args():
  parser = argparse.ArgumentParser(description="Get input filename.")
  parser.add_argument("-i", action="store", dest="input_filename", 
                      default=None, help="Specify input filename.")
  args = parser.parse_args(sys.argv[1:])
  return args

def main():
  args = parse_args()
  input_filename = args.input_filename
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
