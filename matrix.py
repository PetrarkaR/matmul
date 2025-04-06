import numpy as np
import time 

n=256

matrixA= np.loadtxt("matrixA.txt",dtype="i")
matrixB= np.loadtxt("matrixB.txt",dtype="i")
st=time.monotonic()
matrixC= matrixA @ matrixB
et=time.monotonic()
flops=(2*n**3)
print(f"GFLOPS: {flops/(et-st)*10**-9} ")
print(f"time : {et-st}")
np.savetxt("matrixC_Py.txt",matrixC,fmt="%d")



#print(matrix)