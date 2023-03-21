import numpy as np
import csv
import random
N = 10


def geom_progression(val):
    arr = []
    left = 1
    for i in range(N):
        arr.append(left)
        left *= val
    return arr

def create_rand_symmetric_matrix_with_defined_eigenvalues(n,val):
    D = np.diag(geom_progression(val))
    Q , R = np.linalg.qr( np.random.random(size=(n, n)))
    A = Q.dot(D).dot(Q.T)
    print(np.diag(D))
    return A


def write_matrix(matrix, name_of_file):
    with open(name_of_file, 'w', newline='') as file:
        writer = csv.writer(file, delimiter=';')
        for row in matrix:
            writer.writerow(row)

a = create_rand_symmetric_matrix_with_defined_eigenvalues(N,1.1)
# print(a)
write_matrix(a, "matrix.txt")