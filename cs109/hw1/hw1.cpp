/*
	Name: Daniel Boles
	Class: CS109
	Professor: Ira Pohl
	Date 10/9/17
	Assignment: HW1

*/


#include <iostream>
#include <vector>

using namespace std;
const int N = 40;

void sum(int*p, int n, vector<int> d){				// The following function takes the sum of *p and the array d[i] of i <n

	int i;											// Define i
	*p = 0;											// Define *p as 0 before iterating

	for(i = 0; i < n; ++i) *p = *p + d[i];			// here we take the sum of the iterative loop from i to n
}

int main(){											// Beginning main which fills data[] array with integers 0 to 39 and then summs them all in the end

	int i;											// define i
	int accum = 0;									// define the total sum as 'accum' short for accumulation
	vector<int> data;
	data.push_back(0);								// define the vector data[] and fill it with the first value

	for(i = 1; i < N; ++i) data.push_back(i);		// begin iterative loop writing the integers into data[]
	sum(&accum, N, data);							// here the call to our function sum takes all the data vector and sums it into accum

	printf("sum is %d\n", accum);					// lastly print out the sum.
	return 0;
}