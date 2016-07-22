import numpy as np
from sklearn.cluster import KMeans
from sklearn import decomposition
from sklearn import datasets
import sys
import argparse

def parse_args():
  parser = argparse.ArgumentParser(description="Get input filename.")
  parser.add_argument("-i", action="store", dest="input_filename", 
                      default=None, help="Specify input filename.")
  args = parser.parse_args(sys.argv[1:])
  return args

def get_accuracy(label_array):
  labels = []
  labels.append(label_array[0])

  for i in range(150):
    if label_array[i] in labels:
      continue
    else:
      labels.append(label_array[i])
  #print labels
  mismatches = 0
  x = labels[0]
  for i in range(150):
    if i == 50:
        x = labels[1]
    elif i == 100:
        x = labels[2]

    if x != label_array[i]:
      mismatches += 1
  #print mismatches
  accuracy = float(1 - mismatches / 150.0)
  return accuracy
    

def main():
  args = parse_args()
  input_filename = args.input_filename

  dataset = datasets.load_iris()
  # k_means on the raw iris dataset
  raw_dataset_k_means_model = KMeans(n_clusters=3)
  raw_dataset_k_means_model.fit(dataset.data)
  #print iris.data
  #print raw_dataset_k_means_model.labels_
  print "Accuracy of K-means on raw iris dataset = ", "{0:.2f}".format(get_accuracy(raw_dataset_k_means_model.labels_))

  # k_means on pca(using py library) of iris_dataset
  pca_model = decomposition.PCA(n_components=3)
  reduced_dataset = pca_model.fit_transform(dataset.data)
  reduced_dataset_k_means_model = KMeans(n_clusters=3)
  reduced_dataset_k_means_model.fit(reduced_dataset)

  #print reduced_dataset_k_means_model.labels_
  print "Accuracy of K-means on iris dataset after pca implementation using sklearn library = ", "{0:.2f}".format(get_accuracy(reduced_dataset_k_means_model.labels_))

  # k_means of output from pca program(pca_main.c)
  fin = open(input_filename, 'r')
  l = [ map(float,line.split(' ')) for line in fin ]
  manually_reduced_dataset = np.array(l)
  manually_reduced_dataset_k_means_model = KMeans(n_clusters=3)
  manually_reduced_dataset_k_means_model.fit(manually_reduced_dataset)

  #print manually_reduced_dataset_k_means_model .labels_
  print "Accuracy of K-means on iris dataset after pca implementation using pca_main.c =", "{0:.2f}".format(get_accuracy(manually_reduced_dataset_k_means_model .labels_))

if __name__ == '__main__':
  main()
