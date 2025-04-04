import numpy as np

matrixA=np.random.randint(0,64,(256,256),dtype=int)
matrixB=np.random.randint(0,64,(256,256),dtype=int)

with open("matrixA.txt","w") as mat:
    #mat.write(matrix)
    np.savetxt("matrixA.txt", matrixA, fmt="%d")
with open("matrixB.txt","w") as mat:
    #mat.write(matrix)
    np.savetxt("matrixB.txt", matrixB, fmt="%d")
print("done")