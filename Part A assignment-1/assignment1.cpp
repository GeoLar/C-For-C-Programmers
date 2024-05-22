/*
* Course C++ for C-programmers Part A. 
* Homework 1. Convert this program to C++
* 
* The program calculates the sum of numbers stored in a vector
* and prints the result on the standard outout.
*/
#include <cstddef>
#include <iostream>
#include <vector>

const std::size_t  kMaxNumbers = 40; // Initial size of vector containing numbers to summarize

// Calculates the sum of the numbers in vector d and returns it in the output parameter p
inline void Sum(int* p, const std::vector<int>& d) {
	*p = 0;

	for (std::size_t i = 0; i < d.size(); ++i)
		*p += d[i];
}

int main() {
	std::vector<int> data(kMaxNumbers); // Vector containing all of the numbers to summarize

	// Initialize the data vector
	for (int i = 0; i < kMaxNumbers; ++i)
		data.push_back(i);

	// Summarize and print the result
	int accum = 0; 
	Sum(&accum, data);
	std::cout << "The sum is " << accum << std::endl;

	return 0;

}