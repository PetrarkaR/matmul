import numpy as np

matrixA= np.loadtxt("matrixA.txt",dtype="i")
matrixB= np.loadtxt("matrixB.txt",dtype="i")

matrixC= matrixA @ matrixB

np.savetxt("matrixC_Py.txt",matrixC,fmt="%d")



#print(matrix)