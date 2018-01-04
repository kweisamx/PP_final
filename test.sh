#!/bin/bash

g++ cudaversion.cpp -lOpenCL

echo "Complier finish"

./a.out
echo "finish"
