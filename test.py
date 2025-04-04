import numpy as np 

matrixC = np.loadtxt("matrixC_C.txt", dtype="i")
matrixPy = np.loadtxt("matrixC_Py.txt", dtype="i")

if np.array_equal(matrixC, matrixPy):
    print("test passed")
else:
    print("test failed")
    print("First few differences:")
    diff = matrixC != matrixPy
    count = 0
    for i in range(len(matrixC)):
        for j in range(len(matrixC[0])):
            if diff[i][j] and count < 5:
                print(f"Position [{i},{j}]: C={matrixC[i][j]}, Python={matrixPy[i][j]}")
                count += 1