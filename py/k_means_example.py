import numpy as np
from sklearn.cluster import KMeans
from sklearn import datasets
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
  iris = datasets.load_iris()
  k_means_iris = KMeans(n_clusters = 3)
  k_means_iris.fit(iris.data)
  #print iris.data
  print k_means_iris.labels_


  input_filename = get_input_filename()
  fin = open(input_filename, 'r')
  #fin.readline()
  l = [ map(float,line.split(' ')) for line in fin ]
  X = np.array(l)
  k_means = KMeans(n_clusters = 3)
  #print X
  k_means.fit(X)
  print k_means.labels_

if __name__ == '__main__':
  main()