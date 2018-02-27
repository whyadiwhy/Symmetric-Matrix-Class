/**********************************************************************************************
		THIS FILE CONTAINS SOME EXAMPLE TEST CASES FOR THE SYMMETRIC MATRIX CLASS HEADER FILE
************************************************************************************************/

#include <iostream>
#include <iomanip>
#include <Eigen/Eigen>
#include "SymMat.h"
int main()
{
	//Creating a matrix from Eigen::Matrix
	Eigen::Matrix<float,3,3> M;
	M<<3.2, -1.3, 10.0,
	   8.3, 4.4, -2.5,
	   4.3, -5.2, 6.7;
	
	std::cout<<"\nThis is the Eigen matrix created:"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(4)<<M(i,j)<<" ";
		}
		std::cout<<std::endl;
	}

	//Creating a symmetric matrix from the elements of Eigen::Matrix
	SymMat<float> S={M(0,0), M(0,1), M(0,2),
					   		  M(1,1), M(1,2),
					  				  M(2,2)};

	std::cout<<"\nThis is the Symmetric matrix created from the Eigen matrix:"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(4)<<S(i,j)<<" ";
		}
		std::cout<<std::endl;
	}

	//Creating matrices to store the result of the operations
	Eigen::Matrix<float,3,3> SUM;
	Eigen::Matrix<float,3,3> DIFF1,DIFF2;
	Eigen::Matrix<float,3,3> MULT1,MULT2;

	//Calling the functions
	SUM=add(S,M);

	DIFF1=sub(S,M);
	DIFF2=sub(M,S);

	MULT1=mult(S,M);
	MULT2=mult(M,S);

/************************************************************************
		OPERATIONS BETWEEN TWO SYMMETRIC MATRICES
*************************************************************************/
	SymMat<float> S1={ 1, 4.3, 2,
					   	 56,  9,
					  		  6};

	std::cout<<"\nThis is another Symmetric matrix"<<std::endl;
	S1.print();

	//Getting an element of matrix through accessors 
	std::cout<<"\nElement at (1,0) is: "<<S1(1,0)<<std::endl;
	std::cout<<"\nElement at (0,1) is: "<<S1(0,1)<<std::endl;

	//Creating matrix of SymMat class
	SymMat<float> S2(3);
	S2=add(S1,S);
	SymMat<float> S3(3);
	S3=sub(S1,S);
	Eigen::Matrix<float,3,3> M1;
	M1=mult<float,3,3> (S1,S);
	
	std::cout<<"\nOperations between Symmetric matrices:"<<std::endl;

	std::cout<<"\nThe Sum of the matrices is:"<<std::endl;
	S2.print();

	std::cout<<"\nThe Difference of the matrices is:"<<std::endl;
	S3.print();

	std::cout<<"\nThe Multiplication of matrices is:"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(6)<<M1(i,j)<<" ";
		}
		std::cout<<std::endl;
	}


/************************************************************************
		OPERATIONS BETWEEN SYMMETRIC MATRIX AND EIGEN MATRIX
*************************************************************************/
	std::cout<<"\nOperations between Symmetric matrix and Eigen matrix:"<<std::endl;

	std::cout<<"\nThe Sum of the matrices is:"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(4)<<SUM(i,j)<<" ";
		}
		std::cout<<std::endl;
	}

	std::cout<<"\nThe Difference of matrices is:"<<std::endl;
	std::cout<<"Symmetric matrix - Eigen matrix"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(4)<<DIFF1(i,j)<<" ";
		}
		std::cout<<std::endl;
	}

	std::cout<<"\nEigen matrix - Symmetric matrix"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(4)<<DIFF2(i,j)<<" ";
		}
		std::cout<<std::endl;
	}


	std::cout<<"\nThe Multiplication of matrices is:"<<std::endl;
	std::cout<<"Symmetric matrix * Eigen matrix"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(6)<<MULT1(i,j)<<" ";
		}
		std::cout<<std::endl;
	}

	std::cout<<"\nEigen matrix * Symmetric matrix"<<std::endl;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			std::cout<<std::setw(6)<<MULT2(i,j)<<" ";
		}
		std::cout<<std::endl;
	}

	std::cout<<std::endl;

/************************************************************************
						RAISING AN ERROR
*************************************************************************/
//When no. of elements entred cannot be in a upper triangle of a square matrix	
	SymMat<float> S4={1,2,3,4};
	S4.print();

	return 0;
}