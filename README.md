# Symmetric-Matrix-Class
_This repository contains:_

    1)A header file that contains the definitions of symmetric matrix class---> SymMat

    2)testcases.cpp that contains the testcases for using the SymMat class and Eigen library

    3)Output images of the testcases.cpp on the terminal

    4)Makefile to compile the files using make.

    5)README.md (this file) which contains information about this repository and how to compile the program




## **_Compiling Instructions:_**

git clone the repository and cd into that folder

1)Using the ``make`` command :
Open the terminal and type ``make`` , this will create the output file called testcases.
then run the command ``./testcases`` , it will execute the file and produce the output.

2)On the terminal type:- ``g++ -std=c++11 testcases.cpp -o testcases`` , 
After that type:- ``./testcases`` to execute the output file and produce the output


## **_How program works:_**

1)*The SymMatrix class stores only the lower triangle in a vector in row major order.
Then to calculate the position of element in vector, sum of arithmetic series is used, since elements grow by one in the lower triangle.*

2)A C++ program(**calcspace.cpp**) that finds the space saved *(as compared to when the whole matrix is stored instead of just upper or lower triangular elements)* it inputs the order of matrix and size of each element and outputs the space saved.

The following operations are done on the matrix to check the efficiency of the program.

    1)Changing elements of only one triangle(upper or lower)

    2)Addition/subtraction(inputting two matrices in which atleast one is symmetric)
  
    3)Multiplication((inputting two matrices in which atleast one is symmetric)
  

Standard streams are used for Input and Output(Keyboard-Input and Monitor-Output)

**Theoretically** the value of **N can range from 0 to 18,446,744,073,709,551,615**(unsigned long long ), so the total elements the matrix can contain are: **> 10^38**

Since we store only half of the matrix(upper or lower triangle) we save space of (n^2 - n )/2 elements.
If each element is of 8bytes and value of N is (2x10^9)then **space saved is: ~ 8x2x10^18 bytes ~ 1.6x10^7 TB(Tera Bytes)**

Note:- 1TB~10^12 Bytes.

_**From practical point of view**: if we create 1000 matrices of size 100x100, where each element is of 8 bytes, then the space saved is: **3.96x10^7 bytes ~ 40 MB**_ 

It is evident that storage optimization becomes more important when we have very large number of data elements and of higher size.

## **RESULTS**
    
                             Space Saved
    N=3,     size=4 bytes -->12 bytes
    N=3,     size=8 bytes -->24 bytes
    N=1000,  size=4 bytes -->1.998e+06 bytes
    N=1000,  size=8 bytes -->3.996e+06 bytes
    N=10^6,  size=4 bytes -->2e+12 bytes
    N=10^6,  size=8 bytes -->4e+12 bytes
    N=10^9,  size=4 bytes -->2e+18 bytes
    N=10^9,  size=8 bytes -->4e+18 bytes
