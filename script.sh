python3 matrixGen.py
echo "generated matrices"
time python3 matrix.py
echo "multiplied python"
gcc matrix.c -o matrix
echo "compiled"
chmod +x matrix
time ./matrix
echo "multiplied c"
python3 test.py
echo "tested"