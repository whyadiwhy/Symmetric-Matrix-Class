/***********************************************************************************************
This header file contains the Symmetric matrix class - SymMat

It stores only the upper triangle of the matrix in classical packed format.
The elements are stored such as first row is stored first , then second , then third row and so on.

Aim of this header file is to provide a symmetric matrix class which stores only the needed elements
and hence reduce the storage space and optimise the operations since the number of elements on which 
the operations are performed are less. 

************************************************************************************************/
//-----------------------------------------------------------------------------------------------


/************************************************************************************************
						INCLUDE GAURDS
*************************************************************************************************/
#ifndef SYMMAT_H
#define SYMMAT_H


/*************************************************************************************************
						INCLUDING THE DEPENDENCIES
**************************************************************************************************/
#include <vector>				//to use vector and its inbuilt functions
#include <initializer_list>		//to initilise the matrix
#include <iostream> 			//for cout in print function
#include <iomanip>  			//to use setw()
#include <cassert>  			//to use assert function
#include <cmath>				//to calculate the squareroot of a number
#include <cstdlib>  			//to use std::exit function 
#include <Eigen/Eigen> 			//to pass eigen matrix as arguments to functions


/*************************************************************************************************
						CLASS DEFINITION
						----------------
Template parameters used are same as in eigen so that it will be easy to merge with the main branch
**************************************************************************************************/
template <typename _Scalar>
class SymMat
{
public:

	//Order of the matrix
	int order;

	//Vector which stores the elements of the matrix
	std::vector<_Scalar> mat;
	
	//Initializer list
	SymMat(std::initializer_list<_Scalar>);

	//Default constructor
	SymMat();

	//Parametrized constructor(parameter is order of matrice)
	SymMat(int);
	
	//Returns the index of the element (i,j) stored in the vector
	int index(int,int);
	
	//Prints the matrix 
	void print();

	/***BASIC ARITHMETIC REDUCTION OPERATIONS*****/
	//Sum of the elements
	_Scalar sum();

	//Returns the mean of elements
	_Scalar mean();

	//Trace of matrix
	_Scalar trace();

	//Returns the minimum coefficient of the matrix
	_Scalar minCoeff();

	//Returns the maximum coefficient of the matrix
	_Scalar maxCoeff();

	/***ADDITIONAL FUNCTIONS***********/
	//No.of elements stored in the classical packed format
	int elemstored();

	//Product of the diagonal elements
	_Scalar diagprod();

	//Product of the elements of the matrix
	_Scalar prod();

	//Transpose function
	//SymMat transpose();

	//Overloading the funtion call operator
	_Scalar& operator()(int,int);

};

/***************************************************************************************************
						FUNCTION PROTOTYPES
						-------------------
This section contains the prototypes of the functions used:-
****************************************************************************************************/

//Addition------------------------------------------------------------------------------------------
template<typename _Scalar>
SymMat<_Scalar> add(SymMat<_Scalar>&,SymMat<_Scalar>&);

template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> add(SymMat<_Scalar>&,Eigen::Matrix<_Scalar,_Rows,_Cols>&);

template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> add(Eigen::Matrix<_Scalar,_Rows,_Cols>&,SymMat<_Scalar>&);


//Subtraction----------------------------------------------------------------------------------------
template<typename _Scalar>
SymMat<_Scalar> sub(SymMat<_Scalar>&,SymMat<_Scalar>&);

template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> sub(SymMat<_Scalar>&,Eigen::Matrix<_Scalar,_Rows,_Cols>&);

template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> sub(Eigen::Matrix<_Scalar,_Rows,_Cols>&,SymMat<_Scalar>&);


//Multiplication--------------------------------------------------------------------------------------
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> mult(SymMat<_Scalar>&,SymMat<_Scalar>&);

template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> mult(SymMat<_Scalar>&,Eigen::Matrix<_Scalar,_Rows,_Cols>&);

template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> mult(Eigen::Matrix<_Scalar,_Rows,_Cols>&,SymMat<_Scalar>&);



/*****************************************************************************************************
						CONSTRUCTOR
******************************************************************************************************/

//Initialize with a default 3x3 matrix initialised with '0'
template<typename _Scalar>
SymMat<_Scalar>::SymMat()
{
	int elements,i;
	order=3;
	elements=6;
	mat.resize(elements);
	std::fill(mat.begin(),mat.end(),0); //filling all elements of the vector with '0'
}

//Custom matrice of order as inputted by user intialised with '0'
template<typename _Scalar>
SymMat<_Scalar>::SymMat(int o)
{
	int elements;
	order=o;
	elements=(order*(order+1))/2;
	mat.resize(elements);
	std::fill(mat.begin(),mat.end(),0); //filling all elements of the vector with '0'
}

//Using initializer_list to initialize the matrice
template<typename _Scalar>
SymMat<_Scalar>::SymMat(std::initializer_list<_Scalar> list) :mat(list) 
{
	/*First it is checked whether the number of elements entered are equal to the elements in
	  the upper triangle of a square matrix.	
	  Since the the no. of elements follow the following series:- 3(for 2x2),6(for 3x3),10(for 4x4),... 
	  the following formula is used to calculate the order of the matrix and whether such an order exist:-
	  -----------------------------------
	  no.of elements=(order*(order+1))/2 
	  (Sum of arithmetic series:- 1,2,3,4...)
	  -----------------------------------
	  */
	order=int(sqrt(2*(mat.size())));
	try
	{
		if((order*(order+1))/2!=mat.size())
		{
			throw 'f';	
		}
		
	}
	catch(char& check)
	{
		std::cout<<"Wrong number of elements for a upper triangle of square matrix!\nTerminating the program..."<<std::endl;
		std::exit(0);
	}
	
}

/*******************************************************************************************************
						OVERLOADING FUNCTION CALL OPERATOR
********************************************************************************************************/
template<typename _Scalar>
_Scalar& SymMat<_Scalar>::operator()(int i, int j)
{
	if(i>=j)
	{
		return mat[index(i,j)];
	}
	else
	{
		//Since the matrix is symmetric, it means that A(i,j)==A(j,i)
		return mat[index(j,i)];
	}

}

/********************************************************************************************************
				CALCULATES THE INDEX OF ELEMENT AT (i,j) IN VECTOR
*********************************************************************************************************/
template<typename _Scalar>
int SymMat<_Scalar>::index(int i, int j)
{
	//to make calculations easy to understand (since the index starts from 0)
	i=i+1;
	j=j+1;

	int Index,total_elements,below_elements,temp;
	if(i>j)  //swapping i and j since the 
	{
		temp=i;
		i=j;
		j=temp;
	}

	//This variable stores the total no. of elements in the triangle
	total_elements=((order)*(order+1))/2;

	//This variable stores the elements which are below/next (from top to bottom) the element to be accessed
	below_elements=((order-i)*(order-i+1))/2 +(order-j);

	//This gives us the index of that element
	Index=total_elements-below_elements-1;	

	return Index;

}


/**********************************************************************************************************
						PRINT MATRIX
***********************************************************************************************************/

//Print function for printing the matrix belonging to SymMat class on screen
template<typename _Scalar>
void SymMat<_Scalar>::print()
{
  int i,j;
  for(i=0;i<order;i++)
  {
  	for (j=0;j<order;j++)
  	{  
  		std::cout<<std::setw(4)<<mat[index(i,j)]<<" ";  //setw() here sets 4 digits space for each element
	} 
  	std::cout<<"\n";
  }
}

/**********************************************************************************************************
						TRACE OF MATRIX
***********************************************************************************************************/

//Trace function to return trace of matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::trace()
{

  //This variable stores the trace of the matrix
  _Scalar store_trace=0;  

  for(int i=0;i<order;i++)
  {
  	store_trace += mat[index(i,i)];
  }
  return store_trace;
}

/**********************************************************************************************************
						PRODUCT OF DIAGONAL ELEMENTS OF THE MATRIX
***********************************************************************************************************/

//Function to return the product elements of the matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::diagprod()
{

  //This variable stores the trace of the matrix
  _Scalar store_diag_prod=1;  

  for(int i=0;i<order;i++)
  {
  	store_diag_prod *= mat[index(i,i)];
  }
  return store_diag_prod;
}




/**********************************************************************************************************
						SUM OF THE ELEMENTS OF MATRIX

Efficiency improvement:-

In a normal matrix, we have to traverse through all the elements to calculate the sum,
However here, the elements in upper triangle except the diagonal elements are same in the lower half, 
So we have to only calculate the sum of upper triangel except the diagonal elements and make it twice 
and then add it to the sum of diagonal elements.

***********************************************************************************************************/

//Sum function to return trace of matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::sum()
{

  //This variable stores the sum of the elements of matrix
  _Scalar store_sum=0,store_trace;

  store_trace=trace();

  for(int i=0;i<mat.size();i++)
  {
  	store_sum+=mat[i];
  }
  store_sum-=store_trace;
  store_sum*=2;
  store_sum+=store_trace;

  return store_sum;
}

/**********************************************************************************************************
						PRODUCT OF THE ELEMENTS OF MATRIX

Efficiency improvement:-

In a normal matrix, we have to traverse through all the elements to calculate the product,
However here, the elements in upper triangle except the diagonal elements are same in the lower half, 
So we have to only calculate the product of upper triangel except the diagonal elements and make it squared 
and then multiply it by the product of diagonal elements.

***********************************************************************************************************/

//Sum function to return trace of matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::prod()
{

  //This variable stores the sum of the elements of matrix
  _Scalar store_prod=1,store_diag_prod;

  store_diag_prod=diagprod();

  for(int i=0;i<mat.size();i++)
  {
  	store_prod*=mat[i];
  }
  store_prod/=store_diag_prod;
  store_prod*=store_prod;
  store_prod*=store_diag_prod;

  return store_prod;
}
 
 


/**********************************************************************************************************
						MEAN OF THE ELEMENTS OF MATRIX

Efficiency improvement:-

In a normal matrix, we have to traverse through all the elements to calculate the sum, and then divide by 
the total number of elements to get the mean.

However, in this class the sum is calculated efficiently using the sum() function and then it is divided by 
the total number of elements.

Hence overall it is faster to calculate the mean of the matrix.

***********************************************************************************************************/

//Mean function to return the mean of elements of the matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::mean()
{

  //This variable stores the sum of the elements of matrix
  _Scalar store_sum,store_mean;  

  store_sum=sum();
  store_mean=store_sum/(order*order);

  return store_mean;
}


/**********************************************************************************************************
						MAX COEFFICIENT AMONGST THE ELEMENTS OF MATRIX

Efficiency improvement:-

In a normal matrix, we have to traverse through all the elements to check all the elements.

In this class, we have to traverse through only the elements in the upper triangle. 

This improves the efficiency since the no. of iterations to check the maximum element value are less.

***********************************************************************************************************/

//Function to return the maximum coefficient in the matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::maxCoeff()
{

  //This variable stores the maximum of the elements of matrix
  _Scalar store_max=mat[0];  

  for(int i=1;i<mat.size();i++)
  {
  	if(mat[i]>store_max)
  	{
  		store_max=mat[i];
  	}
  }

  return store_max;
}


/**********************************************************************************************************
						MINIMUM COEFFICIENT AMONGST THE ELEMENTS OF MATRIX

Efficiency improvement:-

In a normal matrix, we have to traverse through all the elements to check all the elements.

In this class, we have to traverse through only the elements in the upper triangle. 

This improves the efficiency since the no. of iterations to check the minimum element value are less.

***********************************************************************************************************/

//Function to return the minimum coefficient in the matrix
template<typename _Scalar>
_Scalar SymMat<_Scalar>::minCoeff()
{

  //This variable stores the minimum of the elements of matrix
  _Scalar store_min=mat[0];  

  for(int i=1;i<mat.size();i++)
  {
  	if(mat[i]<store_min)
  	{
  		store_min=mat[i];
  	}
  }

  return store_min;
}
/*******************************************************************************************************
						NUMBER OF ELEMENTS STORED IN THE CLASSICAL PACKED FORMAT
********************************************************************************************************/
//Function to return the number of matrix elements stored in the classical packed format 
template<typename _Scalar>
int SymMat<_Scalar>::elemstored()
{
  return mat.size();
}



/***********************************************************************************************************
						ADDITION
					---------------	
Efficiency improvement:-
In addition between symmetric matrices, we only have to add the elements of upper triangle to get


There is function overloading for the following:
1)Both belongs to SymMat
2)First belongs to SymMat and other to Eigen::Matrix
3)First belongs to Eigen::Matrix and other to SymMat
************************************************************************************************************/


//Addition function for two matrices belonging to SymMat class
template<typename _Scalar>
SymMat<_Scalar> add(SymMat<_Scalar>& m1,SymMat<_Scalar>& m2)
{
	assert((m1.mat).size()==(m2.mat).size());       //Condition for matrices to be conformable for addition
	SymMat<_Scalar> m3(m1.order);					//Creating a matrix which stores the addition of these two matrices

	for(int i=0;i<(m1.mat).size();i++)
	{
		m3.mat[i]=m1.mat[i]+m2.mat[i];
	}
	return m3;

}


//Addition function between one matrix belonging to SymMat class(First argument) and another(Second argument) to Eigen::Matrix
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> add(SymMat<_Scalar>& m1,Eigen::Matrix<_Scalar,_Rows,_Cols>& m2)
{
	assert(m1.order == m2.rows() && m1.order == m2.cols());       //Condition for matrices to be conformable for addition
	Eigen::Matrix<_Scalar,_Rows,_Cols> m3;
	for(int i=0;i<m1.order;i++)
	{
		for(int j=0;j<m1.order;j++)
		{
			m3(i,j)=m1.mat[m1.index(i,j)]+m2(i,j);
		}
	}
	return m3;
}


//Addition function between one matrix belonging to Eigen::matrix(First argument) and SymMat class(Second argument) to Eigen::Matrix
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> add(Eigen::Matrix<_Scalar,_Rows,_Cols>& m2,SymMat<_Scalar>& m1)
{
	assert(m1.order==m2.rows() && m1.order == m2.cols());       //Condition for matrices to be conformable for addition
	Eigen::Matrix<_Scalar,_Rows,_Cols> m3;
	for(int i=0;i<m1.order;i++)
	{
		for(int j=0;j<m1.order;j++)
		{
			m3(i,j)=m1.mat[m1.index(i,j)]+m2(i,j);
		}
	}
	return m3;
}



/********************************************************************************************************
						SUBTRACTION
					------------------	
There is function overloading for the following:
1)Both belongs to SymMat
2)First belongs to SymMat and other to Eigen::Matrix
3)First belongs to Eigen::Matrix and other to SymMat
**********************************************************************************************************/

//Addition function for two matrices belonging to SymMat class
template<typename _Scalar>
SymMat<_Scalar> sub(SymMat<_Scalar>& m1,SymMat<_Scalar>& m2)
{
	assert((m1.mat).size()==(m2.mat).size());       //Condition for matrices to be conformable for addition
	SymMat<_Scalar> m3(m1.order);

	for(int i=0;i<(m1.mat).size();i++)
	{
		m3.mat[i]=m1.mat[i]-m2.mat[i];
	}
	return m3;

}


//Addition function between one matrix belonging to SymMat class(First argument) and another(Second argument) to Eigen::Matrix
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> sub(SymMat<_Scalar>& m1,Eigen::Matrix<_Scalar,_Rows,_Cols>& m2)
{
	assert(m1.order == m2.rows() && m1.order == m2.cols());       //Condition for matrices to be conformable for addition
	Eigen::Matrix<_Scalar,_Rows,_Cols> m3;
	for(int i=0;i<m1.order;i++)
	{
		for(int j=0;j<m1.order;j++)
		{
			m3(i,j)=m1.mat[m1.index(i,j)]-m2(i,j);
		}
	}
	return m3;
}


//Addition function between one matrix belonging to Eigen::matrix(First argument) and SymMat class(Second argument) to Eigen::Matrix
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> sub(Eigen::Matrix<_Scalar,_Rows,_Cols>& m2,SymMat<_Scalar>& m1)
{
	assert(m1.order==m2.rows() && m1.order == m2.cols());       //Condition for matrices to be conformable for addition
	Eigen::Matrix<_Scalar,_Rows,_Cols> m3;
	for(int i=0;i<m1.order;i++)
	{
		for(int j=0;j<m1.order;j++)
		{
			m3(i,j)=m2(i,j)-m1.mat[m1.index(i,j)];
		}
	}
	return m3;
}

/**********************************************************************************************************
						MULTIPLICATION
					--------------------	
There is function overloading for the following:
1)Both belongs to SymMat
2)First belongs to SymMat and other to Eigen::Matrix
3)First belongs to Eigen::Matrix and other to SymMat
************************************************************************************************************/

//Multiplication function for two matrices belonging to SymMat class
/*
Only for this function the template parameters are passed from the main funciton since both the function parameters are 
matrices belonging to SymMat class, so they don't contain rows and columns.
This will be corrected once this class inherits from Eigen::Matrix or is changed fully to match the Eigen library
*/
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> mult(SymMat<_Scalar>& m1,SymMat<_Scalar>& m2)
{	
	try
	{
		if(m1.order != m2.order)
		{
		  throw 'f';
		}

	}
	catch(char& check)
	{
		std::cout<< "Matrices are not compatible for multiplication!\nTerminating the program..."<< std::endl;
		exit(0);
	}

	//Multiplication
	Eigen::Matrix<_Scalar,_Rows,_Cols> m3;
	int i,j,k;
	for(i=0;i<m2.order;i++)
	{
		for(j=0;j<m2.order;j++)
		{
			m3(i,j)=0;
			for(k=0;k<m2.order;k++)
			{
				m3(i,j)+=m1.mat[m1.index(i,k)]*m2.mat[m2.index(k,j)];
			}
		}
	}
	return m3;
}


//Multiplication function between one matrix of SymMat class(first parameter) and another from Eigen::Matrix class(second parameter)
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> mult(SymMat<_Scalar>& m1,Eigen::Matrix<_Scalar,_Rows,_Cols>& m2)
{

	try
	{
		if(m1.order != m2.rows())
		{
		  throw 'f';
		}

	}
	catch(char& check)
	{
		std::cout<< "Matrices are not compatible for multiplication!\nTerminating the program..."<< std::endl;
		exit(0);
	}

	//Multiplication
	Eigen::Matrix<_Scalar,_Rows,_Cols> m3;
	int i,j,k;
	for(i=0;i<m1.order;i++)
	{
		for(j=0;j<m2.cols();j++)
		{
			m3(i,j)=0;
			for(k=0;k<m1.order;k++)
			{
				m3(i,j)+=m1.mat[m1.index(i,k)]*m2(k,j);
			}
		}
	}
	return m3;
}


//Multiplication function between one matrix of Eigen::Matrix class(first parameter) and another from SymMat class(second parameter)
template<typename _Scalar,int _Rows, int _Cols>
Eigen::Matrix<_Scalar,_Rows,_Cols> mult(Eigen::Matrix<_Scalar,_Rows,_Cols>& m2,SymMat<_Scalar>& m1)
{
	try
	{
		if(m1.order != m2.cols())
		{
		  throw 'f';
		}

	}
	catch(char& check)
	{
		std::cout<<"Matrices are not compatible for multiplication!\nTerminating the program..."<< std::endl;
		exit(0);
	}

	//Multiplication
	Eigen::Matrix<_Scalar,_Cols,_Rows> m3;
	int i,j,k;
	for(i=0;i<m2.rows();i++)
	{
		for(j=0;j<m1.order;j++)
		{
			m3(i,j)=0;
			for(k=0;k<m1.order;k++)
			{
				m3(i,j)+=m2(i,k)*m1.mat[m1.index(k,j)];
			}
		}
	}
	return m3;
}


//------------------------------------------------------------------------------------------------
#endif //SYMMAT_H
/*************************************************************************************************
								SYMMAT HEADER FILE ENDED
**************************************************************************************************/		