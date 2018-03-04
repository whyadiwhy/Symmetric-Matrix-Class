#include <bits/stdc++.h>
using namespace std;

int main()
{
	cout<<"Enter the order of matrix (N):";
	unsigned long long int N;
	cin>>N;
	cout<<"Enter the size of the data elements(bytes):";
	int s;
	cin>>s;
	double c;
	cout<<"Enter no. of such matrices:";
	int num;
	cin>>num;
	c=num*s*(N*N-N)/2;
	cout<<"The space stored by storing only upper or lower traingle instead of the whole matrix is: "<<c<<" bytes\n";
	return 0;

}